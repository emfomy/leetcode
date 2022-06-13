// Source: https://leetcode.com/problems/pascals-triangle/
// Title: Pascal's Triangle
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer numRows, return the first numRows of Pascal's triangle.
//
// In Pascal's triangle, each number is the sum of the two numbers directly above it as shown:
//
//   https://upload.wikimedia.org/wikipedia/commons/0/0d/PascalTriangleAnimated2.gif
//
// Example 1:
//
//   Input: numRows = 5
//   Output: [[1],[1,1],[1,2,1],[1,3,3,1],[1,4,6,4,1]]
//
// Example 2:
//
//   Input: numRows = 1
//   Output: [[1]]
//
// Constraints:
//
//   1 <= numRows <= 30
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func generate(numRows int) [][]int {
	triangle := make([][]int, numRows)
	triangle[0] = []int{1}

	for i := 1; i < numRows; i++ {
		triangle[i] = make([]int, i+1)

		triangle[i][0] = 1
		for j := 1; j < i; j++ {
			triangle[i][j] = triangle[i-1][j] + triangle[i-1][j-1]
		}
		triangle[i][i] = 1
	}
	return triangle
}
