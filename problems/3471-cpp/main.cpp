// Source: https://leetcode.com/problems/find-the-largest-almost-missing-integer
// Title: Find the Largest Almost Missing Integer
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `nums` and an integer `k`.
//
// An integer `x` is **almost missing** from `nums` if `x` appears in exactly one subarray of size `k` within `nums`.
//
// Return the **largest** **almost missing** integer from `nums`. If no such integer exists, return `-1`.
// A **subarray** is a contiguous sequence of elements within an array.
//
// **Example 1:**
//
// ```
// Input: nums = [3,9,2,1,7], k = 3
// Output: 7
// Explanation:
// - 1 appears in 2 subarrays of size 3: `[9, 2, 1]` and `[2, 1, 7]`.
// - 2 appears in 3 subarrays of size 3: `[3, 9, 2]`, `[9, 2, 1]`, `[2, 1, 7]`.
// - 3 appears in 1 subarray of size 3: `[3, 9, 2]`.
// - 7 appears in 1 subarray of size 3: `[2, 1, 7]`.
// - 9 appears in 2 subarrays of size 3: `[3, 9, 2]`, and `[9, 2, 1]`.
// We return 7 since it is the largest integer that appears in exactly one subarray of size `k`.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [3,9,7,2,1,7], k = 4
// Output: 3
// Explanation:
// - 1 appears in 2 subarrays of size 4: `[9, 7, 2, 1]`, `[7, 2, 1, 7]`.
// - 2 appears in 3 subarrays of size 4: `[3, 9, 7, 2]`, `[9, 7, 2, 1]`, `[7, 2, 1, 7]`.
// - 3 appears in 1 subarray of size 4: `[3, 9, 7, 2]`.
// - 7 appears in 3 subarrays of size 4: `[3, 9, 7, 2]`, `[9, 7, 2, 1]`, `[7, 2, 1, 7]`.
// - 9 appears in 2 subarrays of size 4: `[3, 9, 7, 2]`, `[9, 7, 2, 1]`.
// We return 3 since it is the largest and only integer that appears in exactly one subarray of size `k`.
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [0,0], k = 1
// Output: -1
// Explanation:
// There is no integer that appears in only one subarray of size 1.
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 50`
// - `0 <= nums[i] <= 50`
// - `1 <= k <= nums.length`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

using namespace std;

// If k = n, then all number are almost missing (there are only one subarray).
// If k = 1, then all the non-duplicated number are almost missing.
// Otherwise, only the first and the last number can be almost missing.
class Solution {
  static constexpr int maxNum = 50;

 public:
  int largestInteger(const vector<int>& nums, int k) {
    // Edge case
    if (k == nums.size()) {
      return *max_element(nums.cbegin(), nums.cend());
    }

    // Compute frequency
    auto freq = vector<int>(maxNum + 1);
    for (int num : nums) ++freq[num];

    // Edge case
    if (k == 1) {
      for (int num = maxNum; num >= 0; --num) {
        if (freq[num] == 1) return num;
      }
      return -1;
    }

    // Normal cases
    int ans = -1;
    if (int num = nums.front(); freq[num] == 1) {
      ans = max(ans, num);
    }
    if (int num = nums.back(); freq[num] == 1) {
      ans = max(ans, num);
    }
    return ans;
  }
};
