#include <iostream>
#include <vector>

using namespace std;

vector<int> search(const vector<string>& vec) {
  int i = 1;
  vector<int> ans;
  for (; i < vec.size(); i++) {
    int j = i - 1, k = i;
    while (j >= 0 and k < vec.size() && vec[j] == vec[k]) {
      j--;
      k++;
    }
    if (j < 0 or k >= vec.size()) {
      ans.push_back(i);
    }
  }
  return ans;
}

vector<string> getCols(const vector<string>& rows) {
  vector<string> cols;
  for (int i = 0; i < rows[0].size(); i++) {
    string col = "";
    for (int j = 0; j < rows.size(); j++) {
      col += rows[j][i];
    }
    cols.push_back(col);
  }
  return cols;
}

int solve(const vector<string>& rows) {
  vector<string> cols = getCols(rows);

  vector<int> ans = search(rows);
  if (ans.size() == 0) {
    return search(cols)[0];
  } else {
    return ans[0] * 100;
  }
}

int solve2(vector<string>& rows) {
  const int old_ans = solve(rows);
  for (int i = 0; i < rows.size(); i++) {
    for (int j = 0; j < rows[0].size(); j++) {
      rows[i][j] = rows[i][j] == '.' ? '#' : '.';
      vector<string> cols = getCols(rows);
      auto s1 = search(rows);
      auto s2 = search(cols);
      for (auto x : s1) {
        if (x * 100 != old_ans) {
          return x * 100;
        }
      }
      for (auto x : s2) {
        if (x != old_ans) {
          return x;
        }
      }
      rows[i][j] = rows[i][j] == '.' ? '#' : '.';
    }
  }
  return 0;
}

int main()
{
  string line;
  vector<string> rows;
  int out = 0;
  while (getline(cin, line)) {
    if (line == "") {
      int ans = solve2(rows);
      // cout << ans << endl;
      out += ans;
      rows.clear();
      continue;
    }
    rows.push_back(line);
  }
  int ans = solve2(rows);
  // cout << ans << endl;
  out += ans;
  cout << out << endl;
}
