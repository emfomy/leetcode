// Source: https://leetcode.com/problems/sort-colors
// Title: Sort Colors
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array nums with n objects colored red, white, or blue, sort them in-place so that objects of the same color are adjacent, with the colors in the order red, white, and blue.
//
// Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.
//
// Follow up:
//
//   Could you solve this problem without using the library's sort function?
//   Could you come up with a one-pass algorithm using only O(1) constant space?
//
// Example 1:
//
//   Input: nums = [2,0,2,1,1,0]
//   Output: [0,0,1,1,2,2]
//
// Example 2:
//
//   Input: nums = [2,0,1]
//   Output: [0,1,2]
//
// Example 3:
//
//   Input: nums = [0]
//   Output: [0]
//
// Example 4:
//
//   Input: nums = [1]
//   Output: [1]
//
// Constraints:
//
//   n == nums.length
//   1 <= n <= 300
//   nums[i] is 0, 1, or 2.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

const (
	RED   = 0
	WHITE = 1
	BLUE  = 2
)

// Use two pointers
func sortColors(nums []int) {
	n := len(nums)
	red_ptr := 0
	blue_ptr := n - 1

	curr_ptr := 0
	for curr_ptr <= blue_ptr {
		switch nums[curr_ptr] {
		case RED:
			nums[red_ptr], nums[curr_ptr] = nums[curr_ptr], nums[red_ptr]
			curr_ptr++
			red_ptr++
		case WHITE:
			curr_ptr++
		case BLUE:
			nums[blue_ptr], nums[curr_ptr] = nums[curr_ptr], nums[blue_ptr]
			blue_ptr--
		}
	}
}

// Use counter
func sortColors2(nums []int) {
	counts := [3]int{}
	for _, color := range nums {
		counts[color]++
	}

	j := 0
	for color, count := range counts {
		for i := 0; i < count; i++ {
			nums[j] = color
			j++
		}
	}
}
