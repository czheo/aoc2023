#include <iostream>
#include <vector>
#include <numeric>
#include <map>

using namespace std;

long withMemo(string springs, int p, vector<int> cnts, map<pair<string, int>, long>& memo);

long solve(string springs, int p, const vector<int>& cnts, map<pair<string, int>, long>& memo) {
  if (springs.empty() && p == cnts.size()) {
    return 1;
  }
  if (p == cnts.size()) {
    if (springs.find('#') == string::npos) {
      return 1;
    } else {
      return 0;
    }
  }
  int total = 0;
  for (int i = p; i < cnts.size(); i++) {
    total += cnts[i];
  }
  if (total + cnts.size() - p > springs.size() + 1) {
    return 0;
  }
  if (springs[0] == '.') {
    return withMemo(springs.substr(1), p, cnts, memo);
  } else if (springs[0] == '#') {
    int pos = 0;
    while (pos < cnts[p]) {
      if (springs[pos] == '.') {
        return 0;
      }
      pos++;
    }
    if (pos == springs.size()) {
      if (cnts.size() - p == 1) {
        return 1;
      } else {
        return 0;
      }
    }
    if (springs[pos] == '#') {
      return 0;
    }
    return withMemo(springs.substr(pos + 1), p + 1, cnts, memo);
  } else {
    return withMemo(springs.substr(1), p, cnts, memo) + withMemo("#" + springs.substr(1), p, cnts, memo);
  }
}

long withMemo(string springs, int p, vector<int> cnts, map<pair<string, int>, long>& memo) {
  if (memo.find(make_pair(springs, p)) != memo.end()) {
    return memo[make_pair(springs, p)];
  }
  long ans = solve(springs, p, cnts, memo);
  memo[make_pair(springs, p)] = ans;
  return ans;
}

int main() {
  char c;
  string springs;
  vector<int> cnts;
  long ans = 0;
  while (scanf("%c", &c) != EOF) {
    if (c == ' ') {
      int cnt;
      while (scanf("%d%c", &cnt, &c) != EOF) {
        cnts.push_back(cnt);
        if (c == '\n') {
          vector<int> cnts2;
          for (int i = 0; i < 5; i++) {
            cnts2.insert(cnts2.end(), cnts.begin(), cnts.end());
          }
          map<pair<string, int>, long> memo;
          long x = withMemo(springs + "?" + springs + "?" + springs + "?" + springs + "?" + springs, 0, cnts2, memo);
          cout << x << endl;
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
