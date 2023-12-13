#include <iostream>
#include <vector>

using namespace std;

int search(const vector<string>& vec) {
  int i = 1;
  int ans = 0;
  for (; i < vec.size(); i++) {
    int j = i - 1, k = i;
    while (j >= 0 and k < vec.size() && vec[j] == vec[k]) {
      j--;
      k++;
    }
    if (j < 0 or k >= vec.size()) ans += i;
  }
  return ans;
}

int solve(const vector<string>& rows) {
  vector<string> cols;
  for (int i = 0; i < rows[0].size(); i++) {
    string col = "";
    for (int j = 0; j < rows.size(); j++) {
      col += rows[j][i];
    }
    cols.push_back(col);
  }

  int ans = search(rows) * 100;
  if (ans > 0) return ans;
  return search(cols);
}

int main()
{
  string line;
  vector<string> rows;
  int out = 0;
  while (getline(cin, line)) {
    if (line == "") {
      int ans = solve(rows);
      // cout << ans << endl;
      out += ans;
      rows.clear();
      continue;
    }
    rows.push_back(line);
  }
  int ans = solve(rows);
  // cout << ans << endl;
  out += ans;
  cout << out << endl;
}
