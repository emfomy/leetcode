// Source: https://leetcode.com/problems/non-decreasing-array
// Title: Non-decreasing Array
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array nums with n integers, your task is to check if it could become non-decreasing by modifying at most one element.
//
// We define an array is non-decreasing if nums[i] <= nums[i + 1] holds for every i (0-based) such that (0 <= i <= n - 2).
//
// Example 1:
//
//   Input: nums = [4,2,3]
//   Output: true
//   Explanation: You could modify the first 4 to 1 to get a non-decreasing array.
//
// Example 2:
//
//   Input: nums = [4,2,1]
//   Output: false
//   Explanation: You can't get a non-decreasing array by modify at most one element.
//
// Constraints:
//
//   n == nums.length
//   1 <= n <= 10^4
//   -10^5 <= nums[i] <= 10^5
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import "fmt"

func checkPossibility(nums []int) bool {
	n := len(nums)

	if n <= 2 {
		return true
	}

	modified := false

	for i := 1; i < n; i++ {
		if nums[i-1] <= nums[i] {
			continue
		}

		if modified {
			fmt.Println(nums)
			return false
		}

		if i < 2 || nums[i-2] <= nums[i] {
			nums[i-1] = nums[i] // Remove former number
		} else {
			nums[i] = nums[i-1] // Remove latter number
		}

		modified = true
	}

	fmt.Println(nums)

	return true
}
