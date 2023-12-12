#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int solve(string springs, vector<int> cnts) {
  // cout << springs << " ";
  // for (int i = 0; i < cnts.size(); i++) {
  //   cout << cnts[i] << ",";
  // }
  // cout << endl;
  if (springs.empty() && cnts.empty()) {
    return 1;
  }
  if (cnts.empty()) {
    if (springs.find('#') == string::npos) {
      return 1;
    } else {
      return 0;
    }
  }
  if (reduce(cnts.begin(), cnts.end()) + cnts.size() > springs.size() + 1) {
    return 0;
  }
  if (springs[0] == '.') {
    return solve(springs.substr(1), cnts);
  } else if (springs[0] == '#') {
    int pos = 0;
    while (pos < cnts[0]) {
      if (springs[pos] == '.') {
        return 0;
      }
      pos++;
    }
    if (pos == springs.size()) {
      if (cnts.size() == 1) {
        return 1;
      } else {
        return 0;
      }
    }
    if (springs[pos] == '#') {
      return 0;
    }
    cnts.erase(cnts.begin());
    return solve(springs.substr(pos + 1), cnts);
  } else {
    return solve("." + springs.substr(1), cnts) + solve("#" + springs.substr(1), cnts);
  }
}

int main() {
  char c;
  string springs;
  vector<int> cnts;
  int ans = 0;
  while (scanf("%c", &c) != EOF) {
    if (c == ' ') {
      int cnt;
      while (scanf("%d%c", &cnt, &c) != EOF) {
        cnts.push_back(cnt);
        if (c == '\n') {
          int x = solve(springs, cnts);
          // cout << x << endl;
          ans += x;
          springs.clear();
          cnts.clear();
          break;
        }
      }
    } else {
      springs.push_back(c);
    }
  }
  cout << ans << endl;
}
