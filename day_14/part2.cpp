#include <iostream>
#include <vector>

using namespace std;

void move_e(vector<string>& map) {
  for (int j = map[0].size() - 1; j >= 0; j--) {
    for (int i = 0; i < map.size(); i++) {
      if (map[i][j] == 'O') {
        int x = i, y = j;
        while (y + 1 < map[0].size() && map[x][y + 1] == '.') {
          map[x][y] = '.';
          map[x][y + 1] = 'O';
          y++;
        }
      }
    }
  }
}

void move_s(vector<string>& map) {
  for (int i = map.size() - 1; i >= 0; i--) {
    for (int j = 0; j < map[0].size(); j++) {
      if (map[i][j] == 'O') {
        int x = i, y = j;
        while (x + 1 < map.size() && map[x + 1][y] == '.') {
          map[x][y] = '.';
          map[x + 1][y] = 'O';
          x++;
        }
      }
    }
  }
}

void move_w(vector<string>& map) {
  for (int j = 0; j < map[0].size(); j++) {
    for (int i = 0; i < map.size(); i++) {
      if (map[i][j] == 'O') {
        int x = i, y = j;
        while (y - 1 >= 0 && map[x][y - 1] == '.') {
          map[x][y] = '.';
          map[x][y - 1] = 'O';
          y--;
        }
      }
    }
  }
}

void move_n(vector<string>& map) {
  for (int i = 0; i < map.size(); i++) {
    for (int j = 0; j < map[0].size(); j++) {
      if (map[i][j] == 'O') {
        int x = i, y = j;
        while (x - 1 >= 0 && map[x - 1][y] == '.') {
          map[x][y] = '.';
          map[x - 1][y] = 'O';
          x--;
        }
      }
    }
  }
}

int weight(const vector<string>& map) {
  int ret = 0;
  for (int i = 0; i < map.size(); i++) {
    ret += count(map[i].begin(), map[i].end(), 'O') * (map.size() - i);
  }
  return ret;
}

int simulate(vector<string>& map) {
  move_n(map);
  move_w(map);
  move_s(map);
  move_e(map);
  // for (auto line : map) {
  //   cout << line << endl;
  // }
  return weight(map);
}

int main()
{
  vector<string> map;
  string line;
  while (getline(cin, line)) {
    map.push_back(line);
  }

  for (int i = 0; i < 500; i++) {
    cout << simulate(map) << ",";
  }
  cout << endl;
}
