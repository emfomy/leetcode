// Source: https://leetcode.com/problems/unique-length-3-palindromic-subsequences
// Title: Unique Length-3 Palindromic Subsequences
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a string `s`, return the number of **unique palindromes of length three** that are a **subsequence** of `s`.
//
// Note that even if there are multiple ways to obtain the same subsequence, it is still only counted **once**.
//
// A **palindrome** is a string that reads the same forwards and backwards.
//
// A **subsequence** of a string is a new string generated from the original string with some characters (can be none) deleted without changing the relative order of the remaining characters.
//
// - For example, `"ace"` is a subsequence of `"abcde"`.
//
// **Example 1:**
//
// ```
// Input: s = "aabca"
// Output: 3
// Explanation: The 3 palindromic subsequences of length 3 are:
// - "aba" (subsequence of "aabca")
// - "aaa" (subsequence of "aabca")
// - "aca" (subsequence of "aabca")
// ```
//
// **Example 2:**
//
// ```
// Input: s = "adc"
// Output: 0
// Explanation: There are no palindromic subsequences of length 3 in "adc".
// ```
//
// **Example 3:**
//
// ```
// Input: s = "bbcbaba"
// Output: 4
// Explanation: The 4 palindromic subsequences of length 3 are:
// - "bbb" (subsequence of "bbcbaba")
// - "bcb" (subsequence of "bbcbaba")
// - "bab" (subsequence of "bbcbaba")
// - "aba" (subsequence of "bbcbaba")
// ```
//
// **Constraints:**
//
// - `3 <= s.length <= 10^5`
// - `s` consists of only lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func countPalindromicSubsequence(s string) int {
	n := len(s)

	var charIdxFirst [26]int // last appeared indices
	for i := n - 1; i >= 0; i-- {
		charIdxFirst[s[i]-'a'] = i
	}

	var charIdxLast [26]int // last appeared indices
	for i := 0; i < n; i++ {
		charIdxLast[s[i]-'a'] = i
	}

	res := 0
	for ch := 0; ch < 26; ch++ {
		firstIdx := charIdxFirst[ch]
		lastIdx := charIdxLast[ch]
		var uniqueChars [26]bool
		for i := firstIdx + 1; i < lastIdx; i++ {
			chm := s[i] - 'a'
			if !uniqueChars[chm] {
				res++
			}
			uniqueChars[chm] = true
		}
	}

	return res
}
