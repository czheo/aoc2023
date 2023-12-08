#include <iostream>
#include <map>

using namespace std;

int main()
{
  string steps;
  getline(cin, steps);

  string skip;
  getline(cin, skip);
  char from[4];
  char left[4];
  char right[4];
  map<string, string> left_map;
  map<string, string> right_map;
  while (scanf("%3s = (%3s, %3s)", from, left, right) == 3) {
    left_map[from] = left;
    right_map[from] = right;
  }

  int step = 0;
  string curr = "AAA";
  for (int i = 0;; i = (i + 1) % steps.length()) {
    step++;
    char c = steps[i];
    if (c == 'L') {
      curr = left_map[curr];
    } else if (c == 'R') {
      curr = right_map[curr];
    }
    if (curr == "ZZZ") {
      cout << step << endl;
      break;
    }
  }
}
