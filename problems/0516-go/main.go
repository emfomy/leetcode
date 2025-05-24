// Source: https://leetcode.com/problems/longest-palindromic-subsequence
// Title: Longest Palindromic Subsequence
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a string s, find the longest palindromic subsequence's length in s.
//
// A subsequence is a sequence that can be derived from another sequence by deleting some or no elements without changing the order of the remaining elements.
//
// Example 1:
//
//   Input: s = "bbbab"
//   Output: 4
//   Explanation: One possible longest palindromic subsequence is "bbbb".
//
// Example 2:
//
//   Input: s = "cbbd"
//   Output: 2
//   Explanation: One possible longest palindromic subsequence is "bb".
//
// Constraints:
//
//   1 <= s.length <= 1000
//   s consists only of lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Apply 2D Needleman-Wunsch Algorithm on the string and its reverse.
func longestPalindromeSubseq(s string) int {
	n := len(s)
	mat := make([][]int, n+1)
	for i := 0; i <= n; i++ {
		mat[i] = make([]int, n+1)
	}

	// DP
	for i := 1; i <= n; i++ {
		c1 := s[i-1]
		for j := 1; j <= n; j++ {
			c2 := s[n-j]
			if c1 == c2 {
				mat[i][j] = mat[i-1][j-1] + 1
			} else {
				mat[i][j] = _max(mat[i][j-1], mat[i-1][j])
			}
		}
	}

	return mat[n][n]
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Apply 1D Needleman-Wunsch Algorithm on the string and its reverse.
func longestPalindromeSubseq2(s string) int {
	n := len(s)
	prev := make([]int, n+1)
	next := make([]int, n+1)

	// DP
	for i := 1; i <= n; i++ {
		c1 := s[i-1]
		for j := 1; j <= n; j++ {
			c2 := s[n-j]
			if c1 == c2 {
				next[j] = prev[j-1] + 1
			} else {
				next[j] = _max(next[j-1], prev[j])
			}
		}
		prev, next = next, prev
	}

	return prev[n]
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

func _max(a, b int) int {
	if a > b {
		return a
	}
	return b
}
