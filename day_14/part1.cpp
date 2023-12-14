#include <iostream>
#include <vector>

using namespace std;

int move(vector<string>& map, int i, int j) {
  while (i - 1 >= 0 && map[i - 1][j] == '.') {
    map[i][j] = '.';
    map[i - 1][j] = 'O';
    i--;
  }
  return map.size() - i;
}

int simulate(vector<string>& map) {
  int ans = 0;
  for (int i = 0; i < map.size(); i++) {
    for (int j = 0; j < map[i].size(); j++) {
      if (map[i][j] == 'O') {
        ans += move(map, i, j);
      }
    }
  }
  // for (auto line : map) {
  //   cout << line << endl;
  // }
  return ans;
}

int main()
{
  vector<string> map;
  string line;
  while (getline(cin, line)) {
    map.push_back(line);
  }

  cout << simulate(map) << endl;
}
