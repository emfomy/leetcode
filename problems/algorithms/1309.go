// Source: https://leetcode.com/problems/decrypt-string-from-alphabet-to-integer-mapping/
// Title: Decrypt String from Alphabet to Integer Mapping
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a string s formed by digits and '#'. We want to map s to English lowercase characters as follows:
//
// Characters ('a' to 'i') are represented by ('1' to '9') respectively.
// Characters ('j' to 'z') are represented by ('10#' to '26#') respectively.
// Return the string formed after mapping.
//
// The test cases are generated so that a unique mapping will always exist.
//
// Example 1:
//
//   Input: s = "10#11#12"
//   Output: "jkab"
//   Explanation: "j" -> "10#" , "k" -> "11#" , "a" -> "1" , "b" -> "2".
//
// Example 2:
//
//   Input: s = "1326#"
//   Output: "acz"
//
// Constraints:
//
//   1 <= s.length <= 1000
//   s consists of digits and the '#' letter.
//   s will be a valid string such that mapping is always possible.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"strings"
)

func freqAlphabets(s string) string {
	c0 := byte('a') - 1

	l := len(s)

	buffer := make([]byte, 0, l)
	for i := l - 1; i >= 0; i-- {
		c := s[i]
		if c == '#' {
			buffer = append(buffer, ((s[i-2]-'0')*10+(s[i-1]-'0'))+c0)
			i -= 2
		} else {
			buffer = append(buffer, (c-'0')+c0)
		}
	}

	l = len(buffer)
	sb := strings.Builder{}
	for i := l - 1; i >= 0; i-- {
		sb.WriteByte(buffer[i])
	}
	return sb.String()
}
