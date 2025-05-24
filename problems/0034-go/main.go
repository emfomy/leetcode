// Source: https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array
// Title: Find First and Last Position of Element in Sorted Array
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array of integers nums sorted in non-decreasing order, find the starting and ending position of a given target value.
//
// If target is not found in the array, return [-1, -1].
//
// You must write an algorithm with O(log n) runtime complexity.
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
// Example 3:
//
//   Input: nums = [], target = 0
//   Output: [-1,-1]
//
// Constraints:
//
//   0 <= nums.length <= 10^5
//   -10^9 <= nums[i] <= 10^9
//   nums is a non-decreasing array.
//   -10^9 <= target <= 10^9
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"sort"
)

func searchRange(nums []int, target int) []int {
	rightIdx := sort.SearchInts(nums, target+1)
	if rightIdx == 0 || nums[rightIdx-1] != target {
		return []int{-1, -1}
	}

	leftIdx := sort.SearchInts(nums[:rightIdx], target)

	return []int{leftIdx, rightIdx - 1}
}
