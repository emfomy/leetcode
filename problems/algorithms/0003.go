// Source: https://leetcode.com/problems/longest-substring-without-repeating-characters/
// Title: Longest Substring Without Repeating Characters
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a string, find the length of the longest substring without repeating characters.
//
// Example 1:
//
//   Input: "abcabcbb"
//   Output: 3
//   Explanation: The answer is "abc", with the length of 3.
//
// Example 2:
//
//   Input: "bbbbb"
//   Output: 1
//   Explanation: The answer is "b", with the length of 1.
//
// Example 3:
//
//   Input: "pwwkew"
//   Output: 3
//   Explanation: The answer is "wke", with the length of 3.
//                Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
//
// Constraints:
//
//   0 <= s.length <= 5 * 10^4
//   s consists of English letters, digits, symbols and spaces.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

type void struct{}

func lengthOfLongestSubstring(s string) int {
	pool := make(map[byte]void)
	maxLen := 0
	i := 0 // start index of substring
	j := 0 // end index of substring
	n := len(s)

	for j < n {
		if _, ok := pool[s[j]]; !ok { // no repeating character
			pool[s[j]] = void{}
			j += 1
			maxLen = _max(maxLen, j-i)
		} else {
			delete(pool, s[i])
			i += 1
		}
	}
	return maxLen
}

func _max(a, b int) int {
	if a > b {
		return a
	}
	return b
}
