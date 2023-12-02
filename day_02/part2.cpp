#include <iostream>

using namespace std;

int main()
{
  int id;
  int ans = 0;
  while (scanf("Game %d:", &id) != EOF) {
    int red = 0, green = 0, blue = 0;
    while (1) {
      int n;
      char color[10];
      char sep;
      scanf("%d %[a-z]%c", &n, color, &sep);
      if (strcmp(color, "red") == 0) {
        red = max(red, n);
      } else if (strcmp(color, "green") == 0) {
        green = max(green, n);
      } else if (strcmp(color, "blue") == 0) {
        blue = max(blue, n);
      }
      if (sep == '\n') {
        ans += red * green * blue;
        break;
      }
    }
  }
  printf("%d\n", ans);
}
