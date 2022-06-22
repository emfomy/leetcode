// Source: https://leetcode.com/problems/integer-break/
// Title: Integer Break
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer n, break it into the sum of k positive integers, where k >= 2, and maximize the product of those integers.
//
// Return the maximum product you can get.
//
// Example 1:
//
//   Input: n = 2
//   Output: 1
//   Explanation: 2 = 1 + 1, 1 × 1 = 1.
//
// Example 2:
//
//   Input: n = 10
//   Output: 36
//   Explanation: 10 = 3 + 3 + 4, 3 × 3 × 4 = 36.
//
// Constraints:
//
//   2 <= n <= 58
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import "math"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Use DP
func integerBreak(n int) int {
	dp := make([]int, n+1)

	for i := 2; i <= n; i++ {
		for j := 1; j < i; j++ {
			dp[i] = _max3(dp[i], (i-j)*j, dp[i-j]*j)
		}
	}

	return dp[n]
}

func _max3(a, b, c int) int {
	return _max(_max(a, b), c)
}

func _max(a, b int) int {
	if a > b {
		return a
	}
	return b
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Use Greedy + Math
// Say we break n into (n/x) number of x's. The product is F(x) = x^(n/x)
// To maximum F(x), we need x such that F'(x) = 0
// F'(x) = n * x^(n/x-2) * (1-ln(x)) = 0 => x = e
// Therefore, we want to break n into 2 or 3 (3 is better since e is closer to 3).
func integerBreak2(n int) int {
	if n == 2 {
		return 1
	}
	if n == 3 {
		return 2
	}

	quotient := n / 3
	reminder := n % 3

	if reminder == 1 {
		reminder = 4
		quotient--
	} else if reminder == 0 {
		reminder = 1
	}

	return int(math.Pow(float64(3), float64(quotient))) * reminder
}
