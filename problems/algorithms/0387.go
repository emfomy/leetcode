// Source: https://leetcode.com/problems/first-unique-character-in-a-string/
// Title: Roman to Integer
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a string s, find the first non-repeating character in it and return its index. If it does not exist, return -1.
//
// Example 1:
//
//   Input: s = "leetcode"
//   Output: 0
//
// Example 2:
//
//   Input: s = "loveleetcode"
//   Output: 2
//
// Example 3:
//
//   Input: s = "aabb"
//   Output: -1
//
// Constraints:
//
//   1 <= s.length <= 105
//   s consists of only lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func firstUniqChar(s string) int {
	count := make(map[rune]int, 26)

	for _, c := range s {
		count[c]++
	}

	for i, c := range s {
		if count[c] == 1 {
			return i
		}
	}

	return -1
}
