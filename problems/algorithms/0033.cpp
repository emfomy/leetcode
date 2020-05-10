// Source: https://leetcode.com/problems/search-in-rotated-sorted-array/
// Title: Search in Rotated Sorted Array
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.
//
// (i.e., [0,1,2,4,5,6,7] might become [4,5,6,7,0,1,2]).
//
// You are given a target value to search. If found in the array return its index, otherwise return -1.
//
// You may assume no duplicate exists in the array.
//
// Your algorithm's runtime complexity must be in the order of O(log n).
//
// Example 1:
//
//   Input: nums = [4,5,6,7,0,1,2], target = 0
//   Output: 4
//
// Example 2:
//
//   Input: nums = [4,5,6,7,0,1,2], target = 3
//   Output: -1
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>

class Solution {

 public:
  int search( vector<int>& nums, int target ) {
    if ( nums.size() == 0 ) {
      return -1;
    }

    int base = nums[0];

    auto comp = [base] ( const int a, const int b ) { // True: Less
      if (a < base && b >= base) {
        return false;
      }
      if (a >= base && b < base) {
        return true;
      }
      return (a < b);
    };

    auto it = lower_bound(nums.cbegin(), nums.cend(), target, comp);

    if ( it != nums.cend() && *it == target ) {
      return it - nums.cbegin();
    } else {
      return -1;
    }
  }
};
