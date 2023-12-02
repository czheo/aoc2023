#include <iostream>

using namespace std;

int main()
{
  int id;
  int ans = 0;
  while (scanf("Game %d:", &id) != EOF) {
    while (1) {
      int red = 0, green = 0, blue = 0;
      int n;
      char color[10];
      char sep;
      scanf("%d %[a-z]%c", &n, color, &sep);
      if (strcmp(color, "red") == 0) {
        red = n;
      } else if (strcmp(color, "green") == 0) {
        green = n;
      } else if (strcmp(color, "blue") == 0) {
        blue = n;
      }
      if (red > 12 || green > 13 || blue > 14) {
        while (sep != '\n' && getchar() != '\n');
        break;
      } else if (sep == '\n') {
        ans += id;
        break;
      }
    }
  }
  printf("%d\n", ans);
}
