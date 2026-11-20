// Source: https://leetcode.com/problems/minimum-distance-between-three-equal-elements-i
// Title: Minimum Distance Between Three Equal Elements I
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `nums`.
//
// A tuple `(i, j, k)` of 3 **distinct** indices is **good** if `nums[i] == nums[j] == nums[k]`.
//
// The **distance** of a **good** tuple is `abs(i - j) + abs(j - k) + abs(k - i)`, where `abs(x)` denotes the **absolute value** of `x`.
//
// Return an integer denoting the **minimum** possible **distance** of a **good** tuple. If no **good** tuples exist, return `-1`.
//
// **Example 1:**
//
// ```
// Input: nums = [1,2,1,1,3]
// Output: 6
// Explanation:
// The minimum distance is achieved by the good tuple `(0, 2, 3)`.
// `(0, 2, 3)` is a good tuple because `nums[0] == nums[2] == nums[3] == 1`. Its distance is `abs(0 - 2) + abs(2 - 3) + abs(3 - 0) = 2 + 1 + 3 = 6`.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [1,1,2,3,2,1,2]
// Output: 8
// Explanation:
// The minimum distance is achieved by the good tuple `(2, 4, 6)`.
// `(2, 4, 6)` is a good tuple because `nums[2] == nums[4] == nums[6] == 2`. Its distance is `abs(2 - 4) + abs(4 - 6) + abs(6 - 2) = 2 + 2 + 4 = 8`.
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [1]
// Output: -1
// Explanation:
// There are no good tuples. Therefore, the answer is -1.
// ```
//
// **Constraints:**
//
// - `1 <= n == nums.length <= 100`
// - `1 <= nums[i] <= n`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <climits>
#include <unordered_map>
#include <vector>

using namespace std;

// Hash Map
//
// Group index by value.
//
// For i < j < k, abs(i-j) + abs(j-k) + abs(k-i) = 2(k-i).
// We need to find the minimal difference by any pair the separate by one element.
class Solution {
 public:
  int minimumDistance(const vector<int>& nums) {
    const int n = nums.size();

    // Group
    auto groups = unordered_map<int, vector<int>>();
    for (int i = 0; i < n; ++i) {
      groups[nums[i]].push_back(i);
    }

    // Find min value
    int minDiff = INT_MAX;
    for (const auto [_, idxs] : groups) {
      for (int i = 2; i < idxs.size(); ++i) {
        minDiff = min(minDiff, 2 * (idxs[i] - idxs[i - 2]));
      }
    }

    return minDiff == INT_MAX ? -1 : minDiff;
  }
};

// Hash Map
//
// We only keep last two index per value.
class Solution2 {
  struct Data {
    int prev2 = INT_MIN;
    int prev1 = INT_MIN;

    int update(int x) {
      int ret = prev2;
      prev2 = prev1;
      prev1 = x;
      return ret;
    }
  };

 public:
  int minimumDistance(const vector<int>& nums) {
    const int n = nums.size();

    // Loop
    int minDiff = INT_MAX;
    auto groups = unordered_map<int, Data>();
    for (int idx = 0; idx < n; ++idx) {
      int prevIdx = groups[nums[idx]].update(idx);
      if (prevIdx != INT_MIN) {
        minDiff = min(minDiff, 2 * (idx - prevIdx));
      }
    }

    return minDiff == INT_MAX ? -1 : minDiff;
  }
};
