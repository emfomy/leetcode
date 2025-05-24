// Source: https://leetcode.com/problems/range-sum-query-2d-immutable
// Title: Range Sum Query 2D - Immutable
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a 2D matrix matrix, handle multiple queries of the following type:
//
//   Calculate the sum of the elements of matrix inside the rectangle defined by its upper left corner (row1, col1) and lower right corner (row2, col2).
//
// Implement the NumMatrix class:
//
//   NumMatrix(int[][] matrix) Initializes the object with the integer matrix matrix.
//   int sumRegion(int row1, int col1, int row2, int col2) Returns the sum of the elements of matrix inside the rectangle defined by its upper left corner (row1, col1) and lower right corner (row2, col2).
//
// Example 1:
//
//   https://assets.leetcode.com/uploads/2021/03/14/sum-grid.jpg
//
//   Input
//     ["NumMatrix", "sumRegion", "sumRegion", "sumRegion"]
//     [[[[3, 0, 1, 4, 2], [5, 6, 3, 2, 1], [1, 2, 0, 1, 5], [4, 1, 0, 1, 7], [1, 0, 3, 0, 5]]], [2, 1, 4, 3], [1, 1, 2, 2], [1, 2, 2, 4]]
//
//   Output
//     [null, 8, 11, 12]
//
//   Explanation
//     NumMatrix numMatrix = new NumMatrix([[3, 0, 1, 4, 2], [5, 6, 3, 2, 1], [1, 2, 0, 1, 5], [4, 1, 0, 1, 7], [1, 0, 3, 0, 5]]);
//     numMatrix.sumRegion(2, 1, 4, 3); // return 8 (i.e sum of the red rectangle)
//     numMatrix.sumRegion(1, 1, 2, 2); // return 11 (i.e sum of the green rectangle)
//     numMatrix.sumRegion(1, 2, 2, 4); // return 12 (i.e sum of the blue rectangle)
//
// Constraints:
//
//   m == matrix.length
//   n == matrix[i].length
//   1 <= m, n <= 200
//   -10^5 <= matrix[i][j] <= 10^5
//   0 <= row1 <= row2 < m
//   0 <= col1 <= col2 < n
//   At most 10^4 calls will be made to sumRegion.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

/**
 * Your NumMatrix object will be instantiated and called as such:
 * obj := Constructor(matrix);
 * param_1 := obj.SumRegion(row1,col1,row2,col2);
 */

type NumMatrix struct {
	partialSum [][]int
}

func Constructor(matrix [][]int) NumMatrix {
	m := len(matrix)
	n := len(matrix[0])

	for i := 1; i < m; i++ {
		for j := 0; j < n; j++ {
			matrix[i][j] += matrix[i-1][j]
		}
	}

	for j := 1; j < n; j++ {
		for i := 0; i < m; i++ {
			matrix[i][j] += matrix[i][j-1]
		}
	}

	return NumMatrix{
		partialSum: matrix,
	}
}

func (this *NumMatrix) SumRegion(row1 int, col1 int, row2 int, col2 int) int {
	row1 -= 1
	col1 -= 1
	return this.getPartialSum(row1, col1) +
		this.getPartialSum(row2, col2) -
		this.getPartialSum(row1, col2) -
		this.getPartialSum(row2, col1)
}

func (this *NumMatrix) getPartialSum(i, j int) int {
	if i < 0 || j < 0 {
		return 0
	}
	return this.partialSum[i][j]
}
