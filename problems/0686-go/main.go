// Source: https://leetcode.com/problems/repeated-string-match
// Title: Repeated String Match
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given two strings `a` and `b`, return the minimum number of times you should repeat string `a` so that string `b` is a substring of it. If it is impossible for `b`​​​​​​ to be a substring of `a` after repeating it, return `-1`.
//
// **Notice:** string `"abc"` repeated 0 times is `""`, repeated 1 time is `"abc"` and repeated 2 times is `"abcabc"`.
//
// **Example 1:**
//
// ```
// Input: a = "abcd", b = "cdabcdab"
// Output: 3
// Explanation: We return 3 because by repeating a three times "ab**cdabcdab**cd", b is a substring of it.
// ```
//
// **Example 2:**
//
// ```
// Input: a = "a", b = "aa"
// Output: 2
// ```
//
// **Constraints:**
//
// - `1 <= a.length, b.length <= 10^4`
// - `a` and `b` consist of lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"strings"
)

func repeatedStringMatch(a string, b string) int {
	aa := ""
	for i := 1; true; i++ {
		aa += a
		if strings.Contains(aa, b) {
			return i
		}
		if i > 2 && len(aa) > len(b)*2 {
			break
		}
	}
	return -1
}
