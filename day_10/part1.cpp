#include <iostream>
#include <vector>
#include <set>

using namespace std;

vector<string> grid;

tuple<bool, bool, bool, bool> ctod(char c)
{
  switch (c) {
    case '|':
      // up, down, left, right
      return make_tuple(true, true, false, false);
    case '-':
      return make_tuple(false, false, true, true);
    case 'L':
      return make_tuple(true, false, false, true);
    case 'J':
      return make_tuple(true, false, true, false);
    case '7':
      return make_tuple(false, true, true, false);
    case 'F':
      return make_tuple(false, true, false, true);
    default:
      return make_tuple(false, false, false, false);
  }
}

int run(int x, int y, char pipe) {
  set<pair<int, int>> visited;
  int steps = 0;
  // cout << "running " << x << "," << y << endl;
  auto [u, d, l, r] = ctod(pipe);
  int pu = false, pd = false, pl = false, pr = false;
  while (1) {
    if (u && !pd) {
      pu = true, pd = false, pl = false, pr = false;
      x--;
    } else if (d && !pu) {
      pu = false, pd = true, pl = false, pr = false;
      x++;
    } else if (l && !pr) {
      pu = false, pd = false, pl = true, pr = false;
      y--;
    } else if (r && !pl) {
      pu = false, pd = false, pl = false, pr = true;
      y++;
    }
    if (grid[x][y] == 'S') {
      return steps;
    }
    // cout << x << "," << y << endl;
    pipe = grid[x][y];
    tie(u, d, l, r) = ctod(pipe);
    if (pu && !d) {
      return -1;
    } else if (pd && !u) {
      return -1;
    } else if (pl && !r) {
      return -1;
    } else if (pr && !l) {
      return -1;
    }
    if (x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size()) {
      return -1;
    }
    steps++;

    if (visited.find(make_pair(x, y)) != visited.end()) {
        return -1;
    }
    visited.insert(make_pair(x, y));
    pipe = grid[x][y];
  }
  return -1;
}

int main()
{
  string line;
  int i = 0;
  int sx, sy;
  while (getline(cin, line)) {
    grid.push_back(line);
    if (line.find('S') != string::npos) {
      sx = i;
      sy = line.find('S');
    }
    i++;
  }
  
  string pipes = "|-LJ7F";
  for (char pipe : pipes) {
    int ans = run(sx, sy, pipe);
    if (ans > 0) {
      cout << (ans + 1) / 2 << endl;
      break;
    }
  }
}
