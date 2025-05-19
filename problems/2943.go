// Source: https://leetcode.com/problems/count-symmetric-integers
// Title: Count Symmetric Integers
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given two positive integers `low` and `high`.
//
// An integer `x` consisting of `2 * n` digits is **symmetric** if the sum of the first `n` digits of `x` is equal to the sum of the last `n` digits of `x`. Numbers with an odd number of digits are never symmetric.
//
// Return the **number of symmetric** integers in the range `[low, high]`.
//
// **Example 1:**
//
// ```
// Input: low = 1, high = 100
// Output: 9
// Explanation: There are 9 symmetric integers between 1 and 100: 11, 22, 33, 44, 55, 66, 77, 88, and 99.
// ```
//
// **Example 2:**
//
// ```
// Input: low = 1200, high = 1230
// Output: 4
// Explanation: There are 4 symmetric integers between 1200 and 1230: 1203, 1212, 1221, and 1230.
// ```
//
// **Constraints:**
//
// - `1 <= low <= high <= 10^4`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"strconv"
)

func countSymmetricIntegers(low int, high int) int {
	count := 0
	for num := low; num <= high; num++ {
		str := strconv.Itoa(num)
		n := len(str)
		if n%2 == 1 {
			continue
		}
		upperSum := 0
		for _, digit := range str[:n/2] {
			upperSum += int(digit - '0')
		}

		lowerSum := 0
		for _, digit := range str[n/2:] {
			lowerSum += int(digit - '0')
		}

		if upperSum == lowerSum {
			count++
		}
	}

	return count
}

func countSymmetricIntegers2(low int, high int) int {
	count := 0

	// 2 digits
	for num := max(10, low); num <= min(99, high); num++ {
		upperSum := num / 10
		lowerSum := num % 10
		if upperSum == lowerSum {
			count++
		}
	}

	// 4 digits
	for num := max(1000, low); num <= min(9999, high); num++ {
		upperSum := num/1000 + (num/100)%10
		lowerSum := (num/10)%10 + num%10
		if upperSum == lowerSum {
			count++
		}
	}

	return count
}
