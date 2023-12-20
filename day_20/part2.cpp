#include <iostream>
#include <vector>
#include <map>
#include <deque>
#include <tuple>
#include <set>

using namespace std;

int ans = 1;

enum Pulse {
  LOW, HIGH
};

class Broadcast;
class Conjunction;
class FlipFlop;

struct Processor {
public:
  void processBroadcast(const string& from, Pulse p, Broadcast* mod) const;
  void processConjunction(const string& from, Pulse p, Conjunction* mod) const;
  void processFlipFlop(const string& from, Pulse p, FlipFlop* mod) const;
};

class Module {
public:
  string name;
  vector<Module*> input;
  vector<Module*> output;
  Pulse lastPulse = LOW;
  Module(string n): name(n), output() {}
  virtual void accept(const string& from, Pulse p, const Processor* proc) = 0;
};

deque<tuple<string, Pulse, Module*>> Q;
long lowCnt = 0, highCnt = 0;


class Broadcast : public Module {
public:
  Broadcast(string n): Module(n) {}
  void accept(const string& from, Pulse p, const Processor* proc) {
    // cout << from << (p == LOW ? " -low" : " -high") << "-> " << name << endl;
    if (name == "rx" && p == LOW) {
      cout << ans << endl;
      exit(0);
    }
    p == LOW ? lowCnt++ : highCnt++;
    proc->processBroadcast(from, p, this);
  }
};

class Conjunction : public Module {
public:
  Conjunction(string n): Module(n) {}
  void accept(const string& from, Pulse p, const Processor* proc) {
    // cout << from << (p == LOW ? " -low" : " -high") << "-> " << name << endl;
    if (name == "rx" && p == LOW) {
      cout << ans << endl;
      exit(0);
    }
    p == LOW ? lowCnt++ : highCnt++;
    proc->processConjunction(from, p, this);
  }
};

class FlipFlop : public Module {
public:
  bool on;
  FlipFlop(string n): Module(n), on(false) {}
  void accept(const string& from, Pulse p, const Processor* proc) {
    // cout << from << (p == LOW ? " -low" : " -high") << "-> " << name << endl;
    if (name == "rx" && p == LOW) {
      cout << ans << endl;
      exit(0);
    }
    p == LOW ? lowCnt++ : highCnt++;
    proc->processFlipFlop(from, p, this);
  }
};

void Processor::processBroadcast(const string& from, Pulse p, Broadcast* mod) const{
  mod->lastPulse = p;
  for (auto& out: mod->output) {
    Q.push_back({mod->name, p, out});
  }
}

void Processor::processConjunction(const string& from, Pulse p, Conjunction* mod) const{
  bool allHigh = all_of(mod->input.begin(), mod->input.end(), [](auto& in) { return in->lastPulse == HIGH; });
  mod->lastPulse = allHigh ? LOW: HIGH;
  vector<string> keys {"cn", "gh", "hz", "xc"};
  if (find(keys.begin(), keys.end(), mod->name) != keys.end() && allHigh) {
    cout << mod->name << ":" << ans << endl;
  }
  for (auto& out: mod->output) {
    Q.push_back({mod->name, mod->lastPulse, out});
  }
}

void Processor::processFlipFlop(const string& from, Pulse p, FlipFlop* mod) const{
  if (p == LOW) {
    mod->on = !mod->on;
    mod->lastPulse = mod->on ? HIGH : LOW;
    for (auto& out: mod->output) {
      Q.push_back({mod->name, mod->lastPulse, out});
    }
  }
}

int main()
{
  map<string, Module*> modules;
  vector<pair<string, vector<string>>> connections;
  char name[100];
  char sep;
  while (scanf("%s ->", name) != EOF) {
    string modName;
    if (name[0] == '%') {
      modName = name + 1;
      FlipFlop* ff = new FlipFlop(modName);
      modules[modName] = ff;
    } else if (name[0] == '&') {
      modName = name + 1;
      Conjunction* conj = new Conjunction(modName);
      modules[modName] = conj;
    } else {
      modName = name;
      Broadcast* bc = new Broadcast(modName);
      modules[modName] = bc;
    }
    vector<string> dests;
    while (scanf(" %[^,\n]%c", name, &sep) != EOF) {
      dests.push_back(name);
      if (sep == '\n') break;
    }
    connections.push_back({modName, dests});
  }

  for (auto [from, dests]: connections) {
    for (auto dest: dests) {
      if (modules.find(dest) == modules.end()) {
        modules[dest] = new Broadcast(dest);
      }
      modules[dest]->input.push_back(modules[from]);
      modules[from]->output.push_back(modules[dest]);
    }
  }

  /**
   * By inspecting, we can find the Conjunctions are wired in a particular structure.
   *
   * cn   gh   hz   xc
   * |    |    |    |
   * sh   bh   mz   jf
   *   \   \  /   /
   *     \  \/  /
   *        mf
   *        |
   *        rx
   * 
   * For rx to get LOW, all inputs of mf should be HIGH, i.e. sh, bh, mz, jf should output HIGH.
   * Then, cn, gh, hz, xc should output LOW.
   * We just need to figure out how many times we need to press the button until that happens.
   * A periodic pattern can be observed for cn, gh, hz, xc to turn LOW,
   * so we just need to find the LCM of the periods.
   */
  for (auto [name, mod]: modules) {
    if (dynamic_cast<Conjunction*>(mod) != nullptr) {
      cout << name << " <- ";
      for (auto in: mod->input) {
        cout << in->name << ",";
      }
      cout << endl;
    }
  }


  Processor* proc = new Processor();
  Module* brdcst = modules["broadcaster"];
  for (;; ans++) {
    Q.push_back({"button", LOW, brdcst});
    while (!Q.empty()) {
      auto [from, p, mod] = Q.front();
      Q.pop_front();
      mod->accept(from, p, proc);
    }
  }
}
