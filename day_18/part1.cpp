#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

struct Action {
  char dir;
  int dist;
};

const vector<pair<int, int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
map<pair<int, int>, int> grid;
int min_x = 0, max_x = 0, min_y = 0, max_y = 0;
set<pair<int, int>> visited;

int dfs(int x, int y) {
  vector<pair<int, int>> stack;
  stack.push_back({x, y});
  visited.insert({x, y});
  bool out = false;
  int ans = 0;
  while (!stack.empty()) {
    auto [x, y] = stack.back();
    stack.pop_back();
    ans++;
    for (auto [dx, dy]: dirs) {
      int nx = x + dx;
      int ny = y + dy;
      if (nx < min_x || nx > max_x || ny < min_y || ny > max_y) {
        out = true;
        continue;
      } 
      if (grid.find({nx, ny}) == grid.end() && visited.find({nx, ny}) == visited.end()) {
        visited.insert({nx, ny});
        stack.push_back({nx, ny});
      }
    }
  }
  return out ? 0 : ans;
}

int ans(const vector<Action>& actions) {
  int x = 0, y = 0;
  grid[{x, y}] = 1;
  for (auto action : actions) {
    int dx = 0, dy = 0;
    switch (action.dir) {
      case 'U':
        dx = -1;
        break;
      case 'D':
        dx = 1;
        break;
      case 'L':
        dy = -1;
        break;
      case 'R':
        dy = 1;
        break;
    }
    for (int i = 0; i < action.dist; i++) {
      x += dx;
      y += dy;
      grid[{x, y}] = 1;
      min_x = min(min_x, x);
      max_x = max(max_x, x);
      min_y = min(min_y, y);
      max_y = max(max_y, y);
    }
  }
  for (int i = min_x; i <= max_x; i++) {
    for (int j = min_y; j <= max_y; j++) {
      if (grid.find({i, j}) != grid.end() || visited.find({i, j}) != visited.end()) {
        continue;
      }
      int ans = dfs(i, j);
      if (ans != 0) {
        return ans + grid.size();
      }
    }
  }
  return 0;
}

int main()
{
  char dir;
  int dist;
  char rgb[7];
  vector<Action> actions;
  while (scanf("%c %d (#%6s)\n", &dir, &dist, rgb) != EOF) {
    Action action {dir, dist};
    actions.push_back(action);
  }

  cout << ans(actions) << endl;
}
