// Source: https://leetcode.com/problems/sum-of-square-numbers
// Title: Sum of Square Numbers
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a non-negative integer c, decide whether there're two integers a and b such that a^2 + b^2 = c.
//
// Example 1:
//
//   Input: c = 5
//   Output: true
//   Explanation: 1 * 1 + 2 * 2 = 5
//
// Example 2:
//
//   Input: c = 3
//   Output: false
//
// Constraints:
//
//   0 <= c <= 2^31 - 1
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import "math"

func judgeSquareSum(c int) bool {
	for a := 0; a <= c; a++ {
		a2 := a * a
		if a2 > c {
			return false
		}

		b := math.Sqrt(float64(c - a2))
		if b == math.Trunc(b) {
			return true
		}

		if float64(a) >= b {
			return false
		}
	}

	return false
}
