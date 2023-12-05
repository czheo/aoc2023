#include <iostream>
#include <vector>
#include <deque>

using namespace std;

struct range {
  long start, end;
};

struct entry {
  long dest, src, len;
};

deque<range> process(deque<range> &ids) {
  long dest, src, len;
  vector<entry> map;
  while (scanf("%ld %ld %ld", &dest, &src, &len) > 0) {
    map.push_back({dest, src, len});
  }
  deque<range> new_ids;
  while (!ids.empty()) {
    auto id = ids.front();
    ids.pop_front();
    bool found = false;
    for (auto &e : map) {
      long start = e.src;
      long end = e.src + e.len - 1;
      long offset = e.dest - e.src;
      if (id.start <= end && id.end >= start) {
        new_ids.push_back({max(id.start, start) + offset, min(id.end, end) + offset});
        if (id.start < start) {
          ids.push_back({id.start, start - 1});
        }
        if (id.end > end) {
          ids.push_back({end + 1, id.end});
        }
        found = true;
        break;
      }
    }
    if (!found) {
      new_ids.push_back(id);
    }
  }
  return new_ids;
}

int main()
{
  scanf("seeds:");
  deque<range> ids;
  long start, len;
  while (scanf("%ld %ld", &start, &len) > 0) {
    ids.push_back({start, start + len - 1});
  }

  char from[30], to[30];
  while (scanf("%[a-z]-to-%[a-z] map:", from, to) != EOF) {
    ids = process(ids);
  }

  cout << min_element(ids.begin(), ids.end(),
      [](auto id1, auto id2){
        return id1.start < id2.start;
      })->start << endl;
}
