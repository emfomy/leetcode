// Source: https://leetcode.com/problems/making-a-large-island
// Title: Making A Large Island
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an `n x n` binary matrix `grid`. You are allowed to change **at most one** `0` to be `1`.
//
// Return the size of the largest **island** in `grid` after applying this operation.
//
// An **island** is a 4-directionally connected group of `1`s.
//
// **Example 1:**
//
// ```
// Input: grid = [[1,0],[0,1]]
// Output: 3
// Explanation: Change one 0 to 1 and connect two 1s, then we get an island with area = 3.
// ```
//
// **Example 2:**
//
// ```
// Input: grid = [[1,1],[1,0]]
// Output: 4
// Explanation: Change the 0 to 1 and make the island bigger, only one island with area = 4.```
//
// **Example 3:**
//
// ```
// Input: grid = [[1,1],[1,1]]
// Output: 4
// Explanation: Can't change any 0 to 1, only one island with area = 4.
// ```
//
// **Constraints:**
//
// - `n == grid.length`
// - `n == grid[i].length`
// - `1 <= n <= 500`
// - `grid[i][j]` is either `0` or `1`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// Use union-find
func largestIsland(grid [][]int) int {
	n := len(grid)

	// Prepare
	parent := make([]int, n*n)
	size := make([]int, n*n)
	for x := range n * n {
		parent[x] = x
		size[x] = 1
	}

	// Find
	var find func(int) int
	find = func(x int) int {
		if parent[x] != x {
			parent[x] = find(parent[x])
		}
		return parent[x]
	}

	// Union
	var union func(int, int)
	union = func(x, y int) {
		x = find(x)
		y = find(y)

		if x == y {
			return
		}

		if size[x] < size[y] {
			x, y = y, x
		}

		parent[y] = parent[x]
		size[x] += size[y]
	}

	// Run
	dirs := [][2]int{
		{1, 0},
		{0, 1},
		{-1, 0},
		{0, -1},
	}
	for i := range n {
		for j := range n {
			if grid[i][j] != 1 {
				continue
			}
			for _, dir := range dirs {
				i2, j2 := i+dir[0], j+dir[1]
				if 0 <= i2 && i2 < n && 0 <= j2 && j2 < n && grid[i2][j2] == 1 {
					union(i*n+j, i2*n+j2)
				}
			}
		}
	}

	// Find largest
	res := 0
	for i := range n {
		for j := range n {
			if grid[i][j] != 1 {
				continue
			}
			x := i*n + j
			if parent[x] == x {
				res = max(res, size[x])
			}
		}
	}

	// Filp
	for i := range n {
		for j := range n {
			if grid[i][j] != 0 {
				continue
			}
			xs := make(map[int]bool, 4)
			for _, dir2 := range dirs {
				i2, j2 := i+dir2[0], j+dir2[1]
				if !(0 <= i2 && i2 < n && 0 <= j2 && j2 < n && grid[i2][j2] == 1) {
					continue
				}
				x := find(i2*n + j2)
				xs[x] = true
			}
			area := 1
			for x := range xs {
				area += size[x]
			}
			res = max(res, area)
		}
	}

	return res
}

// Use DFS
func largestIsland2(grid [][]int) int {
	n := len(grid)

	// Prepare
	islandID := 2 // start from 2
	islandSizes := make(map[int]int)
	dirs := [][2]int{
		{1, 0},
		{0, 1},
		{-1, 0},
		{0, -1},
	}

	// DFS
	var dfs func(i, j int) int
	dfs = func(i, j int) int {
		if !(0 <= i && i < n && 0 <= j && j < n) || grid[i][j] != 1 {
			return 0
		}

		grid[i][j] = islandID
		size := 1
		for _, dir := range dirs {
			size += dfs(i+dir[0], j+dir[1])
		}
		return size
	}

	// Run
	for i := range n {
		for j := range n {
			if grid[i][j] != 1 {
				continue
			}
			islandSizes[islandID] = dfs(i, j)
			islandID++
		}
	}

	// Find largest island
	res := 0
	for _, size := range islandSizes {
		res = max(res, size)
	}

	// Filp
	for i := range n {
		for j := range n {
			if grid[i][j] != 0 {
				continue
			}
			neighbors := make(map[int]bool, 4)
			for _, dir2 := range dirs {
				i2, j2 := i+dir2[0], j+dir2[1]
				if !(0 <= i2 && i2 < n && 0 <= j2 && j2 < n) || grid[i2][j2] == 0 {
					continue
				}
				neighbors[grid[i2][j2]] = true
			}
			area := 1
			for island := range neighbors {
				area += islandSizes[island]
			}
			res = max(res, area)
		}
	}

	return res
}
