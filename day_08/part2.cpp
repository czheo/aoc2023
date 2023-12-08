#include <iostream>
#include <map>
#include <vector>
#include <numeric>

using namespace std;

string steps;
map<string, string> left_map;
map<string, string> right_map;

int getSteps(string curr) {
  int step = 0;
  for (int i = 0;; i = (i + 1) % steps.length()) {
    step++;
    char c = steps[i];
    if (c == 'L') {
      curr = left_map[curr];
    } else if (c == 'R') {
      curr = right_map[curr];
    }
    if (curr[2] == 'Z') {
      return step;
    }
  }
}

long getLCM(vector<long> nums) {
  long ret = 1L;
  for (size_t i = 0; i < nums.size(); i++) {
    ret = lcm(ret, nums[i]);
  }
  return ret;
}

int main()
{
  getline(cin, steps);

  string skip;
  getline(cin, skip);
  char from[4];
  char left[4];
  char right[4];
  while (scanf("%3s = (%3s, %3s)", from, left, right) == 3) {
    left_map[from] = left;
    right_map[from] = right;
  }

  vector<string> starts;
  for (auto it = left_map.begin(); it != left_map.end(); it++) {
    if (it->first[2] == 'A') {
      starts.push_back(it->first);
    }
  }

  vector<long> steps;
  for (size_t i = 0; i < starts.size(); i++) {
    steps.push_back(getSteps(starts[i]));
  }

  cout << getLCM(steps) << endl;
}
