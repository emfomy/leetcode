// Source: https://leetcode.com/problems/check-if-it-is-a-straight-line/
// Title: Check If It Is a Straight Line
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an array coordinates, coordinates[i] = [x, y], where [x, y] represents the coordinate of a point. Check if these points make a straight line in the XY plane.
//
// Example 1:
//
//   Input: coordinates = [[1,2],[2,3],[3,4],[4,5],[5,6],[6,7]]
//   Output: true
//
// Example 2:
//
//   Input: coordinates = [[1,1],[2,2],[3,4],[4,5],[5,6],[7,7]]
//   Output: false
//
// Constraints:
//
//   2 <= coordinates.length <= 1000
//   coordinates[i].length == 2
//   -10^4 <= coordinates[i][0], coordinates[i][1] <= 10^4
//   coordinates contains no duplicate point.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func checkStraightLine(coordinates [][]int) bool {
	x0, y0 := coordinates[0][0], coordinates[0][1]
	x1, y1 := coordinates[1][0], coordinates[1][1]

	dx := float32(x1 - x0)
	dy := float32(y1 - y0)

	for _, v := range coordinates[1:] {
		x, y := v[0], v[1]
		if float32(x-x0)*dy != float32(y-y0)*dx {
			return false
		}
	}

	return true
}
