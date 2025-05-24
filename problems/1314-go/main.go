// Source: https://leetcode.com/problems/matrix-block-sum
// Title: Matrix Block Sum
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a m x n matrix mat and an integer k, return a matrix answer where each answer[i][j] is the sum of all elements mat[r][c] for:
//
//   i - k <= r <= i + k,
//   j - k <= c <= j + k, and
//   (r, c) is a valid position in the matrix.
//
// Example 1:
//
//   Input: mat = [[1,2,3],[4,5,6],[7,8,9]], k = 1
//   Output: [[12,21,16],[27,45,33],[24,39,28]]
//
// Example 2:
//
//   Input: mat = [[1,2,3],[4,5,6],[7,8,9]], k = 2
//   Output: [[45,45,45],[45,45,45],[45,45,45]]
//
// Constraints:
//
//   m == mat.length
//   n == mat[i].length
//   1 <= m, n, k <= 100
//   1 <= mat[i][j] <= 100
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Naive
func matrixBlockSum(mat [][]int, k int) [][]int {
	m := len(mat)
	n := len(mat[0])

	ans := make([][]int, m)
	for i := 0; i < m; i++ {
		ans[i] = make([]int, n)
	}

	for i := 0; i < m; i++ {
		for j := 0; j < n; j++ {
			for r := _max(i-k, 0); r <= _min(i+k, m-1); r++ {
				for c := _max(j-k, 0); c <= _min(j+k, n-1); c++ {
					ans[i][j] += mat[r][c]
				}
			}
		}
	}

	return ans
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Prefix sum
func matrixBlockSum2(mat [][]int, k int) [][]int {
	m := len(mat)
	n := len(mat[0])

	// Compute prefix sums
	sum := make([][]int, m+1)
	for i := 0; i < m+1; i++ {
		sum[i] = make([]int, n+1)
	}
	for i := 0; i < m; i++ {
		for j := 0; j < n; j++ {
			sum[i+1][j+1] = mat[i][j] + sum[i][j+1] + sum[i+1][j] - sum[i][j]
		}
	}

	// Compute block sum
	ans := make([][]int, m)
	for i := 0; i < m; i++ {
		ans[i] = make([]int, n)
	}
	for i := 0; i < m; i++ {
		for j := 0; j < n; j++ {
			r1 := _max(0, i-k)
			c1 := _max(0, j-k)
			r2 := _min(m, i+k+1)
			c2 := _min(n, j+k+1)
			ans[i][j] = sum[r2][c2] - sum[r2][c1] - sum[r1][c2] + sum[r1][c1]
		}
	}

	return ans
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

func _max(a, b int) int {
	if a > b {
		return a
	}
	return b
}

func _min(a, b int) int {
	if a < b {
		return a
	}
	return b
}
