// Source: https://leetcode.com/problems/minimum-recolors-to-get-k-consecutive-black-blocks
// Title: Minimum Recolors to Get K Consecutive Black Blocks
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a **0-indexed** string `blocks` of length `n`, where `blocks[i]` is either `'W'` or `'B'`, representing the color of the `i^th` block. The characters `'W'` and `'B'` denote the colors white and black, respectively.
//
// You are also given an integer `k`, which is the desired number of **consecutive** black blocks.
//
// In one operation, you can **recolor** a white block such that it becomes a black block.
//
// Return the **minimum** number of operations needed such that there is at least **one** occurrence of `k` consecutive black blocks.
//
// **Example 1:**
//
// ```
// Input: blocks = "WBBWWBBWBW", k = 7
// Output: 3
// Explanation:
// One way to achieve 7 consecutive black blocks is to recolor the 0th, 3rd, and 4th blocks
// so that blocks = "BBBBBBBWBW".
// It can be shown that there is no way to achieve 7 consecutive black blocks in less than 3 operations.
// Therefore, we return 3.
// ```
//
// **Example 2:**
//
// ```
// Input: blocks = "WBWBBBW", k = 2
// Output: 0
// Explanation:
// No changes need to be made, since 2 consecutive black blocks already exist.
// Therefore, we return 0.
// ```
//
// **Constraints:**
//
// - `n == blocks.length`
// - `1 <= n <= 100`
// - `blocks[i]` is either `'W'` or `'B'`.
// - `1 <= k <= n`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// Use DP
func minimumRecolors(blocks string, k int) int {
	n := len(blocks)

	dpNext := make([]int, n+1)
	for i := n - 1; i >= 0; i-- {
		if blocks[i] == 'B' {
			dpNext[i] = dpNext[i+1] + 1
			if dpNext[i] == k {
				return 0
			}
		}
	}

	for j := 1; j <= k; j++ {
		dpPrev := dpNext
		dpNext = make([]int, n+1)
		for i := n - 1; i >= 0; i-- {
			if blocks[i] == 'B' {
				dpNext[i] = dpNext[i+1] + 1
			} else {
				dpNext[i] = dpPrev[i+1] + 1
			}
			if dpNext[i] == k {
				return j
			}
		}
	}

	return k
}

// Use sliding window
func minimumRecolors2(blocks string, k int) int {
	n := len(blocks)

	res := k
	for i := 0; i <= n-k; i++ {
		count := 0
		for j := i; j < i+k; j++ {
			if blocks[j] == 'W' {
				count++
			}
		}
		res = min(res, count)
	}

	return res
}
