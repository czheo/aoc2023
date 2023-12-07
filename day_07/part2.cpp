#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <string>
#include <tuple>

using namespace std;

bool cmpChar(char a, char b) {
  string order = "J23456789TQKA";

  int posA = order.find(a);
  int posB = order.find(b);

  return posA < posB;
}

bool cmpStr(string a, string b) {
  for (int i = 0; i < 5; i++) {
    if (a[i] != b[i]) {
      return cmpChar(a[i], b[i]);
    }
  }
  return false;
}

bool cmpCard(pair<tuple<int, int, int, int>, string> a, pair<tuple<int, int, int, int>, string> b) {
  if (a.first == b.first) {
    return cmpStr(a.second, b.second);
  } else {
    return a.first < b.first;
  }
}

pair<tuple<int,int, int, int>, string> encode(string card) {
  map<char, int> cnts;
  for (int i = 0; i < 5; i++) {
    char c = card[i];
    if (cnts.find(c) == cnts.end()) {
      cnts[c] = 1;
    } else {
      cnts[c]++;
    }
  }
  
  int rank[6] = {0, 0, 0, 0, 0, 0};
  int j_cnt = 0;
  for (auto it = cnts.begin(); it != cnts.end(); it++) {
    if (it->first == 'J') {
      j_cnt = it->second;
      continue;
    }
    for (int i = 1; i < 6; i++) {
      if (it->second == i) {
        rank[i] += 1;
      }
    }
  }

  if (j_cnt == 5) {
    rank[5] = 1;
  } else if (j_cnt > 0) {
    for (int i = 4; i >= 1; i--) {
      if (rank[i] > 0) {
        rank[i + j_cnt]++;
        rank[i]--;
        break;
      }
    }
  }

  return make_pair(make_tuple(rank[5], rank[4], rank[3], rank[2]), card);
}


int main()
{
  vector<pair<pair<tuple<int, int, int, int>, string>, int>> cards;
  string line;
  while (getline(cin, line)) {
    string card = line.substr(0, 5);
    int score = stoi(line.substr(6, line.length() - 6));
    cards.push_back(make_pair(encode(card), score));
  }
  sort(cards.begin(), cards.end(), [](auto a, auto b) {
    return cmpCard(a.first, b.first);
  });
  long ans = 0;
  for (size_t i = 0; i < cards.size(); i++) {
    // cout << cards[i].second << " " << " " << cards[i].first.second;
    // auto [a, b, c, d] = cards[i].first.first;
    // cout << " " << a << " " << b << " " << c << " " << d << endl;
    ans += cards[i].second * (i + 1);
  }
  cout << ans << endl;
}
