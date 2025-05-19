// Source: https://leetcode.com/problems/trapping-rain-water-ii
// Title: Trapping Rain Water II
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an `m x n` integer matrix `heightMap` representing the height of each unit cell in a 2D elevation map, return the volume of water it can trap after raining.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/04/08/trap1-3d.jpg
//
// ```
// Input: heightMap = [[1,4,3,1,3,2],[3,2,1,3,2,4],[2,3,3,2,3,1]]
// Output: 4
// Explanation: After the rain, water is trapped between the blocks.
// We have two small ponds 1 and 3 units trapped.
// The total volume of water trapped is 4.
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2021/04/08/trap2-3d.jpg
//
// ```
// Input: heightMap = [[3,3,3,3,3],[3,2,2,2,3],[3,2,1,2,3],[3,2,2,2,3],[3,3,3,3,3]]
// Output: 10
// ```
//
// **Constraints:**
//
// - `m == heightMap.length`
// - `n == heightMap[i].length`
// - `1 <= m, n <= 200`
// - `0 <= heightMap[i][j] <= 2 * 10^4`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"slices"
)

// Use matrix + queue
func trapRainWater(heightMap [][]int) int {
	m := len(heightMap)
	n := len(heightMap[0])

	// Find heightest point
	maxVal := 0
	for i := range m {
		maxVal = max(maxVal, slices.Max(heightMap[i]))
	}

	// Fill water with max val
	water := make([][]int, m+2)
	for i := range m + 2 {
		water[i] = make([]int, n+2)
		for j := range n + 2 {
			water[i][j] = maxVal
		}
	}

	// Remove border waters
	for i := 0; i < m+2; i++ {
		water[i][0] = 0
		water[i][n+1] = 0
	}
	for j := 1; j < n+1; j++ {
		water[0][j] = 0
		water[m+1][j] = 0
	}

	// Queue for indices to update
	queue := make([][3]int, 0, m*n)
	for i := 1; i < m+1; i++ {
		queue = append(queue,
			[3]int{i, 1, water[i][1]},
			[3]int{i, n, water[i][n]},
		)
	}
	for j := 2; j < n; j++ {
		queue = append(queue,
			[3]int{1, j, water[1][j]},
			[3]int{m, j, water[m][j]},
		)
	}

	// Directions
	dirs := [4][2]int{
		{-1, 0},
		{1, 0},
		{0, -1},
		{0, 1},
	}

	for len(queue) > 0 {
		i, j, val := queue[0][0], queue[0][1], queue[0][2]
		queue = queue[1:]

		if val > water[i][j] { // outdated
			continue
		}

		minNeighbor := min(water[i-1][j], water[i+1][j], water[i][j-1], water[i][j+1])
		if water[i][j] <= minNeighbor {
			continue
		}

		water[i][j] = max(minNeighbor, heightMap[i-1][j-1])
		for _, dir := range dirs {
			if water[i+dir[0]][j+dir[1]] > water[i][j] {
				queue = append(queue, [3]int{i + dir[0], j + dir[1], water[i+dir[0]][j+dir[1]]})
			}
		}
	}

	res := 0
	for i := range m {
		for j := range n {
			res += water[i+1][j+1] - heightMap[i][j]
		}
	}

	return res
}
