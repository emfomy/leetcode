// Source: https://leetcode.com/problems/zero-array-transformation-ii
// Title: Zero Array Transformation II
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `nums` of length `n` and a 2D array `queries` where `queries[i] = [l_i, r_i, val_i]`.
//
// Each `queries[i]` represents the following action on `nums`:
//
// - Decrement the value at each index in the range `[l_i, r_i]` in `nums` by **at most** `val_i`.
// - The amount by which each value is decremented can be chosen **independently** for each index.
//
// A **Zero Array** is an array with all its elements equal to 0.
//
// Return the **minimum** possible **non-negative** value of `k`, such that after processing the first `k` queries in **sequence**, `nums` becomes a **Zero Array**. If no such `k` exists, return -1.
//
// **Example 1:**
//
// ```
// Input: nums = [2,0,2], queries = [[0,2,1],[0,2,1],[1,1,3]]
// Output: 2
// Explanation:
// - **For i = 0 (l = 0, r = 2, val = 1):**
//   - Decrement values at indices `[0, 1, 2]` by `[1, 0, 1]` respectively.
//   - The array will become `[1, 0, 1]`.
// - **For i = 1 (l = 0, r = 2, val = 1):**
//   - Decrement values at indices `[0, 1, 2]` by `[1, 0, 1]` respectively.
//   - The array will become `[0, 0, 0]`, which is a Zero Array. Therefore, the minimum value of `k` is 2.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [4,3,2,1], queries = [[1,3,2],[0,2,1]]
// Output: -1
// Explanation:
// - **For i = 0 (l = 1, r = 3, val = 2):**
//   - Decrement values at indices `[1, 2, 3]` by `[2, 2, 1]` respectively.
//   - The array will become `[4, 1, 0, 0]`.
// - **For i = 1 (l = 0, r = 2, val = 1):**
//   - Decrement values at indices `[0, 1, 2]` by `[1, 1, 0]` respectively.
//   - The array will become `[3, 0, 0, 0]`, which is not a Zero Array.
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 10^5`
// - `0 <= nums[i] <= 5 * 10^5`
// - `1 <= queries.length <= 10^5`
// - `queries[i].length == 3`
// - `0 <= l_i <= r_i < nums.length`
// - `1 <= val_i <= 5`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// Use binary search on queries
func minZeroArray(nums []int, queries [][]int) int {
	n := len(nums)
	m := len(queries)
	diffs := make([]int, n+1)

	// Binary Search
	curr := 0
	lo, hi := 0, m+1
	for lo < hi {
		mid := (lo + hi) / 2
		applyQueries(curr, mid, diffs, queries)
		curr = mid
		if isZeroArray(diffs, nums) {
			hi = mid
		} else {
			lo = mid + 1
		}
	}

	if lo > m {
		return -1
	}
	return lo
}

func applyQueries(from, to int, diffs []int, queries [][]int) {
	if from == to {
		return
	}

	if from < to {
		for i := from; i < to; i++ {
			l, r, val := queries[i][0], queries[i][1], queries[i][2]
			diffs[l] += val
			diffs[r+1] -= val
		}
	} else {
		for i := from - 1; i >= to; i-- {
			l, r, val := queries[i][0], queries[i][1], queries[i][2]
			diffs[l] -= val
			diffs[r+1] += val
		}
	}
}

func isZeroArray(diffs []int, nums []int) bool {
	n := len(nums)
	val := 0
	for i := range n {
		val += diffs[i]
		if nums[i] > val {
			return false
		}
	}
	return true
}
