#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>

using namespace std;

vector<string> grid;
int X, Y;
int x, y;
map<pair<int, int>, vector<int>> connectedNums;

pair<int, int> symbolPos(int x, int y) {
  pair<int, int> nbs[] = {
    {x - 1, y}, {x + 1, y}, {x, y - 1}, {x, y + 1},
    {x - 1, y - 1}, {x - 1, y + 1}, {x + 1, y - 1}, {x + 1, y + 1},
  };
  for (auto nb: nbs) {
    if (nb.first >= 0 && nb.first < X && nb.second >= 0 && nb.second < Y) {
      if (grid[nb.first][nb.second] == '*') {
        return {nb.first, nb.second};
      }
    }
  }
  return {-1, -1};
}

void parseNum() {
  int num = 0;
  set<pair<int, int>> symbols;
  while (isdigit(grid[x][y])) {
    num = num * 10 + (grid[x][y] - '0');
    auto pos = symbolPos(x, y);
    if (pos != make_pair(-1, -1)) {
      symbols.insert(pos);
    }
    ++y;
  }
  for (auto symbol: symbols) {
    connectedNums[symbol].push_back(num);
  }
}


void parseInput() {
  string line;
  while (getline(cin, line)) {
    grid.push_back(line);
  }
  X = grid.size();
  Y = grid[0].size();
}


int main()
{
  parseInput();

  for (x = 0; x < X; ++x) {
    y = 0;
    while (y < Y) {
      if (isdigit(grid[x][y])) {
        parseNum();
      } else {
        ++y;
      }
    }
  }

  int ans = 0;
  for (auto kv: connectedNums) {
    if (kv.second.size() == 2) {
      ans += kv.second[0] * kv.second[1];
    }
  }
  cout << ans << endl;
}
