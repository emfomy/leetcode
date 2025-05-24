// Source: https://leetcode.com/problems/spiral-matrix
// Title: Spiral Matrix
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an m x n matrix, return all elements of the matrix in spiral order.
//
// Example 1:
//
//   https://assets.leetcode.com/uploads/2020/11/13/spiral1.jpg
//
//   Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
//   Output: [1,2,3,6,9,8,7,4,5]
//
// Example 2:
//
//   https://assets.leetcode.com/uploads/2020/11/13/spiral.jpg
//
//   Input: matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
//   Output: [1,2,3,4,8,12,11,10,9,5,6,7]
//
// Constraints:
//
//   m == matrix.length
//   n == matrix[i].length
//   1 <= m, n <= 10
//   -100 <= matrix[i][j] <= 100
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func spiralOrder(matrix [][]int) []int {
	m := len(matrix)
	n := len(matrix[0])

	// boundaries
	north := 0
	south := m - 1
	west := 0
	east := n - 1

	// spiral
	res := make([]int, 0, m*n)
	for true {
		// Right
		if west > east {
			break
		}
		{
			y := north
			for x := west; x <= east; x++ {
				res = append(res, matrix[y][x])
			}
			north++
		}

		// Down
		if north > south {
			break
		}
		{
			x := east
			for y := north; y <= south; y++ {
				res = append(res, matrix[y][x])
			}
			east--
		}

		// Left
		if west > east {
			break
		}
		{
			y := south
			for x := east; x >= west; x-- {
				res = append(res, matrix[y][x])
			}
			south--
		}

		// Up
		if north > south {
			break
		}
		{
			x := west
			for y := south; y >= north; y-- {
				res = append(res, matrix[y][x])
			}
			west++
		}
	}

	return res
}
