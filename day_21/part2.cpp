#include <iostream>
#include <vector>
#include <deque>

using namespace std;

vector<string> grid;

int ans(int sx, int sy, int step) {
  cout << step << endl;
  deque<pair<int, int>> q;
  q.push_back(make_pair(sx, sy));
  while (!q.empty() && step-- > 0) {
    int sz = q.size();
    for (int i = 0; i < sz; i++) {
      auto [x, y] = q.front();
      // cout << "(" << x << "," << y << ")";
      q.pop_front();
      for (auto [dx, dy]: vector<pair<int, int>>{{0, 1}, {0, -1}, {1, 0}, {-1, 0}}) {
        int nx = x + dx;
        int ny = y + dy;
        if (nx < 0 || nx >= grid.size() || ny < 0 || ny >= grid[nx].size()) {
          continue;
        }
        if (grid[nx][ny] == '#') {
          continue;
        }
        auto p = make_pair(nx, ny);
        if (find(q.begin(), q.end(), p) == q.end()) {
          q.push_back(p);
        }
      }
    }
    // cout << endl;
  }
  return q.size();
}

int main(int argc, char *argv[])
{
  int step = stoi(argv[1]);
  string line;
  while (getline(cin, line)) {
    grid.push_back(line);
  }

  int sx, sy;
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[i].size(); j++) {
      if (grid[i][j] == 'S') {
        sx = i;
        sy = j;
      }
    }
  }

  cout << ans(sx, sy, step) << endl;
}
