// Source: https://leetcode.com/problems/count-the-number-of-arrays-with-k-matching-adjacent-elements
// Title: Count the Number of Arrays with K Matching Adjacent Elements
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given three integers `n`, `m`, `k`. A **good array** `arr` of size `n` is defined as follows:
//
// - Each element in `arr` is in the **inclusive** range `[1, m]`.
// - Exactly `k` indices `i` (where `1 <= i < n`) satisfy the condition `arr[i - 1] == arr[i]`.
//
// Return the number of **good arrays** that can be formed.
//
// Since the answer may be very large, return it **modulo **`10^9 + 7`.
//
// **Example 1:**
//
// ```
// Input: n = 3, m = 2, k = 1
// Output: 4
// Explanation:
// - There are 4 good arrays. They are `[1, 1, 2]`, `[1, 2, 2]`, `[2, 1, 1]` and `[2, 2, 1]`.
// - Hence, the answer is 4.
// ```
//
// **Example 2:**
//
// ```
// Input: n = 4, m = 2, k = 2
// Output: 6
// Explanation:
// - The good arrays are `[1, 1, 1, 2]`, `[1, 1, 2, 2]`, `[1, 2, 2, 2]`, `[2, 1, 1, 1]`, `[2, 2, 1, 1]` and `[2, 2, 2, 1]`.
// - Hence, the answer is 6.
// ```
//
// **Example 3:**
//
// ```
// Input: n = 5, m = 2, k = 0
// Output: 2
// Explanation:
// - The good arrays are `[1, 2, 1, 2, 1]` and `[2, 1, 2, 1, 2]`. Hence, the answer is 2.
// ```
//
// **Constraints:**
//
// - `1 <= n <= 10^5`
// - `1 <= m <= 10^5`
// - `0 <= k <= n - 1`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

const modulo = int(1e9 + 7)
const MAX_N = int(1e5)

var facts [MAX_N + 1]int
var factInvs [MAX_N + 1]int

func init() {
	// Precompute factorials
	facts[0], facts[1] = 1, 1
	for i := 2; i <= MAX_N; i++ {
		facts[i] = (facts[i-1] * i) % modulo
	}

	// Precompute inverse factorials
	factInvs[MAX_N] = _pow(facts[MAX_N], modulo-2)
	for i := MAX_N; i > 0; i-- {
		factInvs[i-1] = (factInvs[i] * i) % modulo
	}
}

// Use math with precomputed factorial
//
// We first consider the case k=0
// The 0-th item has `m` cases.
// The i-th item (i>0) has `m-1` cases (since it should not be equal to the previous one).
// Therefore Ans(n, m, 0) = m(m-1)^(n-1).
//
// For k > 0, we start from Ans(n-k, m, 0)
//
// For each case in Ans(n-k, m, 0), we choose k items and add same items behind them.
// Here we have H(n-k, k) = C(n-k+k-1, k) = C(n-1, k) possible way to choose k items.
// Therefore Ans(n, m, k) = C(n-1, k) * Ans(n-k, m, 0) = C(n-1, k) m(m-1)^(n-k-1).
func countGoodArrays(n int, m int, k int) int {
	ans := _comb(n-1, k)
	ans = _mul(ans, m)
	ans = _mul(ans, _pow(m-1, n-k-1))
	return ans
}

func _pow(x int, n int) int {
	res := 1
	for {
		if (n & 1) != 0 {
			res = (res * x) % modulo
		}
		n >>= 1
		if n == 0 {
			break
		}
		x = (x * x) % modulo
	}
	return res
}

func _inv(x int) int {
	return _pow(x, modulo-2)
}

func _mul(x, y int) int {
	return x * y % modulo
}

func _div(x, y int) int {
	return _mul(x, _inv(y))
}

func _comb(x, y int) int {
	return _div(facts[x], _mul(facts[x-y], facts[y]))
}
