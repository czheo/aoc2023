#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

struct Action {
  char dir;
  long long dist;
};

struct Coord {
  long long x;
  long long y;
};

struct Line {
  Coord start;
  Coord end;
};

vector<Line> lines;


/**
 * using shoelace area formula
 * https://www.youtube.com/watch?v=0KjG8Pg6LGk
 */
long long ans(const vector<Action>& actions) {
  long long x = 0, y = 0;
  long long ret = 0;
  for (auto action : actions) {
    long long dx = 0, dy = 0;
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
    long long nx = x + dx * action.dist;
    long long ny = y + dy * action.dist;
    // cout << x << "," << y << "=>" << nx << "," << ny << endl;
    ret += (y * nx) - (x * ny) + abs(nx - x) + abs(ny - y);
    x = nx, y = ny;
  }
  return (ret + 2) / 2;
}

char toDir(char c) {
  switch (c) {
    case '0':
      return 'R';
    case '1':
      return 'D';
    case '2':
      return 'L';
    case '3':
      return 'U';
  }
  return '?';
}

int main()
{
  char dir;
  long dist;
  char rgb[7];
  vector<Action> actions;
  while (scanf("%c %ld (#%6s)\n", &dir, &dist, rgb) != EOF) {
    Action action {toDir(rgb[5]), strtol(string(rgb).substr(0, 5).c_str(), NULL, 16)};
    actions.push_back(action);
    // cout << rgb << " " << action.dir << " " << action.dist << endl;
  }

  cout << ans(actions) << endl;
}
