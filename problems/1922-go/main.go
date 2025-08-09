// Source: https://leetcode.com/problems/count-good-numbers
// Title: Count Good Numbers
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// A digit string is **good** if the digits **(0-indexed)** at **even** indices are **even** and the digits at **odd** indices are **prime** (`2`, `3`, `5`, or `7`).
//
// - For example, `"2582"` is good because the digits (`2` and `8`) at even positions are even and the digits (`5` and `2`) at odd positions are prime. However, `"3245"` is **not** good because `3` is at an even index but is not even.
//
// Given an integer `n`, return the **total** number of good digit strings of length `n`. Since the answer may be large, **return it modulo **`10^9 + 7`.
//
// A **digit string** is a string consisting of digits `0` through `9` that may contain leading zeros.
//
// **Example 1:**
//
// ```
// Input: n = 1
// Output: 5
// Explanation: The good numbers of length 1 are "0", "2", "4", "6", "8".
// ```
//
// **Example 2:**
//
// ```
// Input: n = 4
// Output: 400
// ```
//
// **Example 3:**
//
// ```
// Input: n = 50
// Output: 564908303
// ```
//
// **Constraints:**
//
// - `1 <= n <= 10^15`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

const modulo = int(1e9 + 7)

// Res = 5^(#even) * 4^(#odd)
func countGoodNumbers(n int64) int {
	odd := n / 2
	even := n - odd
	return (_fastPow(5, even) * _fastPow(4, odd)) % modulo
}

func _fastPow(x int, n int64) int {
	res := 1
	for n > 0 {
		if (n & 1) != 0 {
			res = (res * x) % modulo
		}
		n >>= 1
		x = (x * x) % modulo
	}
	return res
}
