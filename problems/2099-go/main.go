// Source: https://leetcode.com/problems/find-subsequence-of-length-k-with-the-largest-sum
// Title: Find Subsequence of Length K With the Largest Sum
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `nums` and an integer `k`. You want to find a **subsequence **of `nums` of length `k` that has the **largest** sum.
//
// Return **any** such subsequence as an integer array of length `k`.
//
// A **subsequence** is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
//
// **Example 1:**
//
// ```
// Input: nums = [2,1,3,3], k = 2
// Output: [3,3]
// Explanation:
// The subsequence has the largest sum of 3 + 3 = 6.```
//
// **Example 2:**
//
// ```
// Input: nums = [-1,-2,3,4], k = 3
// Output: [-1,3,4]
// Explanation:
// The subsequence has the largest sum of -1 + 3 + 4 = 6.
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [3,4,3,3], k = 2
// Output: [3,4]
// Explanation:
// The subsequence has the largest sum of 3 + 4 = 7.
// Another possible subsequence is [4, 3].
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 1000`
// - `-10^5<= nums[i] <= 10^5`
// - `1 <= k <= nums.length`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"slices"
)

// Just find top-k numbers
func maxSubsequence(nums []int, k int) []int {
	n := len(nums)

	// Pairs
	pairs := make([][2]int, n) // (index, value) pairs
	for i, num := range nums {
		pairs[i] = [2]int{i, num}
	}

	// Sort by value
	slices.SortFunc(pairs, func(a, b [2]int) int {
		return b[1] - a[1]
	})

	// Top k values
	pairs = pairs[:k]

	// Sort by index
	slices.SortFunc(pairs, func(a, b [2]int) int {
		return a[0] - b[0]
	})

	// Answer
	ans := make([]int, k)
	for i, pair := range pairs {
		ans[i] = pair[1]
	}
	return ans
}
