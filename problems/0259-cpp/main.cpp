// Source: https://leetcode.com/problems/3sum-smaller
// Title: 3Sum Smaller
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array of `n` integers `nums` and an integer`target`, find the number of index triplets `i`, `j`, `k` with `0 <= i < j < k < n` that satisfy the condition `nums[i] + nums[j] + nums[k] < target`.
//
// **Example 1:**
//
// ```
// Input: nums = [-2,0,1,3], target = 2
// Output: 2
// Explanation: Because there are two triplets which sums are less than 2:
// [-2,0,1]
// [-2,0,3]
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [], target = 0
// Output: 0
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [0], target = 0
// Output: 0
// ```
//
// **Constraints:**
//
// - `n == nums.length`
// - `0 <= n <= 3500`
// - `-100 <= nums[i] <= 100`
// - `-100 <= target <= 100`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

using namespace std;

// Sort + Two Pointer
//
// For each i, use two pointer to find the maximum k for each j.
class Solution {
 public:
  int threeSumSmaller(vector<int>& nums, int target) {
    int n = nums.size();

    // Sort
    sort(nums.begin(), nums.end());

    // Loop
    auto ans = 0;
    for (auto i = 0; i < n; ++i) {
      auto k = n - 1;
      for (auto j = i + 1; j < n; ++j) {
        // Ensure nums[i] + nums[j] + nums[k] < target
        while (j < k && nums[i] + nums[j] + nums[k] >= target) --k;
        if (j >= k) break;
        ans += k - j;
      }
    }

    return ans;
  }
};
