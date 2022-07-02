// Source: https://leetcode.com/problems/maximum-area-of-a-piece-of-cake-after-horizontal-and-vertical-cuts/
// Title: Maximum Area of a Piece of Cake After Horizontal and Vertical Cuts
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a rectangular cake of size h x w and two arrays of integers horizontalCuts and verticalCuts where:
//
//   horizontalCuts[i] is the distance from the top of the rectangular cake to the ith horizontal cut and similarly, and
//   verticalCuts[j] is the distance from the left of the rectangular cake to the jth vertical cut.
//   Return the maximum area of a piece of cake after you cut at each horizontal and vertical position provided in the arrays horizontalCuts and verticalCuts. Since the answer can be a large number, return this modulo 109 + 7.
//
// Example 1:
//
//   https://assets.leetcode.com/uploads/2020/05/14/leetcode_max_area_2.png
//   Input: h = 5, w = 4, horizontalCuts = [1,2,4], verticalCuts = [1,3]
//   Output: 4
//   Explanation: The figure above represents the given rectangular cake. Red lines are the horizontal and vertical cuts. After you cut the cake, the green piece of cake has the maximum area.
//
// Example 2:
//
//   https://assets.leetcode.com/uploads/2020/05/14/leetcode_max_area_3.png
//   Input: h = 5, w = 4, horizontalCuts = [3,1], verticalCuts = [1]
//   Output: 6
//   Explanation: The figure above represents the given rectangular cake. Red lines are the horizontal and vertical cuts. After you cut the cake, the green and yellow pieces of cake have the maximum area.
//
// Example 3:
//
//   Input: h = 5, w = 4, horizontalCuts = [3], verticalCuts = [3]
//   Output: 9
//
// Constraints:
//
//   2 <= h, w <= 109
//   1 <= horizontalCuts.length <= min(h-1, 10^5)
//   1 <= verticalCuts.length <= min(w-1, 10^5)
//   1 <= horizontalCuts[i] < h
//   1 <= verticalCuts[i] < w
//   All the elements in horizontalCuts are distinct.
//   All the elements in verticalCuts are distinct.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"sort"
)

const modulo = int(1e9 + 7)

func maxArea(h int, w int, horizontalCuts []int, verticalCuts []int) int {
	m := len(horizontalCuts)
	n := len(verticalCuts)

	sort.Ints(horizontalCuts)
	sort.Ints(verticalCuts)

	height := _max(horizontalCuts[0], h-horizontalCuts[m-1])
	for i := 1; i < m; i++ {
		height = _max(height, horizontalCuts[i]-horizontalCuts[i-1])
	}

	width := _max(verticalCuts[0], w-verticalCuts[n-1])
	for i := 1; i < n; i++ {
		width = _max(width, verticalCuts[i]-verticalCuts[i-1])
	}

	return (height * width) % modulo
}

func _max(a, b int) int {
	if a > b {
		return a
	}
	return b
}
