// Source: https://leetcode.com/problems/minimize-xor
// Title: Minimize XOR
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given two positive integers `num1` and `num2`, find the positive integer `x` such that:
//
// - `x` has the same number of set bits as `num2`, and
// - The value `x XOR num1` is **minimal**.
//
// Note that `XOR` is the bitwise XOR operation.
//
// Return the integer `x`. The test cases are generated such that `x` is **uniquely determined**.
//
// The number of **set bits** of an integer is the number of `1`'s in its binary representation.
//
// **Example 1:**
//
// ```
// Input: num1 = 3, num2 = 5
// Output: 3
// Explanation:
// The binary representations of num1 and num2 are 0011 and 0101, respectively.
// The integer **3** has the same number of set bits as num2, and the value `3 XOR 3 = 0` is minimal.
// ```
//
// **Example 2:**
//
// ```
// Input: num1 = 1, num2 = 12
// Output: 3
// Explanation:
// The binary representations of num1 and num2 are 0001 and 1100, respectively.
// The integer **3** has the same number of set bits as num2, and the value `3 XOR 1 = 2` is minimal.
// ```
//
// **Constraints:**
//
// - `1 <= num1, num2 <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"math/bits"
)

func minimizeXor(num1 int, num2 int) int {
	bit1 := bits.OnesCount(uint(num1))
	bit2 := bits.OnesCount(uint(num2))

	res := 0

	if bit1 >= bit2 { // Use upper `1`s from num1
		count := 0
		for i := 30; i >= 0 && count < bit2; i-- {
			b := 1 << i
			if num1&b != 0 {
				res |= b
				count++
			}
		}
	} else { // Use all `1`s from num and lower `0`s from num1
		res = num1
		count := bit1
		for i := 0; i < 30 && count < bit2; i++ {
			b := 1 << i
			if num1&b == 0 {
				res |= b
				count++
			}
		}
	}

	return res
}
