#include <iostream>
#include <vector>
#include <set>

using namespace std;

vector<string> map;

int main()
{
  string line;
  while (getline(cin, line)) {
    map.push_back(line);
  }

  set<int> miss_xs;
  set<int> miss_ys;
  for (int i = 0; i < map.size(); i++) {
    miss_xs.insert(i);
  }
  for (int i = 0; i < map[0].size(); i++) {
    miss_ys.insert(i);
  }

  vector<pair<int, int>> points;
  for (int i = 0; i < map.size(); i++) {
    for (int j = 0; j < map[0].size(); j++) {
      if (map[i][j] == '#') {
        miss_xs.erase(i);
        miss_ys.erase(j);
        points.push_back(make_pair(i, j));
      }
    }
  }

  vector<int> prefix_x;
  vector<int> prefix_y;
  int x_cnt = 0;
  int y_cnt = 0;
  for (int i = 0; i < map.size(); i++) {
    if (miss_xs.find(i) != miss_xs.end()) {
      x_cnt++;
    }
    prefix_x.push_back(x_cnt);
  }
  for (int j = 0; j < map[0].size(); j++) {
    if (miss_ys.find(j) != miss_ys.end()) {
      y_cnt++;
    }
    prefix_y.push_back(y_cnt);
  }

  long ans = 0;
  for (int i = 0; i < points.size(); i++) {
    for (int j = i + 1; j < points.size(); j++) {
      ans += abs(points[i].first - points[j].first) + abs(points[i].second - points[j].second)
        + abs(prefix_x[points[i].first] - prefix_x[points[j].first]) * 999999
        + abs(prefix_y[points[i].second] - prefix_y[points[j].second]) * 999999;
    }
  }
  cout << ans << endl;
}
