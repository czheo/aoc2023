#include <iostream>
#include <vector>

using namespace std;

int main()
{
  vector<int> times;
  vector<int> distances;
  scanf("Time:");
  int time;
  while (scanf("%d", &time) > 0) {
    times.push_back(time);
  }
  scanf("Distance:");
  int distance;
  while (scanf("%d", &distance) > 0) {
    distances.push_back(distance);
  }

  int ans = 1;
  for (size_t i = 0; i < times.size(); i++) {
    int cnt = 0;
    for (int x = 1; x < times[i]; x++) {
      if (x * (times[i] - x) > distances[i]) {
        cnt++;
      }
    }
    ans *= cnt;
  }
  cout << ans << endl;
}
