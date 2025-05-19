// Source: https://leetcode.com/problems/maximum-ascending-subarray-sum
// Title: Maximum Ascending Subarray Sum
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array of positive integers `nums`, return the maximum possible sum of an **ascending** subarray in `nums`.
//
// A subarray is defined as a contiguous sequence of numbers in an array.
//
// A subarray `[nums_l, nums_(l+1), ..., nums_(r-1), nums_r]` is **ascending** if for all `i` where `l <= i < r`, `nums_i < nums_i+1`. Note that a subarray of size `1` is **ascending**.
//
// **Example 1:**
//
// ```
// Input: nums = [10,20,30,5,10,50]
// Output: 65
// Explanation: [5,10,50] is the ascending subarray with the maximum sum of 65.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [10,20,30,40,50]
// Output: 150
// Explanation: [10,20,30,40,50] is the ascending subarray with the maximum sum of 150.
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [12,17,15,13,10,11,12]
// Output: 33
// Explanation: [10,11,12] is the ascending subarray with the maximum sum of 33.
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 100`
// - `1 <= nums[i] <= 100`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func maxAscendingSum(nums []int) int {
	n := len(nums)

	maxSum, subSum := nums[0], nums[0]

	for i := range n - 1 {
		if nums[i+1] <= nums[i] {
			subSum = 0
		}
		subSum += nums[i+1]
		maxSum = max(maxSum, subSum)
	}

	return maxSum
}
