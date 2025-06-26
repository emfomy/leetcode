// Source: https://leetcode.com/problems/k-th-smallest-in-lexicographical-order
// Title: K-th Smallest in Lexicographical Order
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given two integers `n` and `k`, return the `k^th` lexicographically smallest integer in the range `[1, n]`.
//
// **Example 1:**
//
// ```
// Input: n = 13, k = 2
// Output: 10
// Explanation: The lexicographical order is [1, 10, 11, 12, 13, 2, 3, 4, 5, 6, 7, 8, 9], so the second smallest number is 10.
// ```
//
// **Example 2:**
//
// ```
// Input: n = 1, k = 1
// Output: 1
// ```
//
// **Constraints:**
//
// - `1 <= k <= n <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"strconv"

	"github.com/emirpasic/gods/trees/binaryheap"
)

// Heap, TLE
func findKthNumber(n int, k int) int {
	heap := binaryheap.NewWithStringComparator()

	for i := 1; i <= n; i++ {
		heap.Push(strconv.Itoa(i))
	}

	var item any
	for range k {
		item, _ = heap.Pop()
	}

	ans, _ := strconv.Atoi(item.(string))
	return ans
}

// Count step
func findKthNumber2(n int, k int) int {
	countSteps := func(prefix1, prefix2 int) int {
		steps := 0
		for prefix1 <= n {
			steps += min(n+1, prefix2) - prefix1
			prefix1 *= 10
			prefix2 *= 10
		}
		return steps
	}

	curr := 1
	k--

	for k > 0 {
		step := countSteps(curr, curr+1)
		if step <= k {
			curr++
			k -= step
		} else {
			curr *= 10
			k--
		}
	}

	return curr
}
