#include <iostream>
#include <vector>
#include <set>
#include <deque>

using namespace std;

struct Pipe {
  bool up, down, left, right;
  Pipe(bool u, bool d, bool l, bool r) : up(u), down(d), left(l), right(r) {}
};

vector<string> grid;
vector<vector<Pipe>> map;
vector<vector<char>> filled;
int sx, sy;

Pipe toPipe(char c)
{
  switch (c) {
    case '|':
      return Pipe(true, true, false, false);
    case '-':
      return Pipe(false, false, true, true);
    case 'L':
      return Pipe(true, false, false, true);
    case 'J':
      return Pipe(true, false, true, false);
    case '7':
      return Pipe(false, true, true, false);
    case 'F':
      return Pipe(false, true, false, true);
    default:
      return Pipe(false, false, false, false);
  }
}

bool valid(int x, int y) {
  return x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size();
}

set<pair<int, int>> run(int x, int y) {
  set<pair<int, int>> visited;
  int px = -100, py = -100;
  // cout << "run: " << x << "," << y << " " << grid[x][y] << endl;
  visited.insert(make_pair(x, y));
  while (1) {
    auto [u, d, l, r] = map[x][y];
    if (u && px != x - 1 && valid(x-1, y) && map[x - 1][y].down) {
      px = x--;
      py = y;
    } else if (d && px != x + 1 && valid(x+1, y) && map[x + 1][y].up) {
      px = x++;
      py = y;
    } else if (l && py != y - 1 && valid(x, y-1) && map[x][y - 1].right) {
      px = x;
      py = y--;
    } else if (r && py != y + 1 && valid(x, y+1) && map[x][y + 1].left) {
      px = x;
      py = y++;
    } else {
      return set<pair<int, int>>();
    }

    if (visited.find(make_pair(x, y)) != visited.end()) {
      if (x == sx && y == sy) {
        return visited;
      } else {
        return set<pair<int, int>>();
      }
    } else {
      visited.insert(make_pair(x, y));
    }

    // cout << x << "," << y
    //   << " " << map[x][y].up << map[x][y].down << map[x][y].left << map[x][y].right
    //   << " " << px << "," << py << endl;
  }
  return set<pair<int, int>>();
}


int bfs(int x, int y, set<pair<int, int>>& visited) {
  deque<pair<int, int>> q;
  q.push_back(make_pair(x, y));
  visited.insert(make_pair(x, y));
  bool isAns = true;
  int ans = 0;
  cout << "bfs: " << x << "," << y << endl;
  while (!q.empty()) {
    auto [x, y] = q.front();
    q.pop_front();
    for (auto [dx, dy] : vector<pair<int, int>>{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}) {
      int nx = x + dx, ny = y + dy;
      if (nx < 0 || nx >= filled.size() || ny < 0 || ny >= filled[0].size()) {
        isAns = false;
        continue;
      }
      if (visited.find(make_pair(nx, ny)) != visited.end()) {
        continue;
      }
      if (filled[nx][ny] == '.') {
        ans++;
      }
      if (filled[nx][ny] == ' ' || filled[nx][ny] == '.') {
        visited.insert(make_pair(nx, ny));
        q.push_back(make_pair(nx, ny));
      }
    }
  }
  return isAns ? ans : -1;
}


int search() {
  set<pair<int, int>> visited;
  for (int i = 0; i < filled.size(); i++) {
    for (int j = 0; j < filled[0].size(); j++) {
      if (filled[i][j] == ' ' && visited.find(make_pair(i, j)) == visited.end()) {
        int ans = bfs(i, j, visited);
        if (ans >= 0) {
          return ans;
        }
      }
    }
  }
  return 0;
}


int enclosed(set<pair<int, int>> path) {
  for (int i = 0; i < grid.size() * 2; i++) {
    filled.push_back(vector<char>());
  }
  for (int i = 0; i < filled.size(); i++) {
    for (int j = 0; j < grid[0].size() * 2; j++) {
      filled[i].push_back(' ');
    }
  }
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[0].size(); j++) {
      if (path.find(make_pair(i, j)) != path.end()) {
        filled[i * 2][j * 2] = grid[i][j];
        auto [u, d, l, r] = toPipe(grid[i][j]);
        if (u) {
          filled[i * 2 - 1][j * 2] = '|';
        }
        if (d) {
          filled[i * 2 + 1][j * 2] = '|';
        }
        if (l) {
          filled[i * 2][j * 2 - 1] = '-';
        }
        if (r) {
          filled[i * 2][j * 2 + 1] = '-';
        }
      } else {
        filled[i * 2][j * 2] = '.';
      }
    }
  }
  // for (int i = 0; i < filled.size(); i++) {
  //   for (int j = 0; j < filled[0].size(); j++) {
  //     cout << filled[i][j];
  //   }
  //   cout << endl;
  // }
  return search();
}

int main()
{
  string line;
  int i = 0;
  while (getline(cin, line)) {
    grid.push_back(line);
    map.push_back(vector<Pipe>());
    for (char c : line) {
      map[i].push_back(toPipe(c));
    }
    if (line.find('S') != string::npos) {
      sx = i;
      sy = line.find('S');
    }
    i++;
  }
  
  string pipes = "|-LJ7F";
  for (char pipe : pipes) {
    grid[sx][sy] = pipe;
    map[sx][sy] = toPipe(pipe);
    auto ans = run(sx, sy);
    if (ans.size() > 0) {
      // cout << ans.size() << endl;
      cout << enclosed(ans) << endl;
      break;
    }
  }
}
