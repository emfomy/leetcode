// Source: https://leetcode.com/problems/first-completely-painted-row-or-column
// Title: First Completely Painted Row or Column
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a **0-indexed** integer array `arr`, and an `m x n` integer **matrix** `mat`. `arr` and `mat` both contain **all** the integers in the range `[1, m * n]`.
//
// Go through each index `i` in `arr` starting from index `0` and paint the cell in `mat` containing the integer `arr[i]`.
//
// Return the smallest index `i` at which either a row or a column will be completely painted in `mat`.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2023/01/18/grid1.jpg
//
// ```
// Input: arr = [1,3,4,2], mat = [[1,4],[2,3]]
// Output: 2
// Explanation: The moves are shown in order, and both the first row and second column of the matrix become fully painted at arr[2].
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2023/01/18/grid2.jpg
//
// ```
// Input: arr = [2,8,7,4,1,3,5,6,9], mat = [[3,2,5],[1,4,6],[8,7,9]]
// Output: 3
// Explanation: The second column becomes fully painted at arr[3].
// ```
//
// **Constraints:**
//
// - `m == mat.length`
// - `n = mat[i].length`
// - `arr.length == m * n`
// - `1 <= m, n <= 10^5`
// - `1 <= m * n <= 10^5`
// - `1 <= arr[i], mat[r][c] <= m * n`
// - All the integers of `arr` are **unique**.
// - All the integers of `mat` are **unique**.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func firstCompleteIndex(arr []int, mat [][]int) int {
	m, n := len(mat), len(mat[0])

	rowMap := make([]int, m*n+1)
	colMap := make([]int, m*n+1)
	for i, row := range mat {
		for j, num := range row {
			rowMap[num] = i
			colMap[num] = j
		}
	}

	rowCount := make([]int, m)
	colCount := make([]int, n)

	for idx, num := range arr {
		rowCount[rowMap[num]]++
		colCount[colMap[num]]++
		if rowCount[rowMap[num]] == n || colCount[colMap[num]] == m {
			return idx
		}
	}
	return -1
}

func firstCompleteIndex2(arr []int, mat [][]int) int {
	m, n := len(mat), len(mat[0])

	idxMap := make([]int, m*n+1)
	for idx, num := range arr {
		idxMap[num] = idx
	}

	res := m * n
	for i := range m {
		rowMax := idxMap[mat[i][0]]
		for j := 1; j < n; j++ {
			rowMax = max(rowMax, idxMap[mat[i][j]])
		}
		res = min(res, rowMax)
	}
	for j := range n {
		colMax := idxMap[mat[0][j]]
		for i := 1; i < m; i++ {
			colMax = max(colMax, idxMap[mat[i][j]])
		}
		res = min(res, colMax)
	}

	return res
}
