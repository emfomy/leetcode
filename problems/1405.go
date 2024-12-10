// Source: https://leetcode.com/problems/longest-happy-string
// Title: Longest Happy String
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// A string s is called happy if it satisfies the following conditions:
//
//   * s only contains the letters 'a', 'b', and 'c'.
//   * s does not contain any of "aaa", "bbb", or "ccc" as a substring.
//   * s contains at most a occurrences of the letter 'a'.
//   * s contains at most b occurrences of the letter 'b'.
//   * s contains at most c occurrences of the letter 'c'.
//
// Given three integers a, b, and c, return the longest possible happy string. If there are multiple longest happy strings, return any of them. If there is no such string, return the empty string "".
//
// A substring is a contiguous sequence of characters within a string.
//
// Example 1:
//
//   Input: a = 1, b = 1, c = 7
//   Output: "ccaccbcc"
//   Explanation: "ccbccacc" would also be a correct answer.
//
// Example 2:
//
//   Input: a = 7, b = 1, c = 0
//   Output: "aabaa"
//   Explanation: It is the only correct answer in this case.
//
// Constraints:
//
//   0 <= a, b, c <= 100
//   a + b + c > 0
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func longestDiverseString(a int, b int, c int) string {
	x, y, z := "a", "b", "c"
	// Sort
	if a < b {
		a, b = b, a
		x, y = y, x
	}
	if b < c {
		b, c = c, b
		y, z = z, y
	}
	if a < b {
		a, b = b, a
		x, y = y, x
	}

	res := ""
	for a > 0 {
		if a > b && a >= 2 {
			res += x + x
			a -= 2
		} else {
			res += x
			a -= 1
		}
		a, b = b, a
		x, y = y, x

		if b < c {
			b, c = c, b
			y, z = z, y
		}
	}

	return res
}
