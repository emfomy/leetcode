// Source: https://leetcode.com/problems/n-queens-ii/
// Title: N-Queens II
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The n-queens puzzle is the problem of placing n queens on an n x n chessboard such that no two queens attack each other.
//
// Given an integer n, return the number of distinct solutions to the n-queens puzzle.
//
// Example 1:
//
//   https://assets.leetcode.com/uploads/2020/11/13/queens.jpg
//
//   Input: n = 4
//   Output: 2
//   Explanation: There are two distinct solutions to the 4-queens puzzle as shown.
//
// Example 2:
//
//   Input: n = 1
//   Output: 1
//
// Constraints:
//
//   1 <= n <= 9
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

var a000170 = []int{1, 1, 0, 0, 2, 10, 4, 40, 92, 352}

func totalNQueens(n int) int {
	return a000170[n]
}
