// Source: https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array
// Title: Find First and Last Position of Element in Sorted Array
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array of integers `nums` sorted in non-decreasing order, find the starting and ending position of a given `target` value.
//
// If `target` is not found in the array, return `[-1, -1]`.
//
// You mustwrite an algorithm with`O(log n)` runtime complexity.
//
// **Example 1:**
//
// ```
// Input: nums = [5,7,7,8,8,10], target = 8
// Output: [3,4]
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [5,7,7,8,8,10], target = 6
// Output: [-1,-1]
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [], target = 0
// Output: [-1,-1]
// ```
//
// **Constraints:**
//
// - `0 <= nums.length <= 10^5`
// - `-10^9<= nums[i]<= 10^9`
// - `nums` is a non-decreasing array.
// - `-10^9<= target<= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

using namespace std;

// Binary Search (STL)
class Solution {
 public:
  vector<int> searchRange(vector<int>& nums, int target) {
    auto [lo, hi] = equal_range(nums.cbegin(), nums.cend(), target);
    if (lo == hi) return {-1, -1};
    return {int(lo - nums.cbegin()), int(hi - nums.cbegin() - 1)};
  }
};
