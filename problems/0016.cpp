// Source: https://leetcode.com/problems/3sum-closest
// Title: 3Sum Closest
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer array `nums` of length `n` and an integer `target`, find three integers at **distinct indices** in `nums` such that the sum is closest to `target`.
//
// Return the sum of the three integers.
//
// You may assume that each input would have exactly one solution.
//
// **Example 1:**
//
// ```
// Input: nums = [-1,2,1,-4], target = 1
// Output: 2
// Explanation: The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [0,0,0], target = 1
// Output: 0
// Explanation: The sum that is closest to the target is 0. (0 + 0 + 0 = 0).
// ```
//
// **Constraints:**
//
// - `3 <= nums.length <= 500`
// - `-1000 <= nums[i] <= 1000`
// - `-10^4 <= target <= 10^4`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdlib>
#include <vector>

using namespace std;

// Sort + Two Pointer
//
// First sort the numbers.
// Say i < j < k. Loop for all k.
// Use two pointer idea on i & j to find the nearest sum.
class Solution {
 public:
  int threeSumClosest(vector<int>& nums, int target) {
    auto n = nums.size();

    // Sort
    sort(nums.begin(), nums.end());

    // Loop
    auto ans = nums[0] + nums[1] + nums[2];
    auto ansDiff = abs(ans - target);
    for (auto k = 3; k < n; ++k) {
      // Two Pointer
      auto i = 0, j = k - 1;
      while (i < j) {
        auto sum = nums[i] + nums[j] + nums[k];
        if (sum == target) return sum;
        if (sum > target) {
          --j;
        } else {
          ++i;
        }

        auto sumDiff = abs(sum - target);
        if (ansDiff > sumDiff) {
          ansDiff = sumDiff;
          ans = sum;
        }
      }
    }

    return ans;
  }
};
