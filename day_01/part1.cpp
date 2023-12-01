#include <iostream>

using namespace std;

int toInt(const string& s) {
  char c1 = '\0';
  char c2 = '\0';
  for (size_t i = 0; i < s.size(); i++) {
    if (isdigit(s[i])) {
      c2 = s[i];
      if (c1 == '\0') {
        c1 = c2;
      }
    }
  }
  return (c1 - '0') * 10 + (c2 - '0');
}

int main()
{
  string line;
  int sum = 0;
  while (getline(cin, line)) {
    int n = toInt(line);
    sum += n;
  }
  cout << sum << endl;
}
