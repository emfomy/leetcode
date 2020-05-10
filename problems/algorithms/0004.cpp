// Source: https://leetcode.com/problems/median-of-two-sorted-arrays/
// Title: Median of Two Sorted Arrays
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There are two sorted arrays nums1 and nums2 of size m and n respectively.
//
// Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).
//
// You may assume nums1 and nums2 cannot be both empty.
//
// Example 1:
//
//   nums1 = [1, 3]
//   nums2 = [2]
//
//   The median is 2.0
//
// Example 2:
//
//   nums1 = [1, 2]
//   nums2 = [3, 4]
//
//   The median is (2 + 3)/2 = 2.5
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Solution {
 public:
  double findMedianSortedArrays( vector<int>& nums1, vector<int>& nums2 ) {
    auto len = nums1.size() + nums2.size();
    vector<int> nums(len);
    merge(nums1.cbegin(), nums1.cend(), nums2.cbegin(), nums2.cend(), nums.begin());
    return double(nums[(len-1)/2] + nums[(len)/2]) / 2;
  }
};
