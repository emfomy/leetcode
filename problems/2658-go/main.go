// Source: https://leetcode.com/problems/maximum-number-of-fish-in-a-grid
// Title: Maximum Number of Fish in a Grid
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a **0-indexed** 2D matrix `grid` of size `m x n`, where `(r, c)` represents:
//
// - A **land** cell if `grid[r][c] = 0`, or
// - A **water** cell containing `grid[r][c]` fish, if `grid[r][c] > 0`.
//
// A fisher can start at any **water** cell `(r, c)` and can do the following operations any number of times:
//
// - Catch all the fish at cell `(r, c)`, or
// - Move to any adjacent **water** cell.
//
// Return the **maximum** number of fish the fisher can catch if he chooses his starting cell optimally, or `0` if no water cell exists.
//
// An **adjacent** cell of the cell `(r, c)`, is one of the cells `(r, c + 1)`, `(r, c - 1)`, `(r + 1, c)` or `(r - 1, c)` if it exists.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2023/03/29/example.png
//
// ```
// Input: grid = [[0,2,1,0],[4,0,0,3],[1,0,0,4],[0,3,2,0]]
// Output: 7
// Explanation: The fisher can start at cell `(1,3)` and collect 3 fish, then move to cell `(2,3)`and collect 4 fish.
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2023/03/29/example2.png
//
// ```
// Input: grid = [[1,0,0,0],[0,0,0,0],[0,0,0,0],[0,0,0,1]]
// Output: 1
// Explanation: The fisher can start at cells (0,0) or (3,3) and collect a single fish.
// ```
//
// **Constraints:**
//
// - `m == grid.length`
// - `n == grid[i].length`
// - `1 <= m, n <= 10`
// - `0 <= grid[i][j] <= 10`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"slices"
)

// Use union-find to find the connected component
func findMaxFish(grid [][]int) int {
	m, n := len(grid), len(grid[0])
	mn := m * n

	// Union-Find
	parent := make([]int, mn)
	size := make([]int, mn)
	value := make([]int, mn)
	for x := range mn {
		parent[x] = x
		size[x] = 1
		value[x] = grid[x/n][x%n]
	}

	// Find
	var find func(int) int
	find = func(x int) int { // path compression
		if x != parent[x] {
			parent[x] = find(parent[x])
		}
		return parent[x]
	}

	// Union
	union := func(x, y int) { // union with size
		x = find(x)
		y = find(y)
		if x == y {
			return
		}

		if size[x] < size[y] {
			x, y = y, x
		}

		parent[y] = x
		size[x] += size[y]
		value[x] += value[y]
	}

	// Run
	dirs := [][2]int{
		{1, 0},
		{0, 1},
		{-1, 0},
		{0, -1},
	}
	for i := range m {
		for j := range n {
			if grid[i][j] == 0 {
				continue
			}
			ij := i*n + j
			for _, dir := range dirs {
				i2, j2 := i+dir[0], j+dir[1]
				if 0 <= i2 && i2 < m && 0 <= j2 && j2 < n && grid[i2][j2] > 0 {
					ij2 := i2*n + j2
					union(ij, ij2)
				}
			}
		}
	}

	return slices.Max(value)
}

// Use DFS to find the connected component
func findMaxFish2(grid [][]int) int {
	m, n := len(grid), len(grid[0])

	dirs := [][2]int{
		{1, 0},
		{0, 1},
		{-1, 0},
		{0, -1},
	}

	// DFS
	var dfs func(int, int) int
	dfs = func(i, j int) int {
		if grid[i][j] == 0 {
			return 0
		}

		score := grid[i][j]
		grid[i][j] = 0
		for _, dir := range dirs {
			i2, j2 := i+dir[0], j+dir[1]
			if 0 <= i2 && i2 < m && 0 <= j2 && j2 < n && grid[i2][j2] > 0 {
				score += dfs(i2, j2)
			}
		}
		return score
	}

	// Run
	maxScore := 0
	for i := range m {
		for j := range n {
			if grid[i][j] > 0 {
				maxScore = max(maxScore, dfs(i, j))
			}
		}
	}

	return maxScore
}
