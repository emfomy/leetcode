//  Source: https://leetcode.com/problems/unique-paths-ii/
//  Title: Unique Paths II
//  Difficulty: Medium
//  Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an m x n integer array grid. There is a robot initially located at the top-left corner (i.e., grid[0][0]). The robot tries to move to the bottom-right corner (i.e., grid[m-1][n-1]). The robot can only move either down or right at any point in time.
//
// An obstacle and space are marked as 1 or 0 respectively in grid. A path that the robot takes cannot include any square that is an obstacle.
//
// Return the number of possible unique paths that the robot can take to reach the bottom-right corner.
//
// The testcases are generated so that the answer will be less than or equal to 2 * 10^9.
//
// Example 1:
//
//   https://assets.leetcode.com/uploads/2020/11/04/robot1.jpg
//   Input: obstacleGrid = [[0,0,0],[0,1,0],[0,0,0]]
//   Output: 2
//   Explanation:
//     There is one obstacle in the middle of the 3x3 grid above.
//     There are two ways to reach the bottom-right corner:
//     1. Right -> Right -> Down -> Down
//     2. Down -> Down -> Right -> Right
//
//   Example 2:
//
//   https://assets.leetcode.com/uploads/2020/11/04/robot2.jpg
//   Input: obstacleGrid = [[0,1],[0,0]]
//   Output: 1
//
// Constraints:
//
//   m == obstacleGrid.length
//   n == obstacleGrid[i].length
//   1 <= m, n <= 100
//   obstacleGrid[i][j] is 0 or 1.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

func uniquePathsWithObstacles(obstacleGrid [][]int) int {
	m := len(obstacleGrid)
	n := len(obstacleGrid[0])

	dp := make([]int, n)
	dp[0] = 1

	for i := 0; i < m; i++ {
		if obstacleGrid[i][0] != 0 {
			dp[0] = 0
		}
		for j := 1; j < n; j++ {
			if obstacleGrid[i][j] != 0 {
				dp[j] = 0
			} else {
				dp[j] += dp[j-1]
			}
		}
	}

	return dp[n-1]
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Mofidy the grid
func uniquePathsWithObstacles2(obstacleGrid [][]int) int {
	m := len(obstacleGrid)
	n := len(obstacleGrid[0])

	obstacleGrid[0][0] = 1 - obstacleGrid[0][0]

	for j := 1; j < n; j++ {
		if obstacleGrid[0][j] != 0 {
			obstacleGrid[0][j] = 0
		} else {
			obstacleGrid[0][j] += obstacleGrid[0][j-1]
		}
	}

	for i := 1; i < m; i++ {
		if obstacleGrid[i][0] != 0 {
			obstacleGrid[i][0] = 0
		} else {
			obstacleGrid[i][0] += obstacleGrid[i-1][0]
		}
	}

	for i := 1; i < m; i++ {
		for j := 1; j < n; j++ {
			if obstacleGrid[i][j] != 0 {
				obstacleGrid[i][j] = 0
			} else {
				obstacleGrid[i][j] += obstacleGrid[i-1][j] + obstacleGrid[i][j-1]
			}
		}
	}

	return obstacleGrid[m-1][n-1]
}
