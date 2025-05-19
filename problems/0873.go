// Source: https://leetcode.com/problems/length-of-longest-fibonacci-subsequence
// Title: Length of Longest Fibonacci Subsequence
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// A sequence `x_1, x_2, ..., x_n` is Fibonacci-like if:

// - `n >= 3`
// - `x_i + x_(i+1) == x_(i+2)` for all `i + 2 <= n`

// Given a **strictly increasing** array `arr` of positive integers forming a sequence, return the **length** of the longest Fibonacci-like subsequence of `arr`. If one does not exist, return `0`.

// A **subsequence** is derived from another sequence `arr` by deleting any number of elements (including none) from `arr`, without changing the order of the remaining elements. For example, `[3, 5, 8]` is a subsequence of `[3, 4, 5, 6, 7, 8]`.

// **Example 1:**

// ```
// Input: arr = [1,2,3,4,5,6,7,8]
// Output: 5
// Explanation: The longest subsequence that is fibonacci-like: [1,2,3,5,8].```

// **Example 2:**

// ```
// Input: arr = [1,3,7,11,12,14,18]
// Output: 3
// Explanation
// :****The longest subsequence that is fibonacci-like: [1,11,12], [3,11,14] or [7,11,18].```

// **Constraints:**

// - `3 <= arr.length <= 1000`
// - `1 <= arr[i] < arr[i + 1] <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// We can generate a fibbonacci array with given any pair of numbers
// Therefore we can loop thought all pairs to find the maximum subsequence
func lenLongestFibSubseq(arr []int) int {
	n := len(arr)
	numSet := make(map[int]bool, n)
	// pairSet := make(map[int64]bool)

	for _, num := range arr {
		numSet[num] = true
	}

	res := 0

	for i := 0; i < n; i++ {
		for j := i + 1; j < n; j++ {
			a, b := arr[i], arr[j]
			// pair := int64(a)<<32 + int64(b)
			// if pairSet[pair] { // already visited
			// 	continue
			// }

			l := 2
			for true {
				// pairSet[pair] = true
				c := a + b
				if !numSet[c] {
					break
				}
				l++
				a, b = b, c
			}
			res = max(res, l)
		}
	}

	if res == 2 {
		return 0
	}
	return res
}
