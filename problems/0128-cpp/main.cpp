// Source: https://leetcode.com/problems/longest-consecutive-sequence
// Title: Longest Consecutive Sequence
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an unsorted array of integers `nums`, return the length of the longest consecutive elements sequence.
//
// You must write an algorithm that runs in`O(n)`time.
//
// **Example 1:**
//
// ```
// Input: nums = [100,4,200,1,3,2]
// Output: 4
// Explanation: The longest consecutive elements sequence is `[1, 2, 3, 4]`. Therefore its length is 4.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [0,3,7,2,5,8,4,6,0,1]
// Output: 9
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [1,0,1,2]
// Output: 3
// ```
//
// **Constraints:**
//
// - `0 <= nums.length <= 10^5`
// - `-10^9 <= nums[i] <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

// Use hash map + union-find
class Solution {
  vector<int> parent;
  vector<int> size;
  int maxSize;

  void build(int n) {
    parent.resize(n);
    size.resize(n);
    for (auto i = 0; i < n; i++) {
      parent[i] = i;
      size[i] = 1;
    }
    maxSize = 1;
  }

  int find(int x) {
    if (parent[x] != x) {
      parent[x] = find(parent[x]);
    }
    return parent[x];
  }

  void merge(int x, int y) {  // the keyword union is reserved
    x = find(x);
    y = find(y);
    if (x == y) return;

    // Ensure size(x) >= size(y)
    if (size[x] < size[y]) {
      swap(x, y);
    }

    parent[y] = x;
    size[x] += size[y];
    maxSize = max(maxSize, size[x]);
  }

 public:
  int longestConsecutive(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;

    unordered_map<int, int> num2idx;
    for (auto i = 0; i < n; i++) {
      num2idx[nums[i]] = i;
    }

    build(n);

    for (auto [x, _] : num2idx) {
      auto y = x + 1;
      if (!num2idx.count(y)) continue;
      merge(num2idx[x], num2idx[y]);
    }

    return maxSize;
  }
};

// Use hash set
class Solution2 {
 public:
  int longestConsecutive(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;

    unordered_set<int> numSet(nums.begin(), nums.end());

    auto ans = 0;
    for (auto num : numSet) {
      if (numSet.count(num - 1)) continue;  // not start of a sequence

      auto end = num + 1;
      for (; numSet.count(end); end++);
      ans = max(ans, end - num);
    }

    return ans;
  }
};
