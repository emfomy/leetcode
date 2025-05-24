// Source: https://leetcode.com/problems/minimum-moves-to-equal-array-elements-ii
// Title: Minimum Moves to Equal Array Elements II
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer array nums of size n, return the minimum number of moves required to make all array elements equal.
//
// In one move, you can increment or decrement an element of the array by 1.
//
// Test cases are designed so that the answer will fit in a 32-bit integer.
//
// Example 1:
//
//   Input: nums = [1,2,3]
//   Output: 2
//   Explanation:
//   Only two moves are needed (remember each move increments or decrements one element):
//   [1,2,3]  =>  [2,2,3]  =>  [2,2,2]
//
// Example 2:
//
//   Input: nums = [1,10,2,9]
//   Output: 16
//
// Constraints:
//
//   n == nums.length
//   1 <= nums.length <= 10^5
//   -10^9 <= nums[i] <= 10^9
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"sort"
)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// We want to move everything to the medium.
func minMoves2(nums []int) int {
	n := len(nums)

	sort.Ints(nums)
	medium := nums[n/2]

	res := 0
	for _, v := range nums {
		res += _abs(v - medium)
	}

	return res
}

func _abs(v int) int {
	if v >= 0 {
		return v
	}
	return -v
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// We want to move everything to the medium.
// Let M be the medium.
// Result = (M-nums[0]) + (M-nums[1]) + ... + (nums[n-2] - M)+ (nums[n-1] - M)
//
//	= (nums[n-1] - nums[0]) + (nums[n-2] - nums[1]) + ...
func minMoves2a(nums []int) int {
	n := len(nums)

	sort.Ints(nums)

	i := 0
	j := n - 1

	res := 0
	for i < j {
		res += nums[j] - nums[i]
		i++
		j--
	}

	return res
}
