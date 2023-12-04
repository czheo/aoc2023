#include <iostream>
#include <set>
#include <cmath>

using namespace std;

int main()
{
  int id;
  int ans = 0;
  int instances[300];
  fill_n(instances, 300, 1);
  while (scanf("Card %d:", &id) != EOF) {
    set<int> winners;
    int n;
    int cnt = 0;
    while (scanf("%d", &n) > 0) {
      winners.insert(n);
    }
    scanf("|");
    while (scanf("%d", &n) > 0) {
      if (winners.find(n) != winners.end()) {
        cnt++;
      }
    }
    for (int i = 0; i < cnt; ++i) {
      instances[i + id + 1] += instances[id];
    }
    ans += instances[id];
  }
  cout << ans << endl;
}
