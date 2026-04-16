// Source: https://leetcode.com/problems/missing-ranges
// Title: Missing Ranges
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an inclusive range `[lower, upper]` and a **sorted unique** integer array `nums`, where all elements are within the inclusive range.
//
// A number `x` is considered **missing** if `x` is in the range `[lower, upper]` and `x` is not in `nums`.
//
// Return the **shortest sorted** list of ranges that **exactly covers all the missing numbers**. That is, no element of `nums` is included in any of the ranges, and each missing number is covered by one of the ranges.
//
// **Example 1:**
//
// ```
// Input: nums = [0,1,3,50,75], lower = 0, upper = 99
// Output: [[2,2],[4,49],[51,74],[76,99]]
// Explanation: The ranges are:
// [2,2]
// [4,49]
// [51,74]
// [76,99]
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [-1], lower = -1, upper = -1
// Output: []
// Explanation: There are no missing ranges since there are no missing numbers.
// ```
//
// **Constraints:**
//
// - `-10^9 <= lower <= upper <= 10^9`
// - `0 <= nums.length <= 100`
// - `lower <= nums[i] <= upper`
// - All the values of `nums` are **unique**.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// Single Pass
class Solution {
 public:
  vector<vector<int>> findMissingRanges(const vector<int>& nums, int lower, int upper) {
    const int n = nums.size();

    // Loop
    auto ans = vector<vector<int>>();
    for (int i = 0; i <= n; ++i) {
      int rangeStart = (i == 0) ? lower : max(nums[i - 1] + 1, lower);
      int rangeEnd = (i == n) ? upper : min(nums[i] - 1, upper);

      // Range too left
      if (rangeEnd < lower) continue;

      // Range too right
      if (rangeStart > upper) break;

      // Empty range
      if (rangeStart > rangeEnd) continue;

      // Valid range
      ans.push_back({rangeStart, rangeEnd});
    }

    return ans;
  }
};
