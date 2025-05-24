// Source: https://leetcode.com/problems/edit-distance
// Title: Edit Distance
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given two strings word1 and word2, return the minimum number of operations required to convert word1 to word2.
//
// You have the following three operations permitted on a word:
//
//   Insert a character
//   Delete a character
//   Replace a character
//
// Example 1:
//
//   Input: word1 = "horse", word2 = "ros"
//   Output: 3
//   Explanation:
//     horse -> rorse (replace 'h' with 'r')
//     rorse -> rose (remove 'r')
//     rose -> ros (remove 'e')
//
// Example 2:
//
//   Input: word1 = "intention", word2 = "execution"
//   Output: 5
//   Explanation:
//     intention -> inention (remove 't')
//     inention -> enention (replace 'i' with 'e')
//     enention -> exention (replace 'n' with 'x')
//     exention -> exection (replace 'n' with 'c')
//     exection -> execution (insert 'u')
//
// Constraints:
//
//   0 <= word1.length, word2.length <= 500
//   word1 and word2 consist of lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// Apply 2D Needleman-Wunsch Algorithm
func minDistance(word1 string, word2 string) int {
	m := len(word1)
	n := len(word2)

	mat := make([][]int, m+1)
	for i := 0; i <= m; i++ {
		mat[i] = make([]int, n+1)
	}

	for j := 0; j <= n; j++ {
		mat[0][j] = j
	}

	// DP
	for i, c1 := range word1 {
		mat[i+1][0] = i + 1
		for j, c2 := range word2 {
			mat[i+1][j+1] = _min(mat[i][j+1], mat[i+1][j]) + 1
			if c1 == c2 {
				mat[i+1][j+1] = _min(mat[i+1][j+1], mat[i][j])
			} else {
				mat[i+1][j+1] = _min(mat[i+1][j+1], mat[i][j]+1)
			}
		}
	}

	return mat[m][n]
}

// Apply 1D Needleman-Wunsch Algorithm
func minDistance2(word1 string, word2 string) int {
	n := len(word2)

	prev := make([]int, n+1)
	next := make([]int, n+1)

	for j := 0; j <= n; j++ {
		prev[j] = j
	}

	// DP
	for i, c1 := range word1 {
		next[0] = i + 1
		for j, c2 := range word2 {
			next[j+1] = _min(next[j], prev[j+1]) + 1
			if c1 == c2 {
				next[j+1] = _min(next[j+1], prev[j])
			} else {
				next[j+1] = _min(next[j+1], prev[j]+1)
			}
		}
		prev, next = next, prev
	}

	return prev[n]
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

func _min(a, b int) int {
	if a < b {
		return a
	}
	return b
}
