// Source: https://leetcode.com/problems/longest-common-subsequence/
// Title: Longest Common Subsequence
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given two strings text1 and text2, return the length of their longest common subsequence. If there is no common subsequence, return 0.
//
// A subsequence of a string is a new string generated from the original string with some characters (can be none) deleted without changing the relative order of the remaining characters.
//
// For example, "ace" is a subsequence of "abcde".
// A common subsequence of two strings is a subsequence that is common to both strings.
//
// Example 1:
//
//   Input: text1 = "abcde", text2 = "ace"
//   Output: 3
//   Explanation: The longest common subsequence is "ace" and its length is 3.
//
// Example 2:
//
//   Input: text1 = "abc", text2 = "abc"
//   Output: 3
//   Explanation: The longest common subsequence is "abc" and its length is 3.
//
// Example 3:
//
//   Input: text1 = "abc", text2 = "def"
//   Output: 0
//   Explanation: There is no such common subsequence, so the result is 0.
//
// Constraints:
//
//   1 <= text1.length, text2.length <= 1000
//   text1 and text2 consist of only lowercase English characters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// Apply 2D Needleman-Wunsch Algorithm
func longestCommonSubsequence(text1 string, text2 string) int {
	m := len(text1)
	n := len(text2)

	mat := make([][]int, m+1)
	for i := 0; i <= m; i++ {
		mat[i] = make([]int, n+1)
	}

	// DP
	for i, c1 := range text1 {
		for j, c2 := range text2 {
			if c1 == c2 {
				mat[i+1][j+1] = mat[i][j] + 1
			} else {
				mat[i+1][j+1] = _max(mat[i+1][j], mat[i][j+1])
			}
		}
	}

	return mat[m][n]
}

// Apply 1D Needleman-Wunsch Algorithm
func longestCommonSubsequence2(text1 string, text2 string) int {
	n := len(text2)

	prev := make([]int, n+1)
	next := make([]int, n+1)

	// DP
	for _, c1 := range text1 {
		for j, c2 := range text2 {
			if c1 == c2 {
				next[j+1] = prev[j] + 1
			} else {
				next[j+1] = _max(next[j], prev[j+1])
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
