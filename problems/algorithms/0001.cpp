// Source: https://leetcode.com/problems/two-sum/
// Title: Two Sum
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array of integers, return indices of the two numbers such that they add up to a specific target.
//
// You may assume that each input would have exactly one solution, and you may not use the same element twice.
//
// Example:
//
//   Given nums = [2, 7, 11, 15], target = 9,
//
//   Because nums[0] + nums[1] = 2 + 7 = 9,
//   return [0, 1].
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Solution {
 public:
  vector<int> twoSum( vector<int>& nums, int target ) {
    const int n = nums.size();
    unordered_map<int, int> d;
    for ( auto i = 0; i < n; ++i ) {
      const auto num = nums[i];
      if ( d.count(num) ) {
        return {d[num], i };
      }
      d[target-num] = i;
    }
    return {};
  }
};
