// Source: https://leetcode.com/problems/triangle
// Title: Triangle
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a triangle array, return the minimum path sum from top to bottom.
//
// For each step, you may move to an adjacent number of the row below. More formally, if you are on index i on the current row, you may move to either index i or index i + 1 on the next row.
//
// Example 1:
//
//   Input: triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
//   Output: 11
//   Explanation:
//     The triangle looks like:
//        2
//       3 4
//      6 5 7
//     4 1 8 3
//     The minimum path sum from top to bottom is 2 + 3 + 5 + 1 = 11 (underlined above).
//
// Example 2:
//
//   Input: triangle = [[-10]]
//   Output: -10
//
// Constraints:
//
//   1 <= triangle.length <= 200
//   triangle[0].length == 1
//   triangle[i].length == triangle[i - 1].length + 1
//   -10^4 <= triangle[i][j] <= 10^4
//
// Follow up: Could you do this using only O(n) extra space, where n is the total number of rows in the triangle?
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"math"
)

func minimumTotal(triangle [][]int) int {
	n := len(triangle)

	prev := make([]int, n)
	next := make([]int, n)

	prev[0] = triangle[0][0]

	for i := 1; i < n; i++ {
		row := triangle[i]

		next[0] = row[0] + prev[0]
		for j := 1; j < i; j++ {
			next[j] = row[j] + _min(prev[j-1], prev[j])
		}
		next[i] = row[i] + prev[i-1]

		prev, next = next, prev
	}

	res := math.MaxInt32
	for _, v := range prev {
		res = _min(res, v)
	}
	return res
}

func _min(a, b int) int {
	if a < b {
		return a
	}
	return b
}
