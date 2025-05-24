// Source: https://leetcode.com/problems/zero-array-transformation-i
// Title: Zero Array Transformation I
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `nums` of length `n` and a 2D array `queries`, where `queries[i] = [l_i, r_i]`.
//
// For each `queries[i]`:
//
// - Select a subset of indices within the range `[l_i, r_i]` in `nums`.
// - A **subset** of an array is a selection of elements (possibly none) of the array.
// - Decrement the values at the selected indices by 1.
//
// A **Zero Array** is an array where all elements are equal to 0.
//
// Return `true` if it is possible to transform `nums` into a **Zero Array** after processing all the queries sequentially, otherwise return `false`.
//
// **Example 1:**
//
// ```
// Input: nums = [1,0,1], queries = [[0,2]]
// Output: true
// Explanation:
// - **For i = 0:**
//   - Select the subset of indices as `[0, 2]` and decrement the values at these indices by 1.
//   - The array will become `[0, 0, 0]`, which is a Zero Array.
// ``
//
// **Example 2:**
//
// ```
// Input: nums = [4,3,2,1], queries = [[1,3],[0,2]]
// Output: false
// Explanation:
// - **For i = 0:**
//   - Select the subset of indices as `[1, 2, 3]` and decrement the values at these indices by 1.
//   - The array will become `[4, 2, 1, 0]`.
// - **For i = 1:**
//   - Select the subset of indices as `[0, 1, 2]` and decrement the values at these indices by 1.
//   - The array will become `[3, 1, 0, 0]`, which is not a Zero Array.
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 10^5`
// - `0 <= nums[i] <= 10^5`
// - `1 <= queries.length <= 10^5`
// - `queries[i].length == 2`
// - `0 <= l_i <= r_i < nums.length`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func isZeroArray(nums []int, queries [][]int) bool {
	n := len(nums)
	diffs := make([]int, n+1)

	for _, query := range queries {
		diffs[query[0]]++
		diffs[query[1]+1]--
	}

	val := 0
	for i := range n {
		val += diffs[i]
		if val < nums[i] {
			return false
		}
	}
	return true
}
