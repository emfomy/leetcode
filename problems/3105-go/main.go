// Source: https://leetcode.com/problems/longest-strictly-increasing-or-strictly-decreasing-subarray
// Title: Longest Strictly Increasing or Strictly Decreasing Subarray
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an array of integers `nums`. Return the length of the **longest** subarray of `nums` which is either **strictly increasing** or **strictly decreasing**.

// A **subarray** is a contiguous **non-empty** sequence of elements within an array.

// An array is said to be **strictly increasing** if each element is strictly greater than its previous one (if exists).

// An array is said to be **strictly decreasing** if each element is strictly smaller than its previous one (if exists).

// **Example 1:**

// ```
// Input: nums = [1,4,3,3,2]
// Output: 2
// Explanation:
// The strictly increasing subarrays of `nums` are `[1]`, `[2]`, `[3]`, `[3]`, `[4]`, and `[1,4]`.
// The strictly decreasing subarrays of `nums` are `[1]`, `[2]`, `[3]`, `[3]`, `[4]`, `[3,2]`, and `[4,3]`.
// Hence, we return `2`.
// ```

// **Example 2:**

// ```
// Input: nums = [3,3,3,3]
// Output: 1
// Explanation:
// The strictly increasing subarrays of `nums` are `[3]`, `[3]`, `[3]`, and `[3]`.
// The strictly decreasing subarrays of `nums` are `[3]`, `[3]`, `[3]`, and `[3]`.
// Hence, we return `1`.
// ```

// **Example 3:**

// ```
// Input: nums = [3,2,1]
// Output: 3
// Explanation:
// The strictly increasing subarrays of `nums` are `[3]`, `[2]`, and `[1]`.
// The strictly decreasing subarrays of `nums` are `[3]`, `[2]`, `[1]`, `[3,2]`, `[2,1]`, and `[3,2,1]`.
// Hence, we return `3`.
// ```

// **Constraints:**

// - `1 <= nums.length <= 50`
// - `1 <= nums[i] <= 50`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func longestMonotonicSubarray(nums []int) int {
	incLen, decLen, maxLen := 1, 1, 1
	n := len(nums)

	for i := range n - 1 {
		if nums[i+1] > nums[i] {
			incLen++
		} else {
			incLen = 1
		}
		if nums[i+1] < nums[i] {
			decLen++
		} else {
			decLen = 1
		}

		maxLen = max(maxLen, incLen, decLen)
	}
	return maxLen
}
