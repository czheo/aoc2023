#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

vector<vector<int>> grid;

// x, y, steps, direction
map<tuple<int, int, int, int>, int> losses;

int encodeDir(const pair<int, int>& dir) {
  if (dir == make_pair(-1, 0)) return UP;
  if (dir == make_pair(1, 0)) return DOWN;
  if (dir == make_pair(0, -1)) return LEFT;
  if (dir == make_pair(0, 1)) return RIGHT;
  return -1;
}

int ans() {
  priority_queue<tuple<int, int, int, int, int>,
    std::vector<tuple<int, int, int, int, int>>,
    std::greater<tuple<int, int, int, int, int>>> q;
  q.push(make_tuple(0, 0, 0, 0, RIGHT));
  q.push(make_tuple(0, 0, 0, 0, DOWN));
  losses[make_tuple(0, 0, 0, RIGHT)] = 0;
  losses[make_tuple(0, 0, 0, DOWN)] = 0;
  int ans = INT_MAX;
  while (!q.empty()) {
    auto [loss, x, y, steps, dir] = q.top();
    q.pop();
    if (loss > ans) continue;
    if (x == grid.size() - 1 && y == grid[0].size() - 1) {
      ans = min(ans, loss);
      continue;
    }
    for (auto [dx, dy]: vector<pair<int, int>>{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}) {
      if (steps == 3 && encodeDir({dx, dy}) == dir) continue;
      if (dir == UP && encodeDir({dx, dy}) == DOWN) continue;
      if (dir == DOWN && encodeDir({dx, dy}) == UP) continue;
      if (dir == LEFT && encodeDir({dx, dy}) == RIGHT) continue;
      if (dir == RIGHT && encodeDir({dx, dy}) == LEFT) continue;
      int i = x + dx, j = y + dy;
      if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size()) continue;
      int newLoss = loss + grid[i][j];
      int newSteps = encodeDir({dx, dy}) == dir ? steps + 1 : 1;
      auto key = make_tuple(i, j, newSteps, encodeDir({dx, dy}));
      auto ent = losses.find(key);
      if (ent == losses.end() || newLoss < ent->second) {
        losses[key] = newLoss;
        q.push(make_tuple(newLoss, i, j, newSteps, encodeDir({dx, dy})));
      }
    }
  }
  return ans;
}

int main()
{
  string line;
  while (getline(cin, line)) {
    vector<int> row;
    for (char c : line) {
      row.push_back(c - '0');
    }
    grid.push_back(row);
  }

  cout << ans() << endl;
}
