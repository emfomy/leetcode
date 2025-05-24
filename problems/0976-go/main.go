// Source: https://leetcode.com/problems/largest-perimeter-triangle
// Title: Largest Perimeter Triangle
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer array nums, return the largest perimeter of a triangle with a non-zero area, formed from three of these lengths. If it is impossible to form any triangle of a non-zero area, return 0.
//
// Example 1:
//
//   Input: nums = [2,1,2]
//   Output: 5
//
// Example 2:
//
//   Input: nums = [1,2,1]
//   Output: 0
//
// Constraints:
//
//   3 <= nums.length <= 10^4
//   1 <= nums[i] <= 10^6
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"sort"
)

func largestPerimeter(nums []int) int {
	// Reverse sort
	sort.Ints(nums)

	res := 0
	for i := len(nums) - 1; i >= 2; i++ {
		// a+b > c && a+c > b && b+c > a
		// However, since a >= b >= c > 0, we only need to check b+c > a
		if nums[i] < nums[i-1]+nums[i-2] {
			res = _max(res, nums[i]+nums[i-1]+nums[i-2])
		}
	}

	return res
}

func _max(a, b int) int {
	if a > b {
		return a
	}
	return b
}
