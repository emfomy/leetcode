// Source: https://leetcode.com/problems/max-area-of-island
// Title: Max Area of Island
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an m x n binary matrix grid. An island is a group of 1's (representing land) connected 4-directionally (horizontal or vertical.) You may assume all four edges of the grid are surrounded by water.
//
// The area of an island is the number of cells with a value 1 in the island.
//
// Return the maximum area of an island in grid. If there is no island, return 0.
//
// Example 1:
//
//   https://assets.leetcode.com/uploads/2021/05/01/maxarea1-grid.jpg
//
//   Input: grid = [[0,0,1,0,0,0,0,1,0,0,0,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,1,1,0,1,0,0,0,0,0,0,0,0],[0,1,0,0,1,1,0,0,1,0,1,0,0],[0,1,0,0,1,1,0,0,1,1,1,0,0],[0,0,0,0,0,0,0,0,0,0,1,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,0,0,0,0,0,0,1,1,0,0,0,0]]
//   Output: 6
//   Explanation: The answer is not 11, because the island must be connected 4-directionally.
//
// Example 2:
//
//   Input: grid = [[0,0,0,0,0,0,0,0]]
//   Output: 0
//
// Constraints:
//
//   m == grid.length
//   n == grid[i].length
//   1 <= m, n <= 50
//   grid[i][j] is either 0 or 1.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func maxAreaOfIsland(grid [][]int) int {
	res := 0
	m := len(grid)
	n := len(grid[0])

	for i, row := range grid {
		for j, v := range row {
			if v == 1 {
				res = _max(res, _getIslandArea(grid, m, n, i, j))
			}
		}
	}

	return res
}

func _getIslandArea(grid [][]int, m, n, i, j int) int {
	res := 1
	grid[i][j] = 0

	if i > 0 && grid[i-1][j] == 1 {
		res += _getIslandArea(grid, m, n, i-1, j)
	}
	if i < m-1 && grid[i+1][j] == 1 {
		res += _getIslandArea(grid, m, n, i+1, j)
	}
	if j > 0 && grid[i][j-1] == 1 {
		res += _getIslandArea(grid, m, n, i, j-1)
	}
	if j < n-1 && grid[i][j+1] == 1 {
		res += _getIslandArea(grid, m, n, i, j+1)
	}

	return res
}

func _max(a, b int) int {
	if a > b {
		return a
	}
	return b
}
