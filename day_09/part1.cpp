#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int nextNum(vector<int>& nums)
{
  vector<int> next_nums;
  vector<int> lasts;
  int diff;
  while (1) {
    bool all_zero = true;
    for (size_t i = 0; i < nums.size() - 1; ++i) {
      diff = nums[i + 1] - nums[i];
      next_nums.push_back(diff);
      if (diff != 0) {
        all_zero = false;
      }
    }
    lasts.push_back(nums[nums.size() - 1]);
    if (all_zero) {
      return reduce(lasts.begin(), lasts.end());
    }
    nums = next_nums;
    next_nums = vector<int>();
  }
}

int main()
{
  string line;
  int ans = 0;
  vector<int> nums;
  int n;
  char c;
  while (scanf("%d%c", &n, &c) != EOF) {
    nums.push_back(n);
    if (c == '\n') {
      ans += nextNum(nums);
      nums.clear();
    }
  }
  cout << ans << endl;
}
