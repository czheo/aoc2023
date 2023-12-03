#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> grid;
int X, Y;
int x, y;

bool isValid(int x, int y) {
  pair<int, int> neighbors[] = {
    {x - 1, y}, {x + 1, y}, {x, y - 1}, {x, y + 1},
    {x - 1, y - 1}, {x - 1, y + 1}, {x + 1, y - 1}, {x + 1, y + 1},
  };
  for (auto nb: neighbors) {
    if (nb.first >= 0 && nb.first < X && nb.second >= 0 && nb.second < Y) {
      if (!isdigit(grid[nb.first][nb.second])
          && grid[nb.first][nb.second] != '.') {
        return true;
      }
    }
  }
  return false;
}

int parseNum() {
  int num = 0;
  bool valid = false;
  while (isdigit(grid[x][y])) {
    num = num * 10 + (grid[x][y] - '0');
    valid = valid || isValid(x, y);
    ++y;
  }
  return valid ? num : 0;
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

  int ans = 0;
  for (x = 0; x < X; ++x) {
    y = 0;
    while (y < Y) {
      if (isdigit(grid[x][y])) {
        ans += parseNum();
      } else {
        ++y;
      }
    }
  }

  cout << ans << endl;
}
