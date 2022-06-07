// Source: https://leetcode.com/problems/maximum-product-subarray/
// Title: Maximum Product Subarray
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer array nums, find a contiguous non-empty subarray within the array that has the largest product, and return the product.
//
// The test cases are generated so that the answer will fit in a 32-bit integer.
//
// A subarray is a contiguous subsequence of the array.
//
// Example 1:
//
//   Input: nums = [2,3,-2,4]
//   Output: 6
//   Explanation: [2,3] has the largest product 6.
//
// Example 2:
//
//   Input: nums = [-2,0,-1]
//   Output: 0
//   Explanation: The result cannot be 2, because [-2,-1] is not a subarray.
//
// Constraints:
//
//   1 <= nums.length <= 2 * 10^4
//   -10 <= nums[i] <= 10
//   The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func maxProduct(nums []int) int {
	res := nums[0]
	maxEndHere := nums[0]
	minEndHere := nums[0]

	for _, num := range nums[1:] {
		if num < 0 {
			maxEndHere, minEndHere = minEndHere, maxEndHere
		}

		maxEndHere = _max(maxEndHere*num, num)
		minEndHere = _min(minEndHere*num, num)

		res = _max(res, maxEndHere)
	}

	return res
}

func _max(a, b int) int {
	if a > b {
		return a
	}
	return b
}

func _min(a, b int) int {
	if a < b {
		return a
	}
	return b
}
