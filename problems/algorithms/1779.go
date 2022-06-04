// Source: https://leetcode.com/problems/find-nearest-point-that-has-the-same-x-or-y-coordinate/
// Title: Find Nearest Point That Has the Same X or Y Coordinate
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given two integers, x and y, which represent your current location on a Cartesian grid: (x, y). You are also given an array points where each points[i] = [ai, bi] represents that a point exists at (ai, bi). A point is valid if it shares the same x-coordinate or the same y-coordinate as your location.
//
// Return the index (0-indexed) of the valid point with the smallest Manhattan distance from your current location. If there are multiple, return the valid point with the smallest index. If there are no valid points, return -1.
//
// The Manhattan distance between two points (x1, y1) and (x2, y2) is abs(x1 - x2) + abs(y1 - y2).
//
// Example 1:
//
//   Input: x = 3, y = 4, points = [[1,2],[3,1],[2,4],[2,3],[4,4]]
//   Output: 2
//   Explanation: Of all the points, only [3,1], [2,4] and [4,4] are valid. Of the valid points, [2,4] and [4,4] have the smallest Manhattan distance from your current location, with a distance of 1. [2,4] has the smallest index, so return 2.
//
// Example 2:
//
//   Input: x = 3, y = 4, points = [[3,4]]
//   Output: 0
//   Explanation: The answer is allowed to be on the same location as your current location.
//
// Example 3:
//
//   Input: x = 3, y = 4, points = [[2,3]]
//   Output: -1
//   Explanation: There are no valid points.
//
// Constraints:
//
//   1 <= points.length <= 10^4
//   points[i].length == 2
//   1 <= x, y, ai, bi <= 10^4
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func nearestValidPoint(x int, y int, points [][]int) int {
	res := -1
	dist := 10_000

	for idx, point := range points {
		dx := point[0] - x
		dy := point[1] - y

		if dx == 0 && dy == 0 {
			return idx
		}

		if dx == 0 {
			if d := _abs(dy); d < dist {
				dist = d
				res = idx
			}
		}

		if dy == 0 {
			if d := _abs(dx); d < dist {
				dist = d
				res = idx
			}
		}
	}

	return res
}

func _abs(v int) int {
	if v >= 0 {
		return v
	}
	return -v
}
