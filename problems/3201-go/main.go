// Source: https://leetcode.com/problems/find-the-maximum-length-of-valid-subsequence-i
// Title: Find the Maximum Length of Valid Subsequence I
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `nums`.
//
// A **subsequence** `sub` of `nums` with length `x` is called **valid** if it satisfies:
//
// - `(sub[0] + sub[1]) % 2 == (sub[1] + sub[2]) % 2 == ... == (sub[x - 2] + sub[x - 1]) % 2.`
//
// A **subsequence** is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
//
// Return the length of the **longest** **valid** subsequence of `nums`.
//
// A **subsequence** is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
//
// **Example 1:**
//
// ```
// Input: nums = [1,2,3,4]
// Output: 4
// Explanation:
// The longest valid subsequence is `[1, 2, 3, 4]`.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [1,2,1,1,2,1,2]
// Output: 6
// Explanation:
// The longest valid subsequence is `[1, 2, 1, 2, 1, 2]`.
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [1,3]
// Output: 2
// Explanation:
// The longest valid subsequence is `[1, 3]`.
// ```
//
// **Constraints:**
//
// - `2 <= nums.length <= 2 * 10^5`
// - `1 <= nums[i] <= 10^7`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// There are two possible valid sequences
// 1. all element has same parity
// 2. alternative parity
func maximumLength(nums []int) int {
	ans := 0

	for parity := range []int{0, 1} {
		// same
		{
			size := 0
			for _, num := range nums {
				if num%2 == parity {
					size++
				}
			}
			ans = max(ans, size)
		}

		// alternative
		{
			size := 0
			for _, num := range nums {
				if num%2 != parity {
					size++
					parity = 1 - parity
				}
			}
			ans = max(ans, size)
		}
	}
	return ans
}
