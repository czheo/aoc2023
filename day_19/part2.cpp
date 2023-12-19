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


long long answer(const map<string, Workflow>& workflows, string name, map<char, pair<int, int>> parts) {
  long long ret = 0;
  if (name == "A") {
    ret = 1;
    for (auto [k, v]: parts) {
      ret *= (v.second - v.first + 1);
    }
  } else if (name == "R") {
    ret = 0;
  } else {
    Workflow workflow = workflows.at(name);
    for (auto rule: workflow.rules) {
      if (rule.condition) {
        Condition cond = rule.condition.value();
        char cat = cond.category;
        pair<int, int> range = parts[cat];
        if (cond.op == '<') {
          if (cond.value > range.first) {
            map<char, pair<int, int>> newParts = parts;
            newParts[cat].second = min(cond.value - 1, range.second);
            ret += answer(workflows, rule.action, newParts);
            if (cond.value <= range.second) {
              parts[cat].first = cond.value;
            }
          }
        } else if (cond.op == '>') {
          if (cond.value < range.second) {
            map<char, pair<int, int>> newParts = parts;
            newParts[cat].first = max(cond.value + 1, range.first);
            ret += answer(workflows, rule.action, newParts);
            if (cond.value >= range.first) {
              parts[cat].second = cond.value;
            }
          }
        } else {
          throw "Bad op";
        }
      } else {
        ret += answer(workflows, rule.action, parts);
      }
    }
  }
  return ret;
}

int main()
{
  string line;
  map<string, Workflow> workflows;
  while (getline(cin, line)) {
    if (line.empty()) {
      break;
    }
    Workflow workflow = parseWorkflow(line);
    workflows[workflow.name] = workflow;
  }

  map<char, pair<int, int>> parts;
  parts['x'] = {1, 4000};
  parts['m'] = {1, 4000};
  parts['a'] = {1, 4000};
  parts['s'] = {1, 4000};

  cout << answer(workflows, "in", parts) << endl;
}
