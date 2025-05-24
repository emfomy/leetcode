// Source: https://leetcode.com/problems/n-th-tribonacci-number
// Title: N-th Tribonacci Number
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The Tribonacci sequence Tn is defined as follows:
//
//   T0 = 0, T1 = 1, T2 = 1, and Tn+3 = Tn + Tn+1 + Tn+2 for n >= 0.
//
// Given n, return the value of Tn.
//
// Example 1:
//
//   Input: n = 4
//   Output: 4
//   Explanation:
//     T_3 = 0 + 1 + 1 = 2
//     T_4 = 1 + 1 + 2 = 4
//
// Example 2:
//
// Input: n = 25
// Output: 1389537

// Constraints:
//
//   0 <= n <= 37
//   The answer is guaranteed to fit within a 32-bit integer, ie. answer <= 2^31 - 1.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"math"
)

func tribonacci(n int) int {
	if n == 0 {
		return 0
	}
	if n == 1 {
		return 1
	}

	prev, curr, next := 0, 1, 1
	for i := 2; i < n; i++ {
		prev, curr, next = curr, next, prev+curr+next
	}

	return next
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// T(n) = beta * alpha^n (rounded to integer), where
// alpha = (a1 + a2 + 1)/3, a1 = cbrt(19+3sqrt(33)), a2 = cbrt(19-3sqrt(33))
// beta = 3b/(b^2-2b+4, b = cbrt(586+102sqrt(33))
var (
	sqrt33 = math.Sqrt(33)
	a1     = math.Cbrt(19 + 3*sqrt33)
	a2     = math.Cbrt(19 - 3*sqrt33)
	b      = math.Cbrt(586 + 102*sqrt33)
	alpha  = (a1 + a2 + 1) / 3
	beta   = (3 * b) / (b*b - 2*b + 4)
)

func tribonacci2(n int) int {
	res := math.Pow(alpha, float64(n)) * beta
	return int(math.Round(res))
}
