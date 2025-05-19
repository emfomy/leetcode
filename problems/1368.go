// Source: https://leetcode.com/problems/minimum-cost-to-make-at-least-one-valid-path-in-a-grid
// Title: Minimum Cost to Make at Least One Valid Path in a Grid
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an `m x n` grid. Each cell of the grid has a sign pointing to the next cell you should visit if you are currently in this cell. The sign of `grid[i][j]` can be:
//
// - `1` which means go to the cell to the right. (i.e go from `grid[i][j]` to `grid[i][j + 1]`)
// - `2` which means go to the cell to the left. (i.e go from `grid[i][j]` to `grid[i][j - 1]`)
// - `3` which means go to the lower cell. (i.e go from `grid[i][j]` to `grid[i + 1][j]`)
// - `4` which means go to the upper cell. (i.e go from `grid[i][j]` to `grid[i - 1][j]`)
//
// Notice that there could be some signs on the cells of the grid that point outside the grid.
//
// You will initially start at the upper left cell `(0, 0)`. A valid path in the grid is a path that starts from the upper left cell `(0, 0)` and ends at the bottom-right cell `(m - 1, n - 1)` following the signs on the grid. The valid path does not have to be the shortest.
//
// You can modify the sign on a cell with `cost = 1`. You can modify the sign on a cell **one time only**.
//
// Return the minimum cost to make the grid have at least one valid path.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2020/02/13/grid1.png
//
// ```
// Input: grid = [[1,1,1,1],[2,2,2,2],[1,1,1,1],[2,2,2,2]]
// Output: 3
// Explanation: You will start at point (0, 0).
// The path to (3, 3) is as follows. (0, 0) --> (0, 1) --> (0, 2) --> (0, 3) change the arrow to down with cost = 1 --> (1, 3) --> (1, 2) --> (1, 1) --> (1, 0) change the arrow to down with cost = 1 --> (2, 0) --> (2, 1) --> (2, 2) --> (2, 3) change the arrow to down with cost = 1 --> (3, 3)
// The total cost = 3.
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2020/02/13/grid2.png
//
// ```
// Input: grid = [[1,1,3],[3,2,2],[1,1,4]]
// Output: 0
// Explanation: You can follow the path from (0, 0) to (2, 2).
// ```
//
// **Example 3:**
// https://assets.leetcode.com/uploads/2020/02/13/grid3.png
//
// ```
// Input: grid = [[1,2],[4,3]]
// Output: 1
// ```
//
// **Constraints:**
//
// - `m == grid.length`
// - `n == grid[i].length`
// - `1 <= m, n <= 100`
// - `1 <= grid[i][j] <= 4`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"container/list"
)

// BFS
func minCost(grid [][]int) int {
	dirs := [][2]int{
		{0, 1},  // right
		{0, -1}, // left
		{1, 0},  // down
		{-1, 0}, // up
	}

	m := len(grid)
	n := len(grid[0])
	scores := make([][]int, m)
	{
		inf := m * n // max score is always less than m*n
		for i := range m {
			scores[i] = make([]int, n)
			for j := range n {
				scores[i][j] = inf
			}
		}
	}

	isValid := func(i, j int) bool {
		return 0 <= i && i < m && 0 <= j && j < n
	}

	deque := list.New()
	deque.PushFront([2]int{})
	scores[0][0] = 0

	for true {
		head := deque.Front()
		if head == nil {
			break
		}
		val := deque.Remove(head).([2]int)
		i, j := val[0], val[1]
		s := scores[i][j]

		if i == m-1 && j == n-1 {
			break
		}

		for d, dir := range dirs {
			ni, nj := i+dir[0], j+dir[1]
			cost := 1
			if d+1 == grid[i][j] {
				cost = 0
			}
			if !isValid(ni, nj) || s+cost >= scores[ni][nj] {
				continue
			}
			scores[ni][nj] = s + cost
			if cost == 0 { // It is better to go with less cost
				deque.PushFront([2]int{ni, nj})
			} else {
				deque.PushBack([2]int{ni, nj})
			}
		}
	}

	return scores[m-1][n-1]
}

// DFS+BFS
//
// We do DFS on 0-cost directions, and do BFS on 1-cost directions
func minCost2(grid [][]int) int {
	dirs := [][2]int{
		{0, 1},  // right
		{0, -1}, // left
		{1, 0},  // down
		{-1, 0}, // up
	}

	m := len(grid)
	n := len(grid[0])
	visited := make([][]bool, m)
	{
		for i := range m {
			visited[i] = make([]bool, n)
		}
	}

	queue := make([][3]int, 0, m*n)

	var dfs func(i, j, s int)
	dfs = func(i, j, s int) {
		if i < 0 || i >= m || j < 0 || j >= n {
			return
		}
		if visited[i][j] {
			return
		}
		visited[i][j] = true
		queue = append(queue, [3]int{i, j, s})
		dir := dirs[grid[i][j]-1]
		dfs(i+dir[0], j+dir[1], s)
	}

	dfs(0, 0, 0)

	for len(queue) > 0 {
		head := queue[0]
		queue = queue[1:]
		if head[0] == m-1 && head[1] == n-1 {
			return head[2]
		}
		for _, dir := range dirs {
			dfs(head[0]+dir[0], head[1]+dir[1], head[2]+1)
		}
	}

	return 0
}
