// Source: https://leetcode.com/problems/move-zeroes/
// Title: Move Zeroes
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer array nums, move all 0's to the end of it while maintaining the relative order of the non-zero elements.
//
// Note that you must do this in-place without making a copy of the array.
//
// Example 1:
//
//   Input: nums = [0,1,0,3,12]
//   Output: [1,3,12,0,0]
//
// Example 2:
//
//   Input: nums = [0]
//   Output: [0]
//
// Constraints:
//
//   1 <= nums.length <= 10^4
//   -2^31 <= nums[i] <= 2^31 - 1
//
// Follow up: Could you minimize the total number of operations done?
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func moveZeroes(nums []int) {
	i := 0

	for _, v := range nums {
		if v != 0 {
			nums[i] = v
			i++
		}
	}

	for ; i < len(nums); i++ {
		nums[i] = 0
	}
}

// Use swap
func moveZeroes2(nums []int) {
	i := 0
	for j := range nums {
		if nums[j] != 0 {
			nums[i], nums[j] = nums[j], nums[i]
			i++
		}
	}
}
