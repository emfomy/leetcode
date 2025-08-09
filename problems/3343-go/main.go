// Source: https://leetcode.com/problems/count-number-of-balanced-permutations
// Title: Count Number of Balanced Permutations
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a string `num`. A string of digits is called **balanced** if the sum of the digits at even indices is equal to the sum of the digits at odd indices.
//
// Return the number of **distinct** **permutations** of `num` that are **balanced**.
//
// Since the answer may be very large, return it **modulo** `10^9 + 7`.
//
// A **permutation** is a rearrangement of all the characters of a string.
//
// **Example 1:**
//
// ```
// Input: num = "123"
// Output: 2
// Explanation:
// - The distinct permutations of `num` are `"123"`, `"132"`, `"213"`, `"231"`, `"312"` and `"321"`.
// - Among them, `"132"` and `"231"` are balanced. Thus, the answer is 2.
// ```
//
// **Example 2:**
//
// ```
// Input: num = "112"
// Output: 1
// Explanation:
// - The distinct permutations of `num` are `"112"`, `"121"`, and `"211"`.
// - Only `"121"` is balanced. Thus, the answer is 1.
// ```
//
// **Example 3:**
//
// ```
// Input: num = "12345"
// Output: 0
// Explanation:
// - None of the permutations of `num` are balanced, so the answer is 0.
// ```
//
// **Constraints:**
//
// - `2 <= num.length <= 80`
// - `num` consists of digits `'0'` to `'9'` only.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

const modulo = int(1e9 + 7)
const MAX_M = 40

// Note that we may precompute the factorials in the inverse factorials.
// Since M = 1e9+7 is a prime, by Fermat's little theorem, a^(M-1) = 1 (mod M)
// Therefore, 1/a = a^(M-2) (mod M).
var facts [MAX_M + 1]int
var factInvs [MAX_M + 1]int

func init() {
	// Precompute factorials
	facts[0], facts[1] = 1, 1
	for i := 2; i <= MAX_M; i++ {
		facts[i] = (facts[i-1] * i) % modulo
	}

	// Precompute inverse factorials
	factInvs[MAX_M] = _fastPow(facts[MAX_M], modulo-2)
	for i := MAX_M; i > 0; i-- {
		factInvs[i-1] = (factInvs[i] * i) % modulo
	}
}

func _fastPow(x int, n int) int {
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

// Use 3D-DP
func countBalancedPermutations(num string) int {
	n := len(num)
	m := (n + 1) / 2

	// Count digits
	freq := [10]int{}
	sum := 0
	for _, d := range num {
		freq[d-'0']++
		sum += int(d - '0')
	}

	// Not balanceable
	if sum%2 == 1 {
		return 0
	}

	// Precompute total permutation
	totalPerm := (facts[m] * facts[n/2]) % modulo

	// DP, digit * evenDigits * currSum
	dp := [10][][]int{}
	for i := range 10 {
		dp[i] = make([][]int, m+1)
		for j := range m + 1 {
			dp[i][j] = make([]int, sum+1)
			for k := range sum + 1 {
				dp[i][j][k] = -1
			}
		}
	}
	var solve func(digit int, evenCount, oddCount int, evenSum, oddSum int) int
	solve = func(digit int, evenCount, oddCount int, evenSum, oddSum int) int {
		if digit == 10 { // end of recursion
			if evenSum == sum/2 && evenCount == m {
				return totalPerm
			}
			return 0
		}
		if evenSum > sum/2 || oddSum > sum/2 || evenCount > m || oddCount > m {
			return 0
		}
		if dp[digit][evenCount][evenSum] != -1 {
			return dp[digit][evenCount][evenSum]
		}

		ways := 0
		for count := max(0, freq[digit]-m+oddCount); count <= min(freq[digit], m-evenCount); count++ {
			evens, odds := count, freq[digit]-count
			numer := solve(digit+1, evenCount+evens, oddCount+odds, evenSum+digit*evens, oddSum+digit*odds)
			denom := (factInvs[evens] * factInvs[odds]) % modulo
			ways += (numer * denom) % modulo
			ways %= modulo
		}

		dp[digit][evenCount][evenSum] = ways
		return ways
	}

	return solve(0, 0, 0, 0, 0)
}
