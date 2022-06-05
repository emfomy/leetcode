// Source: https://leetcode.com/problems/n-queens/
// Title: N-Queens
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The n-queens puzzle is the problem of placing n queens on an n x n chessboard such that no two queens attack each other.
//
// Given an integer n, return all distinct solutions to the n-queens puzzle. You may return the answer in any order.
//
// Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space, respectively.
//
// Example 1:
//
//   https://assets.leetcode.com/uploads/2020/11/13/queens.jpg
//
//   Input: n = 4
//   Output: [[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
//   Explanation: There exist two distinct solutions to the 4-queens puzzle as shown above
//
// Example 2:
//
//   Input: n = 1
//   Output: [["Q"]]
//
// Constraints:
//
//   1 <= n <= 9
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"strings"
)

func solveNQueens(n int) [][]string {
	// Get permutation of queens
	idxs := make([]int, n) // rowIdx -> colIdx
	for i := 0; i < len(idxs); i++ {
		idxs[i] = i
	}

	resList := make([][]string, 0)
	_getPermutations(n, idxs, func() {
		if _checkBoard(n, idxs) {
			resList = append(resList, _makeBoard(n, idxs))
		}
	})

	return resList
}

// Heap's algorithm
func _getPermutations(k int, arr []int, output func()) {
	if k == 1 {
		output()
		return
	}

	_getPermutations(k-1, arr, output)
	for i := 0; i < k-1; i++ {
		if k%2 == 0 { // k even
			arr[i], arr[k-1] = arr[k-1], arr[i] // swap
		} else { // k odd
			arr[0], arr[k-1] = arr[k-1], arr[0] // swap
		}
		_getPermutations(k-1, arr, output)
	}
}

func _checkBoard(k int, idxs []int) bool {
	if k == 1 {
		return true
	}

	// Check if queen k-1 attack other queens
	iLast := k - 1
	vLast := idxs[iLast]
	for i := 0; i < k-1; i++ {
		v := idxs[i]
		if i-iLast == v-vLast || i-iLast == vLast-v {
			return false
		}
	}

	return _checkBoard(k-1, idxs)
}

func _makeBoard(k int, idxs []int) []string {
	board := make([]string, k)
	for i := 0; i < k; i++ {
		board[i] = strings.Repeat(".", idxs[i]) + "Q" + strings.Repeat(".", k-idxs[i]-1)
	}
	return board
}
