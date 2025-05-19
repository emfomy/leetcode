// Source: https://leetcode.com/problems/sort-colors
// Title: Sort Colors
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array `nums` with `n` objects colored red, white, or blue, sort them **in-place** so that objects of the same color are adjacent, with the colors in the order red, white, and blue.
//
// We will use the integers `0`, `1`, and `2` to represent the color red, white, and blue, respectively.
//
// You must solve this problem without using the library's sort function.
//
// **Example 1:**
//
// ```
// Input: nums = [2,0,2,1,1,0]
// Output: [0,0,1,1,2,2]
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [2,0,1]
// Output: [0,1,2]
// ```
//
// **Constraints:**
//
// - `n == nums.length`
// - `1 <= n <= 300`
// - `nums[i]` is either `0`, `1`, or `2`.
//
// **Follow up:** Could you come up with a one-pass algorithm using only constant extra space?
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"slices"
)

// Use sort
func sortColors(nums []int) {
	slices.Sort(nums)
}

// Use two pointers
func sortColors2(nums []int) {
	n := len(nums)
	left, curr, right := 0, 0, n
	for curr < right {
		switch nums[curr] {
		case 0: // swap left
			nums[curr], nums[left] = nums[left], nums[curr]
			curr++
			left++
		case 1: // nothing
			curr++
		case 2: // swap right
			right--
			nums[curr], nums[right] = nums[right], nums[curr]
		}
	}
}
