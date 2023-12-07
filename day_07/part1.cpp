#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <string>

using namespace std;

bool cmpChar(char a, char b) {
  string order = "23456789TJQKA";

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

bool cmpCard(pair<int, string> a, pair<int, string> b) {
  if (a.first == b.first) {
    return cmpStr(a.second, b.second);
  } else {
    return a.first < b.first;
  }
}

pair<int, string> encode(string card) {
  map<char, int> cnts;
  for (int i = 0; i < 5; i++) {
    char c = card[i];
    if (cnts.find(c) == cnts.end()) {
      cnts[c] = 1;
    } else {
      cnts[c]++;
    }
  }
  
  int rank = 0;
  for (auto it = cnts.begin(); it != cnts.end(); it++) {
    if (it->second == 5) {
      rank += 5000;
    } else if (it->second == 4) {
      rank += 400;
    } else if (it->second == 3) {
      rank += 30;
    } else if (it->second == 2) {
      rank += 2;
    }
  }

  return make_pair(rank, card);
}


int main()
{
  vector<pair<pair<int, string>, int>> cards;
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
    // cout << cards[i].second << " " << cards[i].first.first << " " << cards[i].first.second << endl;
    ans += cards[i].second * (i + 1);
  }
  cout << ans << endl;
}
