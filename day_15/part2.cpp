#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Lens {
  string label;
  int l;
};

vector<vector<Lens>> boxes;

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

void insert(Lens lens) {
  int hash = hashs(lens.label);
  vector<Lens>& box = boxes[hash];
  if (lens.l == -1) {
    box.erase(remove_if(box.begin(), box.end(), [&lens](Lens& l) {
      return l.label == lens.label;
    }), box.end());
  } else {
    auto x = find_if(box.begin(), box.end(), [&lens](Lens& l) {
      return l.label == lens.label;
    });
    if (x == box.end()) {
      box.push_back(lens);
    } else {
      x->l = lens.l;
    }
  }
}

int getAns() {
  int ret = 0;
  for (int i = 0; i < 256; i++) {
    vector<Lens>& box = boxes[i];
    for (int j = 0; j < box.size(); j++) {
      int ans = (i + 1) * (j + 1) * box[j].l;
      // cout << box[j].label << "=>" << (i + 1) << "*" << (j + 1) << "*" << box[j].l << "=" << ans << endl;
      ret += ans;
    }
  }
  return ret;
}

int main()
{
  for (int i = 0; i < 256; i++) {
    boxes.push_back(vector<Lens>());
  }
  char c;
  Lens lens;
  while (scanf("%c", &c) != EOF) {
    if (c == ',' || c == '\n') {
      insert(lens);
      lens.label = "";
    } else if (c == '-') {
      lens.l = -1;
    } else if (c == '=') {
      scanf("%d", &lens.l);
    } else {
      lens.label += c;
    }
  }

  cout << getAns() << endl;
}
