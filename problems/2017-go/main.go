// Source: https://leetcode.com/problems/grid-game
// Title: Grid Game
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a **0-indexed** 2D array `grid` of size `2 x n`, where `grid[r][c]` represents the number of points at position `(r, c)` on the matrix. Two robots are playing a game on this matrix.
//
// Both robots initially start at `(0, 0)` and want to reach `(1, n-1)`. Each robot may only move to the **right** (`(r, c)` to `(r, c + 1)`) or **down ** (`(r, c)` to `(r + 1, c)`).
//
// At the start of the game, the **first** robot moves from `(0, 0)` to `(1, n-1)`, collecting all the points from the cells on its path. For all cells `(r, c)` traversed on the path, `grid[r][c]` is set to `0`. Then, the **second** robot moves from `(0, 0)` to `(1, n-1)`, collecting the points on its path. Note that their paths may intersect with one another.
//
// The **first** robot wants to **minimize** the number of points collected by the **second** robot. In contrast, the **second ** robot wants to **maximize** the number of points it collects. If both robots play **optimally** , return the **number of points** collected by the **second** robot.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/09/08/a1.png
//
// ```
// Input: grid = [[2,5,4],[1,5,1]]
// Output: 4
// Explanation: The optimal path taken by the first robot is shown in red, and the optimal path taken by the second robot is shown in blue.
// The cells visited by the first robot are set to 0.
// The second robot will collect 0 + 0 + 4 + 0 = 4 points.
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2021/09/08/a2.png
//
// ```
// Input: grid = [[3,3,1],[8,5,2]]
// Output: 4
// Explanation: The optimal path taken by the first robot is shown in red, and the optimal path taken by the second robot is shown in blue.
// The cells visited by the first robot are set to 0.
// The second robot will collect 0 + 3 + 1 + 0 = 4 points.
// ```
//
// **Example 3:**
// https://assets.leetcode.com/uploads/2021/09/08/a3.png
//
// ```
// Input: grid = [[1,3,1,15],[1,3,3,1]]
// Output: 7
// Explanation: The optimal path taken by the first robot is shown in red, and the optimal path taken by the second robot is shown in blue.
// The cells visited by the first robot are set to 0.
// The second robot will collect 0 + 1 + 3 + 3 + 0 = 7 points.
// ```
//
// **Constraints:**
//
// - `grid.length == 2`
// - `n == grid[r].length`
// - `1 <= n <= 5 * 10^4`
// - `1 <= grid[r][c] <= 10^5`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"math"
)

// Bot1 can only go down once
// After bot 1, bot 2 has only two choice: go top right or bottom left
func gridGame(grid [][]int) int64 {
	n := len(grid[0])

	sumTop := 0
	for _, val := range grid[0] {
		sumTop += val
	}

	res := int64(math.MaxInt64)
	topRight, bottomLeft := int64(sumTop), int64(0)
	for i := 0; i < n; i++ { // bot1 go down at `i`
		topRight -= int64(grid[0][i])
		res = min(res,
			max(
				topRight,   // bot 2 go top right
				bottomLeft, // bot 2 go bottom left
			),
		)
		bottomLeft += int64(grid[1][i])
	}

	return res
}
