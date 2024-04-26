// Source: https://leetcode.com/problems/number-of-submatrices-that-sum-to-target/
// Title: Number of Submatrices That Sum to Target
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a matrix and a target, return the number of non-empty submatrices that sum to target.
//
// A submatrix x1, y1, x2, y2 is the set of all cells matrix[x][y] with x1 <= x <= x2 and y1 <= y <= y2.
//
// Two submatrices (x1, y1, x2, y2) and (x1', y1', x2', y2') are different if they have some coordinate that is different: for example, if x1 != x1'.
//
// Example 1:
//
//   Input: matrix = [[0,1,0],[1,1,1],[0,1,0]], target = 0
//   Output: 4
//   Explanation: The four 1x1 submatrices that only contain 0.
//
// Example 2:
//
//   Input: matrix = [[1,-1],[-1,1]], target = 0
//   Output: 5
//   Explanation: The two 1x2 submatrices, plus the two 2x1 submatrices, plus the 2x2 submatrix.
//
// Example 3:
//
//   Input: matrix = [[904]], target = 0
//   Output: 0
//
// Constraints:
//
//   1 <= matrix.length <= 100
//   1 <= matrix[0].length <= 100
//   -1000 <= matrix[i] <= 1000
//   -10^8 <= target <= 10^8
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func numSubmatrixSumTarget(matrix [][]int, target int) int {
	m := len(matrix)
	n := len(matrix[0])

	// Compute prefix sums
	presum := make([][]int, m+1)
	for i := 0; i < m+1; i++ {
		presum[i] = make([]int, n+1)
	}
	for i := 0; i < m; i++ {
		for j := 0; j < n; j++ {
			presum[i+1][j+1] = matrix[i][j] + presum[i][j+1] + presum[i+1][j] - presum[i][j]
		}
	}

	// Check submatrix sum
	res := 0
	for x1 := 0; x1 < m; x1++ {
		for x2 := x1 + 1; x2 <= m; x2++ {
			for y1 := 0; y1 < n; y1++ {
				for y2 := y1 + 1; y2 <= n; y2++ {
					subsum := presum[x2][y2] - presum[x2][y1] - presum[x1][y2] + presum[x1][y1]
					if subsum == target {
						res++
					}
				}
			}
		}
	}

	return res
}
