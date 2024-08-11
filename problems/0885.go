// Source: https://leetcode.com/problems/spiral-matrix-iii
// Title: Spiral Matrix III
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You start at the cell (rStart, cStart) of an rows x cols grid facing east. The northwest corner is at the first row and column in the grid, and the southeast corner is at the last row and column.
//
// You will walk in a clockwise spiral shape to visit every position in this grid. Whenever you move outside the grid's boundary, we continue our walk outside the grid (but may return to the grid boundary later.). Eventually, we reach all rows * cols spaces of the grid.
//
// Return an array of coordinates representing the positions of the grid in the order you visited them.
//
// Example 1:
//
//   https://s3-lc-upload.s3.amazonaws.com/uploads/2018/08/24/example_1.png
//
//   Input: rows = 1, cols = 4, rStart = 0, cStart = 0
//   Output: [[0,0],[0,1],[0,2],[0,3]]
//
// Example 2:
//
//   https://s3-lc-upload.s3.amazonaws.com/uploads/2018/08/24/example_2.png
//
//   Input: rows = 5, cols = 6, rStart = 1, cStart = 4
//   Output: [[1,4],[1,5],[2,5],[2,4],[2,3],[1,3],[0,3],[0,4],[0,5],[3,5],[3,4],[3,3],[3,2],[2,2],[1,2],[0,2],[4,5],[4,4],[4,3],[4,2],[4,1],[3,1],[2,1],[1,1],[0,1],[4,0],[3,0],[2,0],[1,0],[0,0]]
//
// Constraints:
//
//   1 <= rows, cols <= 100
//   0 <= rStart < rows
//   0 <= cStart < cols
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func spiralMatrixIII(rows int, cols int, rStart int, cStart int) [][]int {
	r, c := rStart, cStart
	res := make([][]int, 0, rows*cols)

	// spiral
	size := 1
	for len(res) < rows*cols {
		// Right
		for i := 0; i < size; i++ {
			if 0 <= r && r < rows && 0 <= c && c < cols {
				res = append(res, []int{r, c})
			}
			c++
		}

		// Down
		for i := 0; i < size; i++ {
			if 0 <= r && r < rows && 0 <= c && c < cols {
				res = append(res, []int{r, c})
			}
			r++
		}

		size++

		// Left
		for i := 0; i < size; i++ {
			if 0 <= r && r < rows && 0 <= c && c < cols {
				res = append(res, []int{r, c})
			}
			c--
		}

		// Up
		for i := 0; i < size; i++ {
			if 0 <= r && r < rows && 0 <= c && c < cols {
				res = append(res, []int{r, c})
			}
			r--
		}

		size++
	}

	return res
}
