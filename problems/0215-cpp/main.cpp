// Source: https://leetcode.com/problems/kth-largest-element-in-an-array
// Title: Kth Largest Element in an Array
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer array nums and an integer k, return the kth largest element in the array.
//
// Note that it is the kth largest element in the sorted order, not the kth distinct element.
//
// Example 1:
//
//   Input: nums = [3,2,1,5,6,4], k = 2
//   Output: 5
//
// Example 2:
//
//   Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
//   Output: 4
//
// Constraints:
//
// 1 <= k <= nums.length <= 10^4
// -104 <= nums[i] <= 10^4
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <functional>
#include <vector>

using namespace std;

class Solution {
 public:
  int findKthLargest(vector<int>& nums, int k) {
    k--;
    nth_element(nums.begin(), nums.begin() + k, nums.end(), greater<int>{});
    return nums[k];
  }
};
