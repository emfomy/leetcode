// Source: https://leetcode.com/problems/maximum-length-of-subarray-with-positive-product
// Title: Maximum Length of Subarray With Positive Product
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array of integers nums, find the maximum length of a subarray where the product of all its elements is positive.
//
// A subarray of an array is a consecutive sequence of zero or more values taken out of that array.
//
// Return the maximum length of a subarray with positive product.
//
// Example 1:
//
//   Input: nums = [1,-2,-3,4]
//   Output: 4
//   Explanation: The array nums already has a positive product of 24.
//
// Example 2:
//
//   Input: nums = [0,1,-2,-3,-4]
//   Output: 3
//   Explanation:
//     The longest subarray with positive product is [1,-2,-3] which has a product of 6.
//     Notice that we cannot include 0 in the subarray since that'll make the product 0 which is not positive.
//
// Example 3:
//
//   Input: nums = [-1,-2,-3,0,1]
//   Output: 2
//   Explanation: The longest subarray with positive product is [-1,-2] or [-2,-3].
//
// Constraints:
//
//   1 <= nums.length <= 10^5
//   -10^9 <= nums[i] <= 10^9
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func getMaxLen(nums []int) int {
	res := 0
	posLen := 0
	negLen := 0

	for _, num := range nums {
		if num == 0 {
			posLen, negLen = 0, 0
			continue
		}

		posLen++
		if negLen > 0 {
			negLen++
		}
		if num < 0 {
			posLen, negLen = negLen, posLen
		}

		res = _max(res, posLen)
	}

	return res
}

func _max(a, b int) int {
	if a > b {
		return a
	}
	return b
}
