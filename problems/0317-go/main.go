// Source: https://leetcode.com/problems/shortest-distance-from-all-buildings
// Title: Shortest Distance from All Buildings
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an `m x n` grid `grid` of values `0`, `1`, or `2`, where:
//
// - each `0` marks **an empty land** that you can pass by freely,
// - each `1` marks **a building** that you cannot pass through, and
// - each `2` marks **an obstacle** that you cannot pass through.
//
// You want to build a house on an empty land that reaches all buildings in the **shortest total travel** distance. You can only move up, down, left, and right.
//
// Return the **shortest travel distance** for such a house. If it is not possible to build such a house according to the above rules, return `-1`.
//
// The **total travel distance** is the sum of the distances between the houses of the friends and the meeting point.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/03/14/buildings-grid.jpg
//
// ```
// Input: grid = [[1,0,2,0,1],[0,0,0,0,0],[0,0,1,0,0]]
// Output: 7
// Explanation: Given three buildings at (0,0), (0,4), (2,2), and an obstacle at (0,2).
// The point (1,2) is an ideal empty land to build a house, as the total travel distance of 3+3+1=7 is minimal.
// So return 7.
// ```
//
// **Example 2:**
//
// ```
// Input: grid = [[1,0]]
// Output: 1
// ```
//
// **Example 3:**
//
// ```
// Input: grid = [[1]]
// Output: -1
// ```
//
// **Constraints:**
//
// - `m == grid.length`
// - `n == grid[i].length`
// - `1 <= m, n <= 50`
// - `grid[i][j]` is either `0`, `1`, or `2`.
// - There will be **at least one** building in the `grid`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"fmt"
	"math"
)

// Use BFS from empty cells
func shortestDistance(grid [][]int) int {
	m, n := len(grid), len(grid[0])

	visited := make([][]int, m) // visited at round i
	for i := range m {
		visited[i] = make([]int, n)
	}

	// Count building
	buildings := 0
	for x := range m {
		for y := range n {
			if grid[x][y] == 1 {
				buildings++
			}
		}
	}

	// BFS from empty cells
	id := 0
	ans := math.MaxInt
	for x := range m {
		for y := range n {
			if grid[x][y] != 0 { // not empty
				continue
			}
			id++
			dist := 0
			count := 0

			queue := [][3]int{{x, y, 0}} // (x, y, dist)
			for len(queue) > 0 {
				x, y, d := queue[0][0], queue[0][1], queue[0][2]
				queue = queue[1:]
				if visited[x][y] == id {
					continue
				}
				visited[x][y] = id

				if grid[x][y] == 1 { // is building
					dist += d
					count++
					continue
				}

				if x > 0 && visited[x-1][y] != id && grid[x-1][y] != 2 {
					queue = append(queue, [3]int{x - 1, y, d + 1})
				}
				if x < m-1 && visited[x+1][y] != id && grid[x+1][y] != 2 {
					queue = append(queue, [3]int{x + 1, y, d + 1})
				}
				if y > 0 && visited[x][y-1] != id && grid[x][y-1] != 2 {
					queue = append(queue, [3]int{x, y - 1, d + 1})
				}
				if y < n-1 && visited[x][y+1] != id && grid[x][y+1] != 2 {
					queue = append(queue, [3]int{x, y + 1, d + 1})
				}
			}

			if count == buildings {
				ans = min(ans, dist)
			}
		}
	}

	if ans == math.MaxInt {
		return -1
	}
	return ans
}

// Use BFS from buildings
func shortestDistance2(grid [][]int) int {
	m, n := len(grid), len(grid[0])

	visited := make([][]int, m) // visited at round i
	dists := make([][]int, m)   // total distance
	counts := make([][]int, m)  // reachable building count
	for i := range m {
		visited[i] = make([]int, n)
		dists[i] = make([]int, n)
		counts[i] = make([]int, n)
	}

	// Count building
	buildings := 0
	for x := range m {
		for y := range n {
			if grid[x][y] == 1 {
				buildings++
			}
		}
	}

	// BFS from buildings
	id := 0
	for x := range m {
		for y := range n {
			if grid[x][y] != 1 { // not building
				continue
			}
			id++

			queue := [][3]int{{x, y, 0}} // (x, y, dist)
			for len(queue) > 0 {
				x, y, d := queue[0][0], queue[0][1], queue[0][2]
				queue = queue[1:]
				if visited[x][y] == id {
					continue
				}
				visited[x][y] = id
				dists[x][y] += d
				counts[x][y]++

				if x > 0 && visited[x-1][y] != id && grid[x-1][y] == 0 {
					queue = append(queue, [3]int{x - 1, y, d + 1})
				}
				if x < m-1 && visited[x+1][y] != id && grid[x+1][y] == 0 {
					queue = append(queue, [3]int{x + 1, y, d + 1})
				}
				if y > 0 && visited[x][y-1] != id && grid[x][y-1] == 0 {
					queue = append(queue, [3]int{x, y - 1, d + 1})
				}
				if y < n-1 && visited[x][y+1] != id && grid[x][y+1] == 0 {
					queue = append(queue, [3]int{x, y + 1, d + 1})
				}
			}
		}
	}

	// Answer
	ans := math.MaxInt
	for x := range m {
		for y := range n {
			if grid[x][y] != 0 { // not empty
				continue
			}
			if counts[x][y] < buildings { // not reachable to all building
				continue
			}
			ans = min(ans, dists[x][y])
		}
	}

	if ans == math.MaxInt {
		return -1
	}
	return ans
}

// Use BFS from buildings
//
// Note that if a cell is not reachable by previous building,
// we can ignore it since it won't be the answer.
func shortestDistance3(grid [][]int) int {
	m, n := len(grid), len(grid[0])

	visited := make([][]int, m) // visited at round i
	dists := make([][]int, m)   // total distance
	for i := range m {
		visited[i] = make([]int, n)
		dists[i] = make([]int, n)
	}

	// Count building
	buildings := 0
	for x := range m {
		for y := range n {
			if grid[x][y] == 1 {
				buildings++
			}
		}
	}

	// BFS from buildings
	id := 0
	for x := range m {
		for y := range n {
			if grid[x][y] != 1 { // not building
				continue
			}
			id++

			visited[x][y] = id - 1
			queue := [][3]int{{x, y, 0}} // (x, y, dist)
			for len(queue) > 0 {
				x, y, d := queue[0][0], queue[0][1], queue[0][2]
				queue = queue[1:]
				if visited[x][y] != id-1 {
					continue
				}
				visited[x][y] = id
				dists[x][y] += d

				if x > 0 && visited[x-1][y] == id-1 && grid[x-1][y] == 0 {
					queue = append(queue, [3]int{x - 1, y, d + 1})
				}
				if x < m-1 && visited[x+1][y] == id-1 && grid[x+1][y] == 0 {
					queue = append(queue, [3]int{x + 1, y, d + 1})
				}
				if y > 0 && visited[x][y-1] == id-1 && grid[x][y-1] == 0 {
					queue = append(queue, [3]int{x, y - 1, d + 1})
				}
				if y < n-1 && visited[x][y+1] == id-1 && grid[x][y+1] == 0 {
					queue = append(queue, [3]int{x, y + 1, d + 1})
				}
			}
		}
	}

	// Answer
	ans := math.MaxInt
	for x := range m {
		for y := range n {
			if grid[x][y] != 0 { // not empty
				continue
			}
			if visited[x][y] != buildings { // not reachable to all building
				continue
			}
			ans = min(ans, dists[x][y])
		}
	}

	if ans == math.MaxInt {
		return -1
	}
	return ans
}

// Use BFS from buildings
//
// Note that if a cell is not reachable by previous building,
// we can ignore it since it won't be the answer.
func shortestDistance4(grid [][]int) int {
	m, n := len(grid), len(grid[0])

	dists := make([][]int, m) // total distance
	for i := range m {
		dists[i] = make([]int, n)
	}

	// Count building
	buildings := 0
	for x := range m {
		for y := range n {
			if grid[x][y] == 1 {
				buildings++
			}
		}
	}

	dirs := [][2]int{
		{-1, 0},
		{1, 0},
		{0, -1},
		{0, 1},
	}

	// BFS from buildings
	emptyVal := 0
	for x := range m {
		for y := range n {
			if grid[x][y] != 1 { // not building
				continue
			}

			currQueue := [][2]int{{x, y}}
			dist := 1
			for len(currQueue) > 0 {
				var nextQueue [][2]int
				for _, cell := range currQueue {
					for _, dir := range dirs {
						x := cell[0] + dir[0]
						y := cell[1] + dir[1]
						if x < 0 || x >= m || y < 0 || y >= n {
							continue
						}

						if grid[x][y] != emptyVal {
							continue
						}

						grid[x][y]--
						dists[x][y] += dist
						nextQueue = append(nextQueue, [2]int{x, y})
					}
				}
				currQueue = nextQueue
				dist++
			}
			emptyVal--
		}
	}

	// Answer
	ans := math.MaxInt
	for x := range m {
		for y := range n {
			if grid[x][y] != emptyVal {
				continue
			}
			ans = min(ans, dists[x][y])
		}
	}

	if ans == math.MaxInt {
		return -1
	}
	return ans
}

func main() {
	fmt.Println(shortestDistance4([][]int{
		{1, 0, 2, 0, 1},
		{0, 0, 0, 0, 0},
		{0, 0, 1, 0, 0},
	}))
}
