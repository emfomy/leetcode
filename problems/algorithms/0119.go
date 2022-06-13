// Source: https://leetcode.com/problems/pascals-triangle-ii/
// Title: Pascal's Triangle II
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer rowIndex, return the rowIndexth (0-indexed) row of the Pascal's triangle.
//
// In Pascal's triangle, each number is the sum of the two numbers directly above it as shown:
//
//   https://upload.wikimedia.org/wikipedia/commons/0/0d/PascalTriangleAnimated2.gif
//
// Example 1:
//
//   Input: rowIndex = 3
//   Output: [1,3,3,1]
//
// Example 2:
//
//   Input: rowIndex = 0
//   Output: [1]
//
// Example 3:
//
//   Input: rowIndex = 1
//   Output: [1,1]
//
// Constraints:
//
//   0 <= numRows <= 33
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func getRow(rowIndex int) []int {
	row := make([]int, rowIndex+1)

	for i := 0; i <= rowIndex; i++ {
		row[i] = 1
		for j := i - 1; j > 0; j-- {
			row[j] += row[j-1]
		}
	}

	return row
}
