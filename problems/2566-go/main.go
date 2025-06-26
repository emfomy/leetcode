// Source: https://leetcode.com/problems/maximum-difference-by-remapping-a-digit
// Title: Maximum Difference by Remapping a Digit
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer `num`. You know that Bob will sneakily **remap** one of the `10` possible digits (`0` to `9`) to another digit.
//
// Return the difference between the maximum and minimumvalues Bob can make by remapping**exactly** **one** digit in `num`.
//
// **Notes:**
//
// - When Bob remaps a digit d1to another digit d2, Bob replaces all occurrences of `d1`in `num`with `d2`.
// - Bob can remap a digit to itself, in which case `num`does not change.
// - Bob can remap different digits for obtaining minimum and maximum values respectively.
// - The resulting number after remapping can contain leading zeroes.
//
// **Example 1:**
//
// ```
// Input: num = 11891
// Output: 99009
// Explanation:
// To achieve the maximum value, Bob can remap the digit 1 to the digit 9 to yield 99899.
// To achieve the minimum value, Bob can remap the digit 1 to the digit 0, yielding 890.
// The difference between these two numbers is 99009.
// ```
//
// **Example 2:**
//
// ```
// Input: num = 90
// Output: 99
// Explanation:
// The maximum value that can be returned by the function is 99 (if 0 is replaced by 9) and the minimum value that can be returned by the function is 0 (if 9 is replaced by 0).
// Thus, we return 99.```
//
// **Constraints:**
//
// - `1 <= num <= 10^8`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"strconv"
	"strings"
)

// To maximize the number, remap to hightest non-9 digit to 9.
// To minimize the number, remap to hightest non-0 digit to 0.
func minMaxDifference(num int) int {
	digits := strconv.Itoa(num)

	// Maximize
	maxDigit := '9'
	for _, digit := range digits {
		if digit != '9' {
			maxDigit = digit
			break
		}
	}
	maxDigits := digits
	if maxDigit != '9' {
		maxDigits = strings.ReplaceAll(digits, string(maxDigit), "9")
	}
	maxNum, _ := strconv.Atoi(maxDigits)

	// Minimize
	minDigit := '0'
	for _, digit := range digits {
		if digit != '0' {
			minDigit = digit
			break
		}
	}
	minDigits := digits
	if minDigit != '0' {
		minDigits = strings.ReplaceAll(digits, string(minDigit), "0")
	}
	minNum, _ := strconv.Atoi(minDigits)

	return maxNum - minNum
}
