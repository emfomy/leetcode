// Source: https://leetcode.com/problems/largest-divisible-subset
// Title: Largest Divisible Subset
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a set of **distinct** positive integers `nums`, return the largest subset `answer` such that every pair `(answer[i], answer[j])` of elements in this subset satisfies:
//
// - `answer[i] % answer[j] == 0`, or
// - `answer[j] % answer[i] == 0`
//
// If there are multiple solutions, return any of them.
//
// **Example 1:**
//
// ```
// Input: nums = [1,2,3]
// Output: [1,2]
// Explanation: [1,3] is also accepted.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [1,2,4,8]
// Output: [1,2,4,8]
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 1000`
// - `1 <= nums[i] <= 2 * 10^9`
// - All the integers in `nums` are **unique**.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"slices"
)

// Use DP
func largestDivisibleSubset(nums []int) []int {
	n := len(nums)

	slices.Sort(nums)

	sizes := make([]int, n) // prefix subset size
	divisors := make([]int, n)
	for i := range n {
		divisors[i] = -1
	}

	maxSize := 0
	maxIdx := 0
	for i, num := range nums {
		sizes[i] = 0
		for j, divisor := range nums[:i] {
			if num%divisor == 0 && sizes[j] > sizes[i] {
				sizes[i] = sizes[j]
				divisors[i] = j
			}
		}
		sizes[i]++ // include current number

		if sizes[i] > maxSize {
			maxSize = sizes[i]
			maxIdx = i
		}
	}

	res := make([]int, 0, maxSize)
	for i := maxIdx; i != -1; i = divisors[i] {
		res = append(res, nums[i])
	}
	return res
}
