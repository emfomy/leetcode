// Source: https://leetcode.com/problems/search-a-2d-matrix-ii/
// Title: Search a 2D Matrix II
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Write an efficient algorithm that searches for a value target in an m x n integer matrix matrix. This matrix has the following properties:
//
//   Integers in each row are sorted in ascending from left to right.
//   Integers in each column are sorted in ascending from top to bottom.
//
// Example 1:
//
//   https://assets.leetcode.com/uploads/2020/11/24/searchgrid2.jpg
//
//   Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 5
//   Output: true
//
// Example 2:
//
//   https://assets.leetcode.com/uploads/2020/11/24/searchgrid.jpg
//
//   Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 20
//   Output: false
//
// Constraints:
//
//   m == matrix.length
//   n == matrix[i].length
//   1 <= n, m <= 300
//   -10^9 <= matrix[i][j] <= 10^9
//   All the integers in each row are sorted in ascending order.
//   All the integers in each column are sorted in ascending order.
//   -10^9 <= target <= 10^9
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"sort"
)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// O(mlogn); Use divide and conquer
func searchMatrix(matrix [][]int, target int) bool {
	m := len(matrix)
	n := len(matrix[0])

	return _searchMatrix(matrix, 0, m, 0, n, target)
}

// Search in matrix[m1:m2][n1:n2].
// We split the matrix in four orthant by (i, j).
// Note that we can skip the the values in top-left/bottom-left orthant,
//   since they are all less/greater the target.
func _searchMatrix(matrix [][]int, m1, m2, n1, n2, target int) bool {
	if m1 >= m2 || n1 >= n2 {
		return false
	}

	i := (m1 + m2) / 2
	j := sort.SearchInts(matrix[i][n1:n2], target) + n1
	if j < n2 && matrix[i][j] == target {
		return true
	}

	if _searchMatrix(matrix, i+1, m2, n1, j, target) {
		return true
	}
	if _searchMatrix(matrix, m1, i, j, n2, target) {
		return true
	}

	return false
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// O(m+n); Search from top-right to bottom-left
func searchMatrix2(matrix [][]int, target int) bool {
	m := len(matrix)
	n := len(matrix[0])

	i := 0
	j := n - 1

	for i < m && j >= 0 {
		val := matrix[i][j]
		if val < target {
			i++
		} else if val > target {
			j--
		} else {
			return true
		}
	}

	return false
}
