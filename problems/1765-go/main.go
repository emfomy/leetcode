// Source: https://leetcode.com/problems/map-of-highest-peak
// Title: Map of Highest Peak
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer matrix `isWater` of size `m x n` that represents a map of **land** and **water** cells.
//
// - If `isWater[i][j] == 0`, cell `(i, j)` is a **land** cell.
// - If `isWater[i][j] == 1`, cell `(i, j)` is a **water** cell.
//
// You must assign each cell a height in a way that follows these rules:
//
// - The height of each cell must be non-negative.
// - If the cell is a **water** cell, its height must be `0`.
// - Any two adjacent cells must have an absolute height difference of **at most** `1`. A cell is adjacent to another cell if the former is directly north, east, south, or west of the latter (i.e., their sides are touching).
//
// Find an assignment of heights such that the maximum height in the matrix is **maximized**.
//
// Return an integer matrix `height` of size `m x n` where `height[i][j]` is cell `(i, j)`'s height. If there are multiple solutions, return **any** of them.
//
// **Example 1:**
//
// **<img alt="" src="https://assets.leetcode.com/uploads/2021/01/10/screenshot-2021-01-11-at-82045-am.png" style="width: 220px; height: 219px;">**
//
// ```
// Input: isWater = [[0,1],[0,0]]
// Output: [[1,0],[2,1]]
// Explanation: The image shows the assigned heights of each cell.
// The blue cell is the water cell, and the green cells are the land cells.
// ```
//
// **Example 2:**
//
// **<img alt="" src="https://assets.leetcode.com/uploads/2021/01/10/screenshot-2021-01-11-at-82050-am.png" style="width: 300px; height: 296px;">**
//
// ```
// Input: isWater = [[0,0,1],[1,0,0],[0,0,0]]
// Output: [[1,1,0],[0,1,1],[1,2,2]]
// Explanation: A height of 2 is the maximum possible height of any assignment.
// Any height assignment that has a maximum height of 2 while still meeting the rules will also be accepted.
// ```
//
// **Constraints:**
//
// - `m == isWater.length`
// - `n == isWater[i].length`
// - `1 <= m, n <= 1000`
// - `isWater[i][j]` is `0` or `1`.
// - There is at least **one** water cell.
//
// **Note:** This question is the same as 542: https://leetcode.com/problems/01-matrix
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// BFS
func highestPeak(isWater [][]int) [][]int {
	m, n := len(isWater), len(isWater[0])
	queue := make([][3]int, 0, m*n)

	height := make([][]int, m)
	for i := range m {
		height[i] = make([]int, n)
	}

	for i := range m {
		for j := range n {
			if isWater[i][j] == 1 {
				queue = append(queue, [3]int{i, j, 0})
			}
		}
	}

	dirs := [][2]int{
		{-1, 0}, // left
		{1, 0},  // right
		{0, -1}, //up
		{0, 1},  //down
	}

	for len(queue) > 0 {
		i, j, h := queue[0][0], queue[0][1], queue[0][2]
		queue = queue[1:]

		for _, dir := range dirs {
			ni, nj, nh := i+dir[0], j+dir[1], h+1

			if ni < 0 || ni >= m || nj < 0 || nj >= n { // out of border
				continue
			}
			if isWater[ni][nj] == 1 || height[ni][nj] > 0 { // visited
				continue
			}

			height[ni][nj] = nh
			queue = append(queue, [3]int{ni, nj, nh})
		}
	}

	return height
}
