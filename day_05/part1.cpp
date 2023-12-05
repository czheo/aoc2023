#include <iostream>
#include <vector>

using namespace std;

vector<long> ids;

struct entry {
  long dest, src, len;
};

void process() {
  long dest, src, len;
  vector<entry> map;
  while (scanf("%ld %ld %ld", &dest, &src, &len) > 0) {
    map.push_back({dest, src, len});
  }
  for (auto &id : ids) {
    for (auto &e : map) {
      dest = e.dest;
      src = e.src;
      len = e.len;
      if (src <= id && id <= src + len - 1) {
        id = dest + (id - src);
        break;
      } 
    }
  }
}

int main()
{
  scanf("seeds:");
  long seed;
  while (scanf("%ld", &seed) > 0) {
    ids.push_back(seed);
  }

  char from[30], to[30];
  while (scanf("%[a-z]-to-%[a-z] map:", from, to) != EOF) {
    process();
  }

  printf("%ld\n", *min_element(ids.begin(), ids.end()));
}
