#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void removeSpace(string &str)
{
  str.erase(remove(str.begin(), str.end(), ' '), str.end());
}

int main()
{
  string time_s;
  scanf("Time: ");
  getline(cin, time_s);
  scanf("Distance: ");
  string dist_s;
  getline(cin, dist_s);
  removeSpace(time_s);
  removeSpace(dist_s);
  long time = stol(time_s);
  long dist = stol(dist_s);
  int cnt = 0;
  for (int x = 1; x < time; x++) {
    if (x * (time - x) > dist) {
      cnt++;
    }
  }
  cout << cnt << endl;
}
