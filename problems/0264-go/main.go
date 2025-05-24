// Source: https://leetcode.com/problems/ugly-number
// Title: Ugly Number
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// An ugly number is a positive integer whose prime factors are limited to 2, 3, and 5.
//
// Given an integer n, return the nth ugly number.
//
// Example 1:
//
//   Input: n = 10
//   Output: 12
//   Explanation: [1, 2, 3, 4, 5, 6, 8, 9, 10, 12] is the sequence of the first 10 ugly numbers.
//
// Example 2:
//
//   Input: n = 1
//   Output: 1
//   Explanation: 1 has no prime factors, therefore all of its prime factors are limited to 2, 3, and 5.
//
// Constraints:
//
// 1 <= n <= 1690
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func nthUglyNumber(n int) int {
	seq := make([]int, n+1)

	next := 1
	seq[0] = next

	t2, t3, t5 := 0, 0, 0

	for i := 1; i < n; i++ {
		val2 := seq[t2] * 2
		val3 := seq[t3] * 3
		val5 := seq[t5] * 5

		next = _min3(val2, val3, val5)
		if next == val2 {
			t2++
		}
		if next == val3 {
			t3++
		}
		if next == val5 {
			t5++
		}
		seq[i] = next
	}
	return next
}

func _min3(a, b, c int) int {
	return _min(_min(a, b), c)
}

func _min(a, b int) int {
	if a < b {
		return a
	}
	return b
}
