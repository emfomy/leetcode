// Source: https://leetcode.com/problems/find-the-duplicate-number
// Title: Find the Duplicate Number
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array of integers `nums` containing`n + 1` integers where each integer is in the range `[1, n]` inclusive.
//
// There is only **one repeated number** in `nums`, return thisrepeatednumber.
//
// You must solve the problem **without** modifying the array `nums`and using only constant extra space.
//
// **Example 1:**
//
// ```
// Input: nums = [1,3,4,2,2]
// Output: 2
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [3,1,3,4,2]
// Output: 3
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [3,3,3,3,3]
// Output: 3```
//
// **Constraints:**
//
// - `1 <= n <= 10^5`
// - `nums.length == n + 1`
// - `1 <= nums[i] <= n`
// - All the integers in `nums` appear only **once** except for **precisely one integer** which appears **two or more** times.
//
// **Follow up:**
// - How can we prove that at least one duplicate number must exist in `nums`?
// - Can you solve the problem in linear runtime complexity?
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <vector>

using namespace std;

// Hash Map
class Solution {
 public:
  int findDuplicate(vector<int>& nums) {
    int n = nums.size();
    auto visited = vector<bool>(n);
    for (auto num : nums) {
      if (visited[num]) return num;
      visited[num] = true;
    }
    return 0;
  }
};

// Use array sign as hash map
class Solution2 {
 public:
  int findDuplicate(vector<int>& nums) {
    int n = nums.size();
    for (auto i = 0; i < n; ++i) {
      auto num = abs(nums[i]);
      if (nums[num] < 0) return num;
      nums[num] = -abs(nums[num]);
    }
    return 0;
  }
};
