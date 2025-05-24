// Source: https://leetcode.com/problems/interleaving-string
// Title: Interleaving String
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given strings s1, s2, and s3, find whether s3 is formed by an interleaving of s1 and s2.
//
// An interleaving of two strings s and t is a configuration where they are divided into non-empty substrings such that:
//
//   s = s1 + s2 + ... + sn
//   t = t1 + t2 + ... + tm
//   |n - m| <= 1
//   The interleaving is s1 + t1 + s2 + t2 + s3 + t3 + ... or t1 + s1 + t2 + s2 + t3 + s3 + ...
//
// Note: a + b is the concatenation of strings a and b.
//
// Example 1:
//
//   Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
//   Output: true
//
// Example 2:
//
//   Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
//   Output: false
//
// Example 3:
//
//   Input: s1 = "", s2 = "", s3 = ""
//   Output: true
//
// Constraints:
//
//   0 <= s1.length, s2.length <= 100
//   0 <= s3.length <= 200
//   s1, s2, and s3 consist of lowercase English letters.
//
// Follow up: Could you solve it using only O(s2.length) additional memory space?
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// Use 2D DP
func isInterleave(s1 string, s2 string, s3 string) bool {
	m := len(s1)
	n := len(s2)
	if m+n != len(s3) {
		return false
	}

	dp := make([][]bool, m+1)
	for i := 0; i <= m; i++ {
		dp[i] = make([]bool, n+1)
	}

	dp[0][0] = true
	for j := 0; j < n; j++ {
		if s2[j] == s3[j] && dp[0][j] {
			dp[0][j+1] = true
		}
	}

	for i := 0; i < m; i++ {
		if s1[i] == s3[i] && dp[i][0] {
			dp[i+1][0] = true
		}
		for j := 0; j < n; j++ {
			if (s1[i] == s3[i+j+1] && dp[i][j+1]) || (s2[j] == s3[i+j+1] && dp[i+1][j]) {
				dp[i+1][j+1] = true
			}
		}
	}

	return dp[m][n]
}

// Use 1D DP
func isInterleave2(s1 string, s2 string, s3 string) bool {
	m := len(s1)
	n := len(s2)
	if m+n != len(s3) {
		return false
	}

	dp := make([]bool, n+1)

	dp[0] = true
	for j := 0; j < n; j++ {
		dp[j+1] = (s2[j] == s3[j] && dp[j])
	}

	for i := 0; i < m; i++ {
		dp[0] = (s1[i] == s3[i] && dp[0])
		for j := 0; j < n; j++ {
			dp[j+1] = (s1[i] == s3[i+j+1] && dp[j+1]) || (s2[j] == s3[i+j+1] && dp[j])
		}
	}

	return dp[n]
}
