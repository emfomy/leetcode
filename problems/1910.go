// Source: https://leetcode.com/problems/remove-all-occurrences-of-a-substring
// Title: Remove All Occurrences of a Substring
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given two strings `s` and `part`, perform the following operation on `s` until **all** occurrences of the substring `part` are removed:
//
// - Find the **leftmost** occurrence of the substring `part` and **remove** it from `s`.
//
// Return `s` after removing all occurrences of `part`.
//
// A **substring** is a contiguous sequence of characters in a string.
//
// **Example 1:**
//
// ```
// Input: s = "daabcbaabcbc", part = "abc"
// Output: "dab"
// Explanation
// : The following operations are done:
// - s = "da**abc** baabcbc", remove "abc" starting at index 2, so s = "dabaabcbc".
// - s = "daba**abc** bc", remove "abc" starting at index 4, so s = "dababc".
// - s = "dab**abc** ", remove "abc" starting at index 3, so s = "dab".
// Now s has no occurrences of "abc".
// ```
//
// **Example 2:**
//
// ```
// Input: s = "axxxxyyyyb", part = "xy"
// Output: "ab"
// Explanation
// : The following operations are done:
// - s = "axxx**xy** yyyb", remove "xy" starting at index 4 so s = "axxxyyyb".
// - s = "axx**xy** yyb", remove "xy" starting at index 3 so s = "axxyyb".
// - s = "ax**xy** yb", remove "xy" starting at index 2 so s = "axyb".
// - s = "a**xy** b", remove "xy" starting at index 1 so s = "ab".
// Now s has no occurrences of "xy".
// ```
//
// **Constraints:**
//
// - `1 <= s.length <= 1000`
// - `1 <= part.length <= 1000`
// - `s`​ and `part` consists of lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"strings"
)

func removeOccurrences(s string, part string) string {
	p := len(part)
	i := p
	for i <= len(s) {
		if strings.HasSuffix(s[:i], part) {
			s = s[:i-p] + s[i:]
			i -= (p - 1)
		} else {
			i++
		}
	}
	return s
}
