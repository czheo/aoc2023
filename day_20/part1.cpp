#include <iostream>
#include <vector>
#include <map>
#include <deque>
#include <tuple>

using namespace std;

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
  vector<Module*> output;
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
    p == LOW ? lowCnt++ : highCnt++;
    proc->processBroadcast(from, p, this);
  }
};

class Conjunction : public Module {
public:
  map<string, Pulse> inputs;
  Conjunction(string n): Module(n) {}
  void accept(const string& from, Pulse p, const Processor* proc) {
    // cout << from << (p == LOW ? " -low" : " -high") << "-> " << name << endl;
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
    p == LOW ? lowCnt++ : highCnt++;
    proc->processFlipFlop(from, p, this);
  }
};

void Processor::processBroadcast(const string& from, Pulse p, Broadcast* mod) const{
  for (auto& out: mod->output) {
    Q.push_back({mod->name, p, out});
  }
}

void Processor::processConjunction(const string& from, Pulse p, Conjunction* mod) const{
  mod->inputs[from] = p;
  bool allHigh = all_of(mod->inputs.begin(), mod->inputs.end(), [](auto& p) { return p.second == HIGH; });
  for (auto& out: mod->output) {
    Q.push_back({mod->name, allHigh ? LOW: HIGH, out});
  }
}

void Processor::processFlipFlop(const string& from, Pulse p, FlipFlop* mod) const{
  if (p == LOW) {
    mod->on = !mod->on;
    for (auto& out: mod->output) {
      Q.push_back({mod->name, mod->on ? HIGH: LOW, out});
    }
  }
}

int main()
{
  map<string, Module*> modules;
  map<string, Conjunction*> conjModules;
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
      conjModules[modName] = conj;
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
      modules[from]->output.push_back(modules[dest]);
      if (conjModules.find(dest) != conjModules.end()) {
        conjModules[dest]->inputs[from] = LOW;
      }
    }
  }
  for (auto [name, mod]: modules) {
    cout << name << "->";
    for (auto out: mod->output) {
      cout << out->name << "|";
    }
    cout << endl;
  }

  Processor* proc = new Processor();
  Module* brdcst = modules["broadcaster"];
  for (int i = 0; i < 1000; i++) {
    Q.push_back({"button", LOW, brdcst});
    while (!Q.empty()) {
      auto [from, p, mod] = Q.front();
      Q.pop_front();
      mod->accept(from, p, proc);
    }
  }
  cout << lowCnt << "*" << highCnt << "=" << lowCnt * highCnt << endl;
}
