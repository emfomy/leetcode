// Source: https://leetcode.com/problems/minimum-number-of-steps-to-make-two-strings-anagram
// Title: Minimum Number of Steps to Make Two Strings Anagram
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given two strings of the same length s and t. In one step you can choose any character of t and replace it with another character.
//
// Return the minimum number of steps to make t an anagram of s.
//
// An Anagram of a string is a string that contains the same characters with a different (or the same) ordering.
//
// Example 1:
//
//   Input: s = "bab", t = "aba"
//   Output: 1
//   Explanation: Replace the first 'a' in t with b, t = "bba" which is anagram of s.
//
// Example 2:
//
//  Input: s = "leetcode", t = "practice"
//  Output: 5
//  Explanation: Replace 'p', 'r', 'a', 'i' and 'c' from t with proper characters to make t anagram of s.
//
// Example 3:
//
//   Input: s = "anagram", t = "mangaar"
//   Output: 0
//   Explanation: "anagram" and "mangaar" are anagrams.
//
// Constraints:
//
//   1 <= s.length <= 5*10^4
//   s.length == t.length
//   s and t consist of lowercase English letters only.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func minSteps(s string, t string) int {
	// Count characters
	count1 := make([]int, 26)
	count2 := make([]int, 26)
	for _, ch := range s {
		count1[ch-'a']++
	}
	for _, ch := range t {
		count2[ch-'a']++
	}

	// Compare character counts
	res := 0
	for i := 0; i < 26; i++ {
		res += _abs(count1[i] - count2[i])
	}
	return res / 2
}

func _abs(v int) int {
	if v >= 0 {
		return v
	}
	return -v
}
