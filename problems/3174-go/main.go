// Source: https://leetcode.com/problems/clear-digits
// Title: Clear Digits
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a string `s`.
//
// Your task is to remove **all** digits by doing this operation repeatedly:
//
// - Delete the first digit and the **closest non-digit** character to its left.
//
// Return the resulting string after removing all digits.
//
// **Example 1:**
//
// ```
// Input: s = "abc"
// Output: "abc"
// Explanation:
// There is no digit in the string.
// ```
//
// **Example 2:**
//
// ```
// Input: s = "cb34"
// Output: ""
// Explanation:
// First, we apply the operation on `s[2]`, and `s` becomes `"c4"`.
// Then we apply the operation on `s[1]`, and `s` becomes `""`.
//
// **Constraints:**
//
// - `1 <= s.length <= 100`
// - `s` consists only of lowercase English letters and digits.
// - The input is generated such that it is possible to delete all digits.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// Use stack
func clearDigits(s string) string {
	n := len(s)

	stack := make([]byte, 0, n)

	for i := range n {
		ch := s[i]
		if '0' <= ch && ch <= '9' { // is digit
			if len(stack) > 0 {
				stack = stack[:len(stack)-1] // pop
			}
		} else {
			stack = append(stack, ch) // push
		}
	}

	return string(stack)
}
