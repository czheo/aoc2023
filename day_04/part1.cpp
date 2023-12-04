#include <iostream>
#include <set>
#include <cmath>

using namespace std;

int main()
{
  int id;
  int ans = 0;
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
    ans += cnt ? pow(2, cnt - 1) : 0;
  }
  cout << ans << endl;
}
