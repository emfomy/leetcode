// Source: https://leetcode.com/problems/contains-duplicate-ii
// Title: Contains Duplicate II
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer array `nums` and an integer `k`, return `true` if there are two **distinct indices** `i` and `j` in the array such that `nums[i] == nums[j]` and `abs(i - j) <= k`.
//
// **Example 1:**
//
// ```
// Input: nums = [1,2,3,1], k = 3
// Output: true
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [1,0,1,1], k = 1
// Output: true
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [1,2,3,1,2,3], k = 2
// Output: false
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 10^5`
// - `-10^9 <= nums[i] <= 10^9`
// - `0 <= k <= 10^5`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <unordered_map>
#include <vector>

using namespace std;

// Use sliding window + hash set
class Solution {
 public:
  bool containsNearbyDuplicate(vector<int>& nums, int k) {
    if (k == 0) return false;

    int n = nums.size();

    unordered_map<int, bool> numSet;
    for (auto idx = 0; idx < n; idx++) {
      if (numSet[nums[idx]]) return true;
      numSet[nums[idx]] = true;
      if (idx - k >= 0) numSet[nums[idx - k]] = false;
    }

    return false;
  }
};
