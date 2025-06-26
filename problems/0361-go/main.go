// Source: https://leetcode.com/problems/bomb-enemy
// Title: Bomb Enemy
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an `m x n` matrix `grid` where each cell is either a wall `'W'`, an enemy `'E'` or empty `'0'`, return the maximum enemies you can kill using one bomb. You can only place the bomb in an empty cell.
//
// The bomb kills all the enemies in the same row and column from the planted point until it hits the wall since it is too strong to be destroyed.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/03/27/bomb1-grid.jpg
//
// ```
// Input: grid = [["0","E","0","0"],["E","0","W","E"],["0","E","0","0"]]
// Output: 3
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2021/03/27/bomb2-grid.jpg
//
// ```
// Input: grid = [["W","W","W"],["0","0","0"],["E","E","E"]]
// Output: 1
// ```
//
// **Constraints:**
//
// - `m == grid.length`
// - `n == grid[i].length`
// - `1 <= m, n <= 500`
// - `grid[i][j]` is either `'W'`, `'E'`, or `'0'`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func maxKilledEnemies(grid [][]byte) int {
	m, n := len(grid), len(grid[0])
	kills := make([][]int, m)
	for i := range m {
		kills[i] = make([]int, n)
	}

	for i := range m {
		{ // from left to right
			kill := 0
			for j := 0; j < n; j++ {
				switch grid[i][j] {
				case '0':
					kills[i][j] += kill
				case 'E':
					kill++
				case 'W':
					kill = 0
				}
			}
		}

		{ // from right to left
			kill := 0
			for j := n - 1; j >= 0; j-- {
				switch grid[i][j] {
				case '0':
					kills[i][j] += kill
				case 'E':
					kill++
				case 'W':
					kill = 0
				}
			}
		}
	}

	for j := range n {
		{ // from top to bottom
			kill := 0
			for i := 0; i < m; i++ {
				switch grid[i][j] {
				case '0':
					kills[i][j] += kill
				case 'E':
					kill++
				case 'W':
					kill = 0
				}
			}
		}

		{ // from bottom to top
			kill := 0
			for i := m - 1; i >= 0; i-- {
				switch grid[i][j] {
				case '0':
					kills[i][j] += kill
				case 'E':
					kill++
				case 'W':
					kill = 0
				}
			}
		}
	}

	// Find answer
	ans := 0
	for _, row := range kills {
		for _, kill := range row {
			ans = max(ans, kill)
		}
	}
	return ans
}

func maxKilledEnemies2(grid [][]byte) int {
	m, n := len(grid), len(grid[0])

	ans := 0
	rowKills := 0
	colKills := make([]int, n)

	for i := range m {
		for j := range n {
			// Recompute rowKills
			if j == 0 || grid[i][j-1] == 'W' {
				rowKills = 0
				for k := j; k < n && grid[i][k] != 'W'; k++ {
					if grid[i][k] == 'E' {
						rowKills++
					}
				}
			}

			// Recompute colKills
			if i == 0 || grid[i-1][j] == 'W' {
				colKills[j] = 0
				for k := i; k < m && grid[k][j] != 'W'; k++ {
					if grid[k][j] == 'E' {
						colKills[j]++
					}
				}
			}

			// Place bomb
			if grid[i][j] == '0' {
				ans = max(ans, rowKills+colKills[j])
			}
		}
	}

	return ans
}
