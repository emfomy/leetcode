// Source: https://leetcode.com/problems/shortest-common-supersequence
// Title: Shortest Common Supersequence
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given two strings `str1` and `str2`, return the shortest string that has both `str1` and `str2` as **subsequences**. If there are multiple valid strings, return **any** of them.
//
// A string `s` is a **subsequence** of string `t` if deleting some number of characters from `t` (possibly `0`) results in the string `s`.
//
// **Example 1:**
//
// ```
// Input: str1 = "abac", str2 = "cab"
// Output: "cabac"
// Explanation:
// str1 = "abac" is a subsequence of "cabac" because we can delete the first "c".
// str2 = "cab" is a subsequence of "cabac" because we can delete the last "ac".
// The answer provided is the shortest such string that satisfies these properties.
// ```
//
// **Example 2:**
//
// ```
// Input: str1 = "aaaaaaaa", str2 = "aaaaaaaa"
// Output: "aaaaaaaa"
// ```
//
// **Constraints:**
//
// - `1 <= str1.length, str2.length <= 1000`
// - `str1` and `str2` consist of lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"strings"
)

// 2D Needleman-Wunsch Algorithm
func shortestCommonSupersequence(str1 string, str2 string) string {
	m, n := len(str1), len(str2)

	mat := make([][]int, m+1)
	for i := range m + 1 {
		mat[i] = make([]int, n+1)
	}
	dir := make([][]byte, m+1)
	for i := range m + 1 {
		dir[i] = make([]byte, n+1)
	}
	for i := range m {
		dir[i+1][0] = 'u'
	}
	for j := range n {
		dir[0][j+1] = 'l'
	}

	// DP
	for i, c1 := range str1 {
		for j, c2 := range str2 {
			if c1 == c2 {
				mat[i+1][j+1] = mat[i][j] + 1
				dir[i+1][j+1] = 'd'
			} else {
				if mat[i+1][j] >= mat[i][j+1] {
					mat[i+1][j+1] = mat[i+1][j]
					dir[i+1][j+1] = 'l'
				} else {
					mat[i+1][j+1] = mat[i][j+1]
					dir[i+1][j+1] = 'u'
				}
			}
		}
	}

	i, j := m, n
	mn := m + n - mat[m][n]
	res := make([]byte, mn)
	for k := mn - 1; k >= 0; k-- {
		switch dir[i][j] {
		case 'd':
			res[k] = str1[i-1]
			i--
			j--
		case 'l':
			res[k] = str2[j-1]
			j--
		case 'u':
			res[k] = str1[i-1]
			i--
		}
	}

	return string(res)
}

// 2D Needleman-Wunsch Algorithm
func shortestCommonSupersequence2(str1 string, str2 string) string {
	m, n := len(str1), len(str2)

	// Make sure str1 is the longest
	if m < n {
		return shortestCommonSupersequence2(str2, str1)
	}

	dp := make([][]int, m+1)
	for i := range m + 1 {
		dp[i] = make([]int, n+1)
	}

	// DP
	for i := m - 1; i >= 0; i-- {
		for j := n - 1; j >= 0; j-- {
			if str1[i] == str2[j] {
				dp[i][j] = dp[i+1][j+1] + 1
			} else {
				dp[i][j] = max(dp[i+1][j], dp[i][j+1])
			}
		}
	}

	var res strings.Builder
	i, j := 0, 0
	for i < m && j < n {
		if str1[i] == str2[j] {
			// same char
			res.WriteByte(str1[i])
			i++
			j++
		} else if dp[i+1][j] >= dp[i][j+1] {
			// pick str1
			// when equal, pick str1 since it's longer
			res.WriteByte(str1[i])
			i++
		} else {
			// pick str2
			res.WriteByte(str2[j])
			j++
		}
	}

	// Copy remainings
	res.WriteString(str1[i:])
	res.WriteString(str2[j:])

	return res.String()
}
