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
        cout << visited[i][j];
        ans++;
      } else {
        cout << ".";
      }
    }
    cout << endl;
  }
  return ans;
}

int main()
{
  string line;
  while (getline(cin, line)) {
    map.push_back(line);
  }
  M = map.size();
  N = map[0].size();
  for (int i = 0; i < M; i++) {
    vector<int> row(N, 0);
    visited.push_back(row);
  }

  visited[0][0] = 1;
  simulate(0, 0, 0, 1);

  cout << count() << endl;
}
