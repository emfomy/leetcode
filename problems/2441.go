// Source: https://leetcode.com/problems/largest-positive-integer-that-exists-with-its-negative
// Title: Largest Positive Integer That Exists With Its Negative
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer array nums that does not contain any zeros, find the largest positive integer k such that -k also exists in the array.
// Return the positive integer k. If there is no such integer, return -1.
//
// Example 1:
//
//   Input: nums = [-1,2,-3,3]
//   Output: 3
//   Explanation: 3 is the only valid k we can find in the array.
//
// Example 2:
//
//   Input: nums = [-1,10,6,7,-7,1]
//   Output: 7
//   Explanation: Both 1 and 7 have their corresponding negative values in the array. 7 has a larger value.
//
// Example 3:
//
//   Input: nums = [-10,8,6,7,-2,-3]
//   Output: -1
//   Explanation: There is no a single valid k, we return -1.
//
// Constraints:
//
//   1 <= nums.length <= 1000
//   -1000 <= nums[i] <= 1000
//   nums[i] != 0
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

func findMaxK(nums []int) int {
	pos := make([]bool, 1001)
	neg := make([]bool, 1001)

	for _, n := range nums {
		if n >= 0 {
			pos[n] = true
		}
		if n <= 0 {
			neg[-n] = true
		}
	}

	for i := 1000; i >= 0; i-- {
		if pos[i] && neg[i] {
			return i
		}
	}
	return -1
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

type void struct{}

func findMaxK2(nums []int) int {
	set := make(map[int]void, len(nums))

	for _, n := range nums {
		if n <= 0 {
			set[n] = void{}
		}
	}

	res := -1
	for _, n := range nums {
		if _, ok := set[-n]; ok {
			res = max(res, n)
		}
	}

	return res
}
