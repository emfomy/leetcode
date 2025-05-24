// Source: https://leetcode.com/problems/out-of-boundary-paths
// Title: Out of Boundary Paths
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There is an m x n grid with a ball. The ball is initially at the position [startRow, startColumn]. You are allowed to move the ball to one of the four adjacent cells in the grid (possibly out of the grid crossing the grid boundary). You can apply at most maxMove moves to the ball.
//
// Given the five integers m, n, maxMove, startRow, startColumn, return the number of paths to move the ball out of the grid boundary. Since the answer can be very large, return it modulo 10^9 + 7.
//
// Example 1:
//
//   Input: m = 2, n = 2, maxMove = 2, startRow = 0, startColumn = 0
//   Output: 6
//
// Example 2:
//
//   Input: m = 1, n = 3, maxMove = 3, startRow = 0, startColumn = 1
//   Output: 12
//
// Constraints:
//
//   1 <= m, n <= 50
//   0 <= maxMove <= 50
//   0 <= startRow < m
//   0 <= startColumn < n
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

const modulo = int(1e9 + 7)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Use 3D DP
func findPaths(m int, n int, maxMove int, startRow int, startColumn int) int {
	grid := make([][][]int, maxMove+1)
	for k := 0; k <= maxMove; k++ {
		grid[k] = make([][]int, m)
		for i := 0; i < m; i++ {
			grid[k][i] = make([]int, n)
		}
	}

	res := 0
	grid[0][startRow][startColumn] = 1

	for move := 0; move < maxMove; move++ {
		for x := 0; x < m; x++ {
			for y := 0; y < n; y++ {
				v := grid[move][x][y] % modulo
				if v == 0 {
					continue
				}

				if x == 0 {
					res += v
				} else {
					grid[move+1][x-1][y] += v
				}

				if x == m-1 {
					res += v
				} else {
					grid[move+1][x+1][y] += v
				}

				if y == 0 {
					res += v
				} else {
					grid[move+1][x][y-1] += v
				}

				if y == n-1 {
					res += v
				} else {
					grid[move+1][x][y+1] += v
				}
			}
		}
	}

	return res % modulo
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Use 2D DP
func findPaths2(m int, n int, maxMove int, startRow int, startColumn int) int {
	prevGrid := make([][]int, m)
	nextGrid := make([][]int, m)
	for i := 0; i < m; i++ {
		prevGrid[i] = make([]int, n)
		nextGrid[i] = make([]int, n)
	}

	res := 0
	prevGrid[startRow][startColumn] = 1

	for move := 0; move < maxMove; move++ {
		for x := 0; x < m; x++ {
			for y := 0; y < n; y++ {
				v := prevGrid[x][y] % modulo
				if v == 0 {
					continue
				}

				prevGrid[x][y] = 0

				if x == 0 {
					res += v
				} else {
					nextGrid[x-1][y] += v
				}

				if x == m-1 {
					res += v
				} else {
					nextGrid[x+1][y] += v
				}

				if y == 0 {
					res += v
				} else {
					nextGrid[x][y-1] += v
				}

				if y == n-1 {
					res += v
				} else {
					nextGrid[x][y+1] += v
				}
			}
		}
		prevGrid, nextGrid = nextGrid, prevGrid
	}

	return res % modulo
}
