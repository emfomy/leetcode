// Source: https://leetcode.com/problems/to-lower-case/
// Title: To Lower Case
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a string s, return the string after replacing every uppercase letter with the same lowercase letter.
//
// Example 1:
//
//   Input: s = "Hello"
//   Output: "hello"
//
// Example 2:
//
//   Input: s = "here"
//   Output: "here"
//
// Example 3:
//
//   Input: s = "LOVELY"
//   Output: "lovely"
//
// Constraints:
//
//   1 <= s.length <= 100
//   s consists of printable ASCII characters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"strings"
)

func toLowerCase(s string) string {
	sb := strings.Builder{}

	for _, c := range s {
		if 'A' <= c && c <= 'Z' {
			sb.WriteRune(c - 'A' + 'a')
		} else {
			sb.WriteRune(c)
		}
	}

	return sb.String()
}
