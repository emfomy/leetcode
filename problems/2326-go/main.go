// Source: https://leetcode.com/problems/spiral-matrix-iv
// Title: Spiral Matrix IV
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given two integers m and n, which represent the dimensions of a matrix.
//
// You are also given the head of a linked list of integers.
//
// Generate an m x n matrix that contains the integers in the linked list presented in spiral order (clockwise), starting from the top-left of the matrix. If there are remaining empty spaces, fill them with -1.
//
// Return the generated matrix.
//
// Example 1:
//
//   https://assets.leetcode.com/uploads/2022/05/09/ex1new.jpg
//
//   Input: m = 3, n = 5, head = [3,0,2,6,8,1,7,9,4,2,5,5,0]
//   Output: [[3,0,2,6,8],[5,0,-1,-1,1],[5,2,4,9,7]]
//   Explanation:
//     The diagram above shows how the values are printed in the matrix.
//     Note that the remaining spaces in the matrix are filled with -1.
//
// Example 2:
//
//   https://assets.leetcode.com/uploads/2022/05/11/ex2.jpg
//
//   Input: m = 1, n = 4, head = [0,1,2]
//   Output: [[0,1,2,-1]]
//   Explanation:
//     The diagram above shows how the values are printed from left to right in the matrix.
//     The last space in the matrix is set to -1.
//
// Constraints:
//
//   1 <= m, n <= 10^5
//   1 <= m * n <= 10^5
//   The number of nodes in the list is in the range [1, m * n].
//   0 <= Node.val <= 1000
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

type ListNode struct {
	Val  int
	Next *ListNode
}

type feeder struct {
	node *ListNode
}

func (f *feeder) get() int {
	if f.node == nil {
		return -1
	}
	val := f.node.Val
	f.node = f.node.Next
	return val
}

func spiralMatrix(m int, n int, head *ListNode) [][]int {
	matrix := make([][]int, m)
	for i := 0; i < m; i++ {
		matrix[i] = make([]int, n)
	}

	// boundaries
	north := 0
	south := m - 1
	west := 0
	east := n - 1

	feeder := feeder{
		node: head,
	}

	// spiral
	for true {
		// Right
		if west > east {
			break
		}
		{
			y := north
			for x := west; x <= east; x++ {
				matrix[y][x] = feeder.get()
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
				matrix[y][x] = feeder.get()
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
				matrix[y][x] = feeder.get()
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
				matrix[y][x] = feeder.get()
			}
			west++
		}
	}

	return matrix
}
