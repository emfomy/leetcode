// Source: https://leetcode.com/problems/set-matrix-zeroes
// Title: Set Matrix Zeroes
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an `m x n` integer matrix `matrix`, if an element is `0`, set its entire row and column to `0`'s.
//
// You must do it in place.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2020/08/17/mat1.jpg
//
// ```
// Input: matrix = [[1,1,1],[1,0,1],[1,1,1]]
// Output: [[1,0,1],[0,0,0],[1,0,1]]
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2020/08/17/mat2.jpg
//
// ```
// Input: matrix = [[0,1,2,0],[3,4,5,2],[1,3,1,5]]
// Output: [[0,0,0,0],[0,4,5,0],[0,3,1,0]]
// ```
//
// **Constraints:**
//
// - `m == matrix.length`
// - `n == matrix[0].length`
// - `1 <= m, n <= 200`
// - `-2^31 <= matrix[i][j] <= 2^31 - 1`
//
// **Follow up:**
//
// - A straightforward solution using `O(mn)` space is probably a bad idea.
// - A simple improvement uses `O(m + n)` space, but still not the best solution.
// - Could you devise a constant space solution?
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// O(m+n) space
func setZeroes(matrix [][]int) {
	m, n := len(matrix), len(matrix[0])
	zeroCols := make([]bool, m)
	zeroRows := make([]bool, n)

	for i := range m {
		for j := range n {
			if matrix[i][j] == 0 {
				zeroCols[i] = true
				zeroRows[j] = true
			}
		}
	}

	for i := range m {
		if zeroCols[i] {
			for j := range n {
				matrix[i][j] = 0
			}
		}
	}

	for j := range n {
		if zeroRows[j] {
			for i := range m {
				matrix[i][j] = 0
			}
		}
	}
}

// O(1) space
func setZeroes2(matrix [][]int) {
	m, n := len(matrix), len(matrix[0])

	// First check if the first row has zeros.
	firstHasZero := false
	for j := range n {
		if matrix[0][j] == 0 {
			firstHasZero = true
			break
		}
	}

	// Next loop through each row and check if it has zeros,
	// and then set it to zero (if needed).
	// Simultaneously, use the first row to store whether each column has zeros.
	for i := 1; i < m; i++ {
		hasZero := false
		for j := range n {
			if matrix[i][j] == 0 {
				hasZero = true
				matrix[0][j] = 0
			}
		}
		if hasZero {
			for j := range n {
				matrix[i][j] = 0
			}
		}
	}

	// Next set the each column to zero based on the first row.
	for j := range n {
		if matrix[0][j] == 0 {
			for i := 1; i < m; i++ {
				matrix[i][j] = 0
			}
		}
	}

	// Finally set the first row to zero (if needed).
	if firstHasZero {
		for j := range n {
			matrix[0][j] = 0
		}
	}
}
