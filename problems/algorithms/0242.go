// Source: https://leetcode.com/problems/valid-anagram/
// Title: Valid Anagram
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given two strings s and t, return true if t is an anagram of s, and false otherwise.
//
// An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase, typically using all the original letters exactly once.
//
// Example 1:
//
//   Input: s = "anagram", t = "nagaram"
//   Output: true
//
//  Example 2:
//
//   Input: s = "rat", t = "car"
//   Output: false
//
// Constraints:
//
//   1 <= s.length, t.length <= 5 * 10^4
//   s and t consist of lowercase English letters.
//
// Follow up: What if the inputs contain Unicode characters? How would you adapt your solution to such a case?
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func isAnagram(s string, t string) bool {
	n := len(s)
	if len(t) != n {
		return false
	}

	pool := make([]int, 26)

	// Count char in s
	for _, v := range s {
		pool[v-'a']++
	}

	// Count char in t
	for _, v := range t {
		pool[v-'a']--
	}

	// Check anagram
	for _, cnt := range pool {
		if cnt != 0 {
			return false
		}
	}

	return true
}
