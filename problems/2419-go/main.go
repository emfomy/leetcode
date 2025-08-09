// Source: https://leetcode.com/problems/longest-subarray-with-maximum-bitwise-and
// Title: Longest Subarray With Maximum Bitwise AND
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `nums` of size `n`.
//
// Consider a **non-empty** subarray from `nums` that has the **maximum** possible **bitwise AND**.
//
// - In other words, let `k` be the maximum value of the bitwise AND of **any** subarray of `nums`. Then, only subarrays with a bitwise AND equal to `k` should be considered.
//
// Return the length of the **longest** such subarray.
//
// The bitwise AND of an array is the bitwise AND of all the numbers in it.
//
// A **subarray** is a contiguous sequence of elements within an array.
//
// **Example 1:**
//
// ```
// Input: nums = [1,2,3,3,2,2]
// Output: 2
// Explanation:
// The maximum possible bitwise AND of a subarray is 3.
// The longest subarray with that value is [3,3], so we return 2.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [1,2,3,4]
// Output: 1
// Explanation:
// The maximum possible bitwise AND of a subarray is 4.
// The longest subarray with that value is [4], so we return 1.
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 10^5`
// - `1 <= nums[i] <= 10^6`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import "slices"

// The AND operation will only reduce the result.
// The problem is the same as finding the longest subarray with only the maximum number.
func longestSubarray(nums []int) int {
	maxNum := slices.Max(nums)
	ans := 0
	size := 0
	for _, num := range nums {
		if num == maxNum {
			size++
			ans = max(ans, size)
		} else {
			size = 0
		}
	}
	return ans
}
