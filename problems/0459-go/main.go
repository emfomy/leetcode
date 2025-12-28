// Source: https://leetcode.com/problems/repeated-substring-pattern
// Title: Repeated Substring Pattern
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a string `s`, check if it can be constructed by taking a substring of it and appending multiple copies of the substring together.
//
// **Example 1:**
//
// ```
// Input: s = "abab"
// Output: true
// Explanation: It is the substring "ab" twice.
// ```
//
// **Example 2:**
//
// ```
// Input: s = "aba"
// Output: false
// ```
//
// **Example 3:**
//
// ```
// Input: s = "abcabcabcabc"
// Output: true
// Explanation: It is the substring "abc" four times or the substring "abcabc" twice.
// ```
//
// **Constraints:**
//
// - `1 <= s.length <= 10^4`
// - `s` consists of lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import "strings"

// Loop through all divisor of the length of the string.
func repeatedSubstringPattern(s string) bool {
	n := len(s)
	for l := 1; l <= n/2; l++ {
		if n % l != 0 {
			continue
		}
		if s == strings.Repeat(s[:l], n/l) {
			return true
		}
	}
	return false
}

func repeatedSubstringPattern2(s string) bool {
	t := s+s
	return strings.Contains(t[1:len(t)-1], s)
}
