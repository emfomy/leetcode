// Source: https://leetcode.com/problems/find-the-punishment-number-of-an-integer
// Title: Find the Punishment Number of an Integer
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a positive integer `n`, return the **punishment number** of `n`.
//
// The **punishment number** of `n` is defined as the sum of the squares of all integers `i` such that:
//
// - `1 <= i <= n`
// - The decimal representation of `i * i` can be partitioned into contiguous substrings such that the sum of the integer values of these substrings equals `i`.
//
// **Example 1:**
//
// ```
// Input: n = 10
// Output: 182
// Explanation: There are exactly 3 integers i in the range [1, 10] that satisfy the conditions in the statement:
// - 1 since 1 * 1 = 1
// - 9 since 9 * 9 = 81 and 81 can be partitioned into 8 and 1 with a sum equal to 8 + 1 == 9.
// - 10 since 10 * 10 = 100 and 100 can be partitioned into 10 and 0 with a sum equal to 10 + 0 == 10.
// Hence, the punishment number of 10 is 1 + 81 + 100 = 182
// ```
//
// **Example 2:**
//
// ```
// Input: n = 37
// Output: 1478
// Explanation: There are exactly 4 integers i in the range [1, 37] that satisfy the conditions in the statement:
// - 1 since 1 * 1 = 1.
// - 9 since 9 * 9 = 81 and 81 can be partitioned into 8 + 1.
// - 10 since 10 * 10 = 100 and 100 can be partitioned into 10 + 0.
// - 36 since 36 * 36 = 1296 and 1296 can be partitioned into 1 + 29 + 6.
// Hence, the punishment number of 37 is 1 + 81 + 100 + 1296 = 1478
// ```
//
// **Constraints:**
//
// - `1 <= n <= 1000`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

var isPNum = map[int]bool{
	1:    true,
	9:    true,
	10:   true,
	36:   true,
	45:   true,
	55:   true,
	82:   true,
	91:   true,
	99:   true,
	100:  true,
	235:  true,
	297:  true,
	369:  true,
	370:  true,
	379:  true,
	414:  true,
	657:  true,
	675:  true,
	703:  true,
	756:  true,
	792:  true,
	909:  true,
	918:  true,
	945:  true,
	964:  true,
	990:  true,
	991:  true,
	999:  true,
	1000: true,
}

func punishmentNumber(n int) int {
	res := 0
	for i := 1; i <= n; i++ {
		if isPNum[i] {
			res += i * i
		}
	}

	return res
}

func punishmentNumber2(n int) int {
	res := 0
	for i := 1; i <= n; i++ {
		if _checkSum(i*i, i) {
			res += i * i
		}
	}

	return res
}

func _checkSum(num, target int) bool {
	if target < 0 || num < target {
		return false
	}
	if num == target {
		return true
	}
	if num >= 10 && _checkSum(num/10, target-num%10) {
		return true
	}
	if num >= 100 && _checkSum(num/100, target-num%100) {
		return true
	}
	if num >= 1000 && _checkSum(num/1000, target-num%1000) {
		return true
	}
	return false
}
