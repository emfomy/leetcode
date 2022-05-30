// Source: https://leetcode.com/problems/divide-two-integers/
// Title: Divide Two Integers
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given two integers dividend and divisor, divide two integers without using multiplication, division, and mod operator.
//
// The integer division should truncate toward zero, which means losing its fractional part. For example, 8.345 would be truncated to 8, and -2.7335 would be truncated to -2.
//
// Return the quotient after dividing dividend by divisor.
//
// Note: Assume we are dealing with an environment that could only store integers within the 32-bit signed integer range: [−2^31, 2^31 − 1]. For this problem, if the quotient is strictly greater than 2^31 - 1, then return 2^31 - 1, and if the quotient is strictly less than -2^31, then return -2^31.
//
// Example 1:
//
//   Input: dividend = 10, divisor = 3
//   Output: 3
//   Explanation: 10/3 = 3.33333.. which is truncated to 3.
//
// Example 2:
//
//   Input: dividend = 7, divisor = -3
//   Output: -2
//   Explanation: 7/-3 = -2.33333.. which is truncated to -2.
//
// Constraints:
//
//   -2^31 <= dividend, divisor <= 2^31 - 1
//   divisor != 0
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"math"
)

func divide(dividend int, divisor int) int {
	return int(divide32(int32(dividend), int32(divisor)))
}

// Convert to 32 bit to fit the environment
func divide32(dividend int32, divisor int32) int32 {
	// These are edge cases
	if dividend == math.MinInt32 && divisor == -1 {
		return math.MaxInt32
	}

	// Convert to positive
	sign := (dividend >= 0) == (divisor >= 0)
	uDividend := abs32(dividend)
	uDivisor := abs32(divisor)

	// Shift divisor to the highest digit of dividend
	shift := uint32(1)
	for ; uDividend/2 >= uDivisor; shift <<= 1 {
		uDivisor <<= 1
	}

	// Apply long division
	quotient := uint32(0)
	for ; shift > 0; shift >>= 1 {
		if uDividend >= uDivisor {
			uDividend -= uDivisor
			quotient += shift
		}
		uDivisor >>= 1
	}

	// Apply sign
	if sign {
		return int32(quotient)
	}
	return int32(-quotient)
}

func abs32(num int32) uint32 {
	if num >= 0 {
		return uint32(num)
	}
	return uint32(-num)
}
