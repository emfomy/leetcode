// Source: https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array
// Title: Find First and Last Position of Element in Sorted Array
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array of integers nums sorted in ascending order, find the starting and ending position of a given target value.
//
// Your algorithm's runtime complexity must be in the order of O(log n).
//
// If the target is not found in the array, return [-1, -1].
//
// Example 1:
//
//   Input: nums = [5,7,7,8,8,10], target = 8
//   Output: [3,4]
//
// Example 2:
//
//   Input: nums = [5,7,7,8,8,10], target = 6
//   Output: [-1,-1]
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> searchRange(vector<int>& nums, int target) {
    if (nums.size() == 0) {
      return {-1, -1};
    }

    auto [lower_it, upper_it] = equal_range(nums.cbegin(), nums.cend(), target);

    if (lower_it != nums.cend() && *lower_it == target && upper_it != nums.cbegin() && *(--upper_it) == target) {
      return {static_cast<int>(lower_it - nums.cbegin()), static_cast<int>(upper_it - nums.cbegin())};
    }
    return {-1, -1};
  }
};
