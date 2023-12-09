#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int nextNum(vector<int>& nums)
{
  vector<int> next_nums;
  vector<int> firsts;
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
    firsts.push_back(nums[0]);
    if (all_zero) {
      int ret = 0;
      while (!firsts.empty()) {
        ret = firsts.back() - ret;
        firsts.pop_back();
      }
      return ret;
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
