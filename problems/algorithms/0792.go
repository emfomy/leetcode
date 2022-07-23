// Source: https://leetcode.com/problems/number-of-matching-subsequences/
// Title: Number of Matching Subsequences
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a string s and an array of strings words, return the number of words[i] that is a subsequence of s.
//
// A subsequence of a string is a new string generated from the original string with some characters (can be none) deleted without changing the relative order of the remaining characters.
//
//   For example, "ace" is a subsequence of "abcde".
//
// Example 1:
//
//   Input: s = "abcde", words = ["a","bb","acd","ace"]
//   Output: 3
//   Explanation: There are three strings in words that are a subsequence of s: "a", "acd", "ace".
//
// Example 2:
//
//   Input: s = "dsahjpjauf", words = ["ahjpjau","ja","ahbwzgqnuk","tnmlanowax"]
//   Output: 2
//
// Constraints:
//
//   1 <= s.length <= 5 * 10^4
//   1 <= words.length <= 5000
//   1 <= words[i].length <= 50
//   s and words[i] consist of only lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// O(n*k)
func numMatchingSubseq(s string, words []string) int {
	res := 0
	for _, word := range words {
		res += _matchingSubseq(s, word)
	}
	return res
}

func _matchingSubseq(s string, word string) int {
	nw := len(word)
	ns := len(s)
	if nw > ns {
		return 0
	}

	i := 0
	for j := 0; j < ns; j++ {
		if word[i] == s[j] {
			i++
			if i == nw {
				return 1
			}
		}
	}
	return 0
}
