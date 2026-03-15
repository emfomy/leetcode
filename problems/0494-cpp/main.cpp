// Source: https://leetcode.com/problems/target-sum
// Title: Target Sum
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `nums` and an integer `target`.
//
// You want to build an **expression** out of nums by adding one of the symbols `'+'` and `'-'` before each integer in nums and then concatenate all the integers.
//
// - For example, if `nums = [2, 1]`, you can add a `'+'` before `2` and a `'-'` before `1` and concatenate them to build the expression `"+2-1"`.
//
// Return the number of different **expressions** that you can build, which evaluates to `target`.
//
// **Example 1:**
//
// ```
// Input: nums = [1,1,1,1,1], target = 3
// Output: 5
// Explanation: There are 5 ways to assign symbols to make the sum of nums be target 3.
// -1 + 1 + 1 + 1 + 1 = 3
// +1 - 1 + 1 + 1 + 1 = 3
// +1 + 1 - 1 + 1 + 1 = 3
// +1 + 1 + 1 - 1 + 1 = 3
// +1 + 1 + 1 + 1 - 1 = 3
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [1], target = 1
// Output: 1
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 20`
// - `0 <= nums[i] <= 1000`
// - `0 <= sum(nums[i]) <= 1000`
// - `-1000 <= target <= 1000`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <numeric>
#include <vector>

using namespace std;

// DP
//
// Loop for the numbers.
// Let DP[i][j] be the number of cases for the first i numbers that sums to j.
// DP[0][0] = 1, DP[0][j] = 0.
// DP[i][j] = DP[i-1][j-nums[i]] + DP[i-1][j+nums[i]]
class Solution {
 public:
  int findTargetSumWays(const vector<int>& nums, const int target) {
    // Total sum
    const int sum = accumulate(nums.cbegin(), nums.cend(), 0);

    // Guard
    if (target < -sum || target > sum) return 0;

    // Initialize the polynomial
    auto prev = vector<int>(4 * sum + 1, 0);  // [-2sum, 2sum] range
    auto curr = vector<int>(4 * sum + 1, 0);  // [-2sum, 2sum] range
    curr[2 * sum] = 1;                        // DP[0] = 1

    // Loop
    for (const int num : nums) {
      swap(curr, prev);
      for (int j = sum; j <= 3 * sum; ++j) {  // loop in [-sum, sum]
        curr[j] = prev[j - num] + prev[j + num];
      }
    }
    return curr[2 * sum + target];
  }
};
