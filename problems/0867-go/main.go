// Source: https://leetcode.com/problems/transpose-matrix
// Title: Transpose Matrix
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a 2D integer array matrix, return the transpose of matrix.
//
// The transpose of a matrix is the matrix flipped over its main diagonal, switching the matrix's row and column indices.
//
// Example 1:
//
//   Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
//   Output: [[1,4,7],[2,5,8],[3,6,9]]
//
// Example 2:
//
//   Input: matrix = [[1,2,3],[4,5,6]]
//   Output: [[1,4],[2,5],[3,6]]
//
// Constraints:
//
//   m == matrix.length
//   n == matrix[i].length
//   1 <= m, n <= 1000
//   1 <= m * n <= 10^5
//   -10^9 <= matrix[i][j] <= 10^9
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func transpose(matrix [][]int) [][]int {
	m := len(matrix)
	n := len(matrix[0])

	res := make([][]int, n)
	for j := 0; j < n; j++ {
		res[j] = make([]int, m)
	}

	for i, row := range matrix {
		for j, v := range row {
			res[j][i] = v
		}
	}

	return res
}
