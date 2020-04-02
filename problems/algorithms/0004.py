# Source: https://leetcode.com/problems/median-of-two-sorted-arrays/
# Title: Median of Two Sorted Arrays
# Difficulty: Hard
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# There are two sorted arrays nums1 and nums2 of size m and n respectively.
#
# Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).
#
# You may assume nums1 and nums2 cannot be both empty.
#
# Example 1:
#
#   nums1 = [1, 3]
#   nums2 = [2]
#
#   The median is 2.0
#
# Example 2:
#
#   nums1 = [1, 2]
#   nums2 = [3, 4]
#
#   The median is (2 + 3)/2 = 2.5
#
################################################################################################################################

class Solution:
    def findMedianSortedArrays(self, nums1: List[int], nums2: List[int]) -> float:
        nums1 += nums2
        nums1.sort()
        n = len(nums1)
        return (nums1[(n-1)//2] + nums1[n//2])/2
