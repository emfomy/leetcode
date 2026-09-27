// Source: https://leetcode.com/problems/minimum-operations-to-reduce-x-to-zero
// Title: Minimum Operations to Reduce X to Zero
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `nums` and an integer `x`. In one operation, you can either remove the leftmost or the rightmost element from the array `nums` and subtract its value from `x`. Note that this **modifies** the array for future operations.
//
// Return the **minimum number** of operations to reduce `x` to **exactly** `0` if it is possible, otherwise, return `-1`.
//
// **Example 1:**
//
// ```
// Input: nums = [1,1,4,2,3], x = 5
// Output: 2
// Explanation: The optimal solution is to remove the last two elements to reduce x to zero.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [5,6,7,8,9], x = 4
// Output: -1
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [3,2,20,1,1,3], x = 10
// Output: 5
// Explanation: The optimal solution is to remove the last three elements and the first two elements (5 operations in total) to reduce x to zero.
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 10^5`
// - `1 <= nums[i] <= 10^4`
// - `1 <= x <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <numeric>
#include <vector>

using namespace std;

// Two Pointer
//
// Say the sum of the array is s.
// The problem is equal to find the longest subarray that sub to s-x.
// Loop through all possible starting point,
// and use two pointer to shift the end point.
class Solution {
 public:
  int minOperations(const vector<int>& nums, int x) {
    const int n = nums.size();

    // Sum
    int total = accumulate(nums.cbegin(), nums.cend(), 0);
    int target = total - x;

    // Edge case
    if (target == 0) return n;
    if (target < 0) return -1;

    // Loop, [i, j]
    int i = 0, sum = 0, ans = 0;
    for (int j = 0; j < n; ++j) {
      sum += nums[j];

      while (sum > target) {
        sum -= nums[i++];
      }

      if (sum == target) {
        ans = max(ans, j - i + 1);
      }
    }

    return ans == 0 ? -1 : n - ans;
  }
};
