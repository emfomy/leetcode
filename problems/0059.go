// Source: https://leetcode.com/problems/spiral-matrix-ii
// Title: Spiral Matrix II
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a positive integer n, generate an n x n matrix filled with elements from 1 to n^2 in spiral order.
//
// Example 1:
//
//   https://assets.leetcode.com/uploads/2020/11/13/spiraln.jpg
//
//   Input: n = 3
//   Output: [[1,2,3],[8,9,4],[7,6,5]]
//
// Example 2:
//
//   Input: n = 1
//   Output: [[1]]
//
// Constraints:
//
//   1 <= n <= 20
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func generateMatrix(n int) [][]int {
	matrix := make([][]int, n)
	for i := 0; i < n; i++ {
		matrix[i] = make([]int, n)
	}

	// boundaries
	north := 0
	south := n - 1
	west := 0
	east := n - 1

	// spiral
	i := 1
	for true {
		// Right
		if west > east {
			break
		}
		{
			y := north
			for x := west; x <= east; x++ {
				matrix[y][x] = i
				i++
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
				matrix[y][x] = i
				i++
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
				matrix[y][x] = i
				i++
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
				matrix[y][x] = i
				i++
			}
			west++
		}
	}

	return matrix
}
