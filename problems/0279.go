// Source: https://leetcode.com/problems/perfect-squares
// Title: Perfect Squares
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer n, return the least number of perfect square numbers that sum to n.
//
// A perfect square is an integer that is the square of an integer; in other words, it is the product of some integer with itself. For example, 1, 4, 9, and 16 are perfect squares while 3 and 11 are not.
//
// Example 1:
//
//   Input: n = 12
//   Output: 3
//   Explanation: 12 = 4 + 4 + 4.
//
// Example 2:
//
//   Input: n = 13
//   Output: 2
//   Explanation: 13 = 4 + 9.
//
// Constraints:
//
//   1 <= n <= 10^4
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import "math"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Use DP
func numSquares(n int) int {
	dp := make([]int, n+1)

	for i := 1; i <= n; i++ {
		dp[i] = math.MaxInt32
		for j := 1; j*j <= i; j++ {
			dp[i] = _min(dp[i], dp[i-j*j]+1)
		}
	}

	return dp[n]
}

func _min(a, b int) int {
	if a < b {
		return a
	}
	return b
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Use Math
// By Lagrange's four-square theorem, the result should be 1, 2, 3, 4.
func numSquares2(n int) int {
	// If n is a perfect square, return 1.
	if _isSquare(n) {
		return 1
	}

	// The result is 4 if and only if n = 4^a * (8b+7)
	// See Legendre's three-square theorem
	for n&3 == 0 { // n%4 == 0
		n >>= 2 // n /= 4
	}
	if n&7 == 7 { // n % 8 == 7
		return 4
	}

	// Check if result is 2
	for i := 1; i*i <= n; i++ {
		if _isSquare(n - i*i) {
			return 2
		}
	}

	return 3
}

func _isSquare(n int) bool {
	sq := int(math.Sqrt(float64(n)))
	return n == sq*sq
}
