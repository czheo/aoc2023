#include <iostream>

using namespace std;

int hashc(int curr, char c) {
  return (curr + c) * 17 % 256;
}

int hashs(const string& s) {
  int curr = 0;
  for (int i = 0; i < s.size(); i++) {
    curr = hashc(curr, s[i]);
  }
  return curr;
}

int main()
{
  char c;
  string s;
  int ans = 0;
  while (scanf("%c", &c) != EOF) {
    if (c == ',' || c == '\n') {
      ans += hashs(s);
      s = "";
    } else {
      s += c;
    }
  }
  cout << ans << endl;
}
