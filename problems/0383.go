// Source: https://leetcode.com/problems/ransom-note
// Title: Ransom Note
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given two strings ransomNote and magazine, return true if ransomNote can be constructed by using the letters from magazine and false otherwise.
//
// Each letter in magazine can only be used once in ransomNote.
//
// Example 1:
//
//   Input: ransomNote = "a", magazine = "b"
//   Output: false
//
// Example 2:
//
//   Input: ransomNote = "aa", magazine = "ab"
//   Output: false
//
// Example 3:
//
//   Input: ransomNote = "aa", magazine = "aab"
//   Output: true
//
// Constraints:
//
//   1 <= ransomNote.length, magazine.length <= 10^5
//   ransomNote and magazine consist of lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func canConstruct(ransomNote string, magazine string) bool {
	count := [26]int{}

	for _, ch := range magazine {
		count[ch-'a']++
	}

	for _, ch := range ransomNote {
		count[ch-'a']--
	}

	for _, cnt := range count {
		if cnt < 0 {
			return false
		}
	}

	return true
}
