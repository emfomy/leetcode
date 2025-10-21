// Source: https://leetcode.com/problems/wildcard-matching
// Title: Wildcard Matching
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an input string (`s`) and a pattern (`p`), implement wildcard pattern matching with support for `'?'` and `'*'` where:
//
// - `'?'` Matches any single character.
// - `'*'` Matches any sequence of characters (including the empty sequence).
//
// The matching should cover the **entire** input string (not partial).
//
// **Example 1:**
//
// ```
// Input: s = "aa", p = "a"
// Output: false
// Explanation: "a" does not match the entire string "aa".
// ```
//
// **Example 2:**
//
// ```
// Input: s = "aa", p = "*"
// Output: true
// Explanation:'*' matches any sequence.
// ```
//
// **Example 3:**
//
// ```
// Input: s = "cb", p = "?a"
// Output: false
// Explanation:'?' matches 'c', but the second letter is 'a', which does not match 'b'.
// ```
//
// **Constraints:**
//
// - `0 <= s.length, p.length <= 2000`
// - `s` contains only lowercase English letters.
// - `p` contains only lowercase English letters, `'?'` or `'*'`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"regexp"
	"strings"
)

func isMatch(s string, p string) bool {
	p = strings.ReplaceAll(p, "?", `\w`)
	p = strings.ReplaceAll(p, "*", `\w*`)
	return regexp.MustCompile("^" + p + "$").MatchString(s)
}
