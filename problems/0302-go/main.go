// Source: https://assets.leetcode.com/uploads/2021/03/14/pixel-grid.jpg
// Title: Smallest Rectangle Enclosing Black Pixels
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an `m x n` binary matrix `image` where `0` represents a white pixel and `1` represents a black pixel.
//
// The black pixels are connected (i.e., there is only one black region). Pixels are connected horizontally and vertically.
//
// Given two integers `x` and `y` that represents the location of one of the black pixels, return the area of the smallest (axis-aligned) rectangle that encloses all black pixels.
//
// You must write an algorithm with less than `O(mn)` runtime complexity
//
// **Example 1:**
//
// ```
// Input: image = [["0","0","1","0"],["0","1","1","0"],["0","1","0","0"]], x = 0, y = 2
// Output: 6
// ```
//
// **Example 2:**
//
// ```
// Input: image = [["1"]], x = 0, y = 0
// Output: 1
// ```
//
// **Constraints:**
//
// - `m == image.length`
// - `n == image[i].length`
// - `1 <= m, n <= 100`
// - `image[i][j]` is either `'0'` or `'1'`.
// - `0 <= x < m`
// - `0 <= y < n`
// - `image[x][y] == '1'.`
// - The black pixels in the `image` only form **one component**.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// Find the top/down/left/right-most index.
func minArea(image [][]byte, x int, y int) int {
	m, n := len(image), len(image[0])

	xmin, xmax, ymin, ymax := x, x, y, y
	for i := range m {
		for j := range n {
			if image[i][j] == '1' {
				xmin = min(xmin, i)
				xmax = max(xmax, i)
				ymin = min(ymin, j)
				ymax = max(ymax, j)
			}
		}
	}

	return (xmax - xmin + 1) * (ymax - ymin + 1)
}

// Use BFS
func minArea2(image [][]byte, x int, y int) int {
	m, n := len(image), len(image[0])

	visited := make([][]bool, m)
	for i := range m {
		visited[i] = make([]bool, n)
	}

	valid := func(xx, yy int) bool {
		return 0 <= xx && xx < m && 0 <= yy && yy < n &&
			image[xx][yy] == '1' && !visited[xx][yy]
	}

	dirs := [4][2]int{
		{-1, 0},
		{1, 0},
		{0, -1},
		{0, 1},
	}

	var queue [][2]int
	queue = append(queue, [2]int{x, y})
	visited[x][y] = true
	xmin, xmax, ymin, ymax := x, x, y, y
	for len(queue) > 0 {
		curr := queue[0]
		queue = queue[1:]

		for _, dir := range dirs {
			nx, ny := curr[0]+dir[0], curr[1]+dir[1]
			if valid(nx, ny) {
				visited[nx][ny] = true
				queue = append(queue, [2]int{nx, ny})
				xmin = min(xmin, nx)
				xmax = max(xmax, nx)
				ymin = min(ymin, ny)
				ymax = max(ymax, ny)
			}
		}
	}

	return (xmax - xmin + 1) * (ymax - ymin + 1)
}
