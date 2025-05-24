// Source: https://leetcode.com/problems/fibonacci-number
// Title: Fibonacci Number
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The Fibonacci numbers, commonly denoted F(n) form a sequence, called the Fibonacci sequence, such that each number is the sum of the two preceding ones, starting from 0 and 1. That is,
//
//   F(0) = 0, F(1) = 1
//   F(n) = F(n - 1) + F(n - 2), for n > 1.
//
// Given n, calculate F(n).
//
// Example 1:
//
//   Input: n = 2
//   Output: 1
//   Explanation: F(2) = F(1) + F(0) = 1 + 0 = 1.
//
// Example 2:
//
//   Input: n = 3
//   Output: 2
//   Explanation: F(3) = F(2) + F(1) = 1 + 1 = 2.
//
// Example 3:
//
//   Input: n = 4
//   Output: 3
//   Explanation: F(4) = F(3) + F(2) = 2 + 1 = 3.
//
// Constraints:
//
//   0 <= n <= 30
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"math"
)

func fib(n int) int {
	if n == 0 {
		return 0
	}

	prev, curr := 0, 1
	for i := 1; i < n; i++ {
		prev, curr = curr, prev+curr
	}

	return curr
}

// F(n) = (Phi^n + Phi^-n)/sqrt(5)
// Since Phi^n < 1, we may use round instead
func fib2(n int) int {
	invSqrt5 := math.Sqrt(0.2)
	res := math.Pow(math.Phi, float64(n)) * invSqrt5
	return int(math.Round(res))
}
