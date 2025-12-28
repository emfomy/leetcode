// Source: https://leetcode.com/problems/check-if-all-1s-are-at-least-length-k-places-away
// Title: Check If All 1's Are at Least Length K Places Away
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an binary array `nums` and an integer `k`, return `true` if all `1`'s are at least `k` places away from each other, otherwise return `false`.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2020/04/15/sample_1_1791.png
//
// ```
// Input: nums = [1,0,0,0,1,0,0,1], k = 2
// Output: true
// Explanation: Each of the 1s are at least 2 places away from each other.
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2020/04/15/sample_2_1791.png
//
// ```
// Input: nums = [1,0,0,1,0,1], k = 2
// Output: false
// Explanation: The second 1 and third 1 are only one apart from each other.
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 10^5`
// - `0 <= k <= nums.length`
// - `nums[i]` is `0` or `1`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

class Solution {
 public:
  bool kLengthApart(vector<int>& nums, int k) {
    int n = nums.size();
    auto prevIdx = -k - 1;
    for (auto i = 0; i < n; ++i) {
      if (nums[i] == 1) {
        if (i - prevIdx <= k) return false;
        prevIdx = i;
      }
    }
    return true;
  }
};
