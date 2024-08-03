// Source: https://leetcode.com/problems/power-of-three
// Title: Power of Three
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer n, return true if it is a power of three. Otherwise, return false.
//
// An integer n is a power of three, if there exists an integer x such that n == 3x.
//
// Example 1:
//
//   Input: n = 27
//   Output: true
//
// Example 2:
//
//   Input: n = 0
//   Output: false
//
// Example 3:
//
//   Input: n = 9
//   Output: true
//
// Constraints:
//
//   -2^31 <= n <= 2^31-1
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func isPowerOfThree(n int) bool {
	if n < 1 {
		return false
	}

	for n%3 == 0 {
		n /= 3
	}

	return n == 1
}

// 1162261467 is the max power of three in 32-bit integer
func isPowerOfThree2(n int) bool {
	return n > 0 && 1162261467%n == 0
}
