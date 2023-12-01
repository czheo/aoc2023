#include <iostream>

using namespace std;

const string numbers[] = {
  "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
};

int toInt(const string& s) {
  int n1 = -1;
  int n2 = -1;
  for (size_t i = 0; i < s.size(); i++) {
    if (isdigit(s[i])) {
      n2 = s[i] - '0';
      if (n1 == -1) {
        n1 = n2;
      }
    } else {
      for (size_t j = 0; j < 10; j++) {
        if (s.substr(i, numbers[j].size()) == numbers[j]) {
          n2 = j;
          if (n1 == -1) {
            n1 = n2;
          }
          break;
        }
      }
    }
  }
  return n1 * 10 + n2;
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
