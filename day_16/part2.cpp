#include <iostream>
#include <vector>
#include <set>
#include <tuple>

using namespace std;

vector<string> map;
vector<vector<int>> visited;
set<tuple<int, int, int, int>> seen;
int M, N;

void simulate(int x, int y, int dx, int dy) {
  if (x >= M || x < 0 || y >= N || y < 0) {
    return;
  }
  if (seen.find(make_tuple(x, y, dx, dy)) != seen.end()) {
    return;
  }
  seen.insert(make_tuple(x, y, dx, dy));
  visited[x][y] += 1;
  // cout << x << " " << y << " " << dx << " " << dy << endl;
  if (map[x][y] == '-') {
    if (dy == 0) {
      simulate(x, y + 1, 0, 1);
      simulate(x, y - 1, 0, -1);
      return;
    }
  } else if (map[x][y] == '|') {
    if (dx == 0) {
      simulate(x + 1, y, 1, 0);
      simulate(x - 1, y, -1, 0);
      return;
    }
  } else if (map[x][y] == '/') {
    if (dx == 0 && dy == 1) {
      dx = -1;
      dy = 0;
    } else if (dx == 0 && dy == -1) {
      dx = 1;
      dy = 0;
    } else if (dx == 1 && dy == 0) {
      dx = 0;
      dy = -1;
    } else if (dx == -1 && dy == 0) {
      dx = 0;
      dy = 1;
    }
  } else if (map[x][y] == '\\') {
    if (dx == 0 && dy == 1) {
      dx = 1;
      dy = 0;
    } else if (dx == 0 && dy == -1) {
      dx = -1;
      dy = 0;
    } else if (dx == 1 && dy == 0) {
      dx = 0;
      dy = 1;
    } else if (dx == -1 && dy == 0) {
      dx = 0;
      dy = -1;
    }
  }
  simulate(x + dx, y + dy, dx, dy);
}

int count() {
  int ans = 0;
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      if (visited[i][j] > 0) {
        // cout << visited[i][j];
        ans++;
      } else {
        // cout << ".";
      }
    }
    // cout << endl;
  }
  return ans;
}

int tryBeam(int x, int y, int dx, int dy) {
  seen.clear();
  visited.clear();
  for (int i = 0; i < M; i++) {
    vector<int> row(N, 0);
    visited.push_back(row);
  }
  visited[x][y] = 1;
  simulate(x, y, dx, dy);
  return count();
}

int main()
{
  string line;
  while (getline(cin, line)) {
    map.push_back(line);
  }
  M = map.size();
  N = map[0].size();

  int ans = 0;
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++){
      for (auto [dx, dy] : vector<pair<int, int>>{{0, 1}, {0, -1}, {1, 0}, {-1, 0}}) {
        if (i == 0 || j == 0 || i == M - 1 || j == N - 1) {
          int curr = tryBeam(i, j, dx, dy);
          ans = max(ans, curr);
        }
      }
    }
  }
  cout << ans << endl;
}
