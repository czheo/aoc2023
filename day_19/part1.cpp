#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct Condition {
  char category;
  char op;
  int value;
};

struct Rule {
  optional<Condition> condition;
  string action;
};

struct Workflow {
  string name;
  vector<Rule> rules;
};

typedef map<char, int> Part;

Rule parseRule(const string& line) {
  char cat;
  char op;
  int value;
  char action[10];
  if (sscanf(line.c_str(), "%c%c%d:%[A-z]", &cat, &op, &value, action) == 4) {
    return Rule{Condition{cat, op, value}, action};
  } else {
    return Rule{nullopt, line};
  }
}

vector<Rule> parseRules(const string& line) {
  vector<Rule> rules;
  size_t pos = 0;
  while (1) {
    size_t npos = line.find(',', pos);
    if (npos == string::npos) {
      rules.push_back(parseRule(line.substr(pos, line.size() - pos)));
      break;
    }
    rules.push_back(parseRule(line.substr(pos, npos - pos)));
    pos = npos + 1;
  }
  return rules;
}

Workflow parseWorkflow(const string& line) {
  size_t pos = line.find('{');
  string name = line.substr(0, pos);
  vector<Rule> rules = parseRules(line.substr(pos + 1, line.size() - pos - 2));
  return Workflow{name, rules};
}

Part parsePart(const string& line) {
  Part part;
  char c1, c2, c3, c4;
  int v1, v2, v3, v4;
  sscanf(line.c_str(), "{%c=%d,%c=%d,%c=%d,%c=%d}",
      &c1, &v1, &c2, &v2, &c3, &v3, &c4, &v4);
  part[c1] = v1;
  part[c2] = v2;
  part[c3] = v3;
  part[c4] = v4;
  return part;
}

string eval(const Workflow& workflow, const Part& part) {
  for (auto rule: workflow.rules) {
    if (rule.condition) {
      Condition cond = rule.condition.value();
      int partValue = part.at(cond.category);
      if (cond.op == '<' && partValue < cond.value) {
        return rule.action;
      } else if (cond.op == '>' && partValue > cond.value) {
        return rule.action;
      }
    } else {
      return rule.action;
    }
  }
  throw "no rule";
}

int runWorkflow(const map<string, Workflow>& workflows, const Part& part) {
  string name = "in";
  while (1) {
    name = eval(workflows.at(name), part);
    if (name == "A") {
      int ret = 0;
      for (auto p: part) {
        ret += p.second;
      }
      return ret;
    } else if (name == "R") {
      return 0;
    }
  }
}

int answer(const map<string, Workflow>& workflows, const vector<Part>& parts) {
  int ans = 0;
  for (auto part: parts) {
    ans += runWorkflow(workflows, part);
  }
  return ans;
}

int main()
{
  string line;
  map<string, Workflow> workflows;
  vector<Part> parts;
  while (getline(cin, line)) {
    if (line.empty()) {
      break;
    }
    Workflow workflow = parseWorkflow(line);
    workflows[workflow.name] = workflow;
  }
  while (getline(cin, line)) {
    parts.push_back(parsePart(line));
  }

  cout << answer(workflows, parts) << endl;
}
