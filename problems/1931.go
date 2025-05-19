// Source: https://leetcode.com/problems/painting-a-grid-with-three-different-colors
// Title: Painting a Grid With Three Different Colors
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given two integers `m` and `n`. Consider an `m x n` grid where each cell is initially white. You can paint each cell **red**, **green**, or **blue**. All cells **must** be painted.
//
// Return the number of ways to color the grid with **no two adjacent cells having the same color**. Since the answer can be very large, return it **modulo** `10^9 + 7`.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/06/22/colorthegrid.png
//
// ```
// Input: m = 1, n = 1
// Output: 3
// Explanation: The three possible colorings are shown in the image above.
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2021/06/22/copy-of-colorthegrid.png
//
// ```
// Input: m = 1, n = 2
// Output: 6
// Explanation: The six possible colorings are shown in the image above.
// ```
//
// **Example 3:**
//
// ```
// Input: m = 5, n = 5
// Output: 580986
// ```
//
// **Constraints:**
//
// - `1 <= m <= 5`
// - `1 <= n <= 1000`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// Use DP
// Since m is small, we can loop through all possible states
// Use a 15bit number to represent a column,
// Each bit represents (red at 0, blue at 0, green at 0, red at 1, ..., green at m)
//
// Note that we can precompute all possible solutions
const modulo = int(1e9 + 7)

type color uint16

const M, N, S = 5, 1000, 48

var DP [M][N][S]int
var STATES [M][S]color
var SS = [M]int{3, 6, 12, 24, 48}

func init() {
	// Prepare states
	red, green, blue := color(0x01), color(0x02), color(0x04)
	STATES[0] = [S]color{red, green, blue}
	for m := range M - 1 {
		s := SS[m]
		j := 0
		for i := range s {
			state := STATES[m][i]
			if state&red == 0 {
				STATES[m+1][j] = state + red<<3
				j++
			}
			if state&green == 0 {
				STATES[m+1][j] = state + green<<3
				j++
			}
			if state&blue == 0 {
				STATES[m+1][j] = state + blue<<3
				j++
			}
		}
		red <<= 3
		green <<= 3
		blue <<= 3
	}

	for m := range M {
		s := SS[m]

		// Markov matrix
		matrix := make([][]int, SS[m])
		for i := range s {
			matrix[i] = make([]int, s)
		}
		for j := range s {
			for i := range j {
				if STATES[m][i]&STATES[m][j] == 0 {
					matrix[i][j] = 1
					matrix[j][i] = 1
				}
			}
		}

		// DP
		for i := range s {
			DP[m][0][i] = 1
		}
		for t := range N - 1 {
			for i := range s {
				for j := range s {
					DP[m][t+1][i] += matrix[i][j] * DP[m][t][j]
				}
				DP[m][t+1][i] %= modulo
			}
		}
	}
}

func colorTheGrid(m int, n int) int {
	ans := 0
	for i := range SS[m-1] {
		ans += DP[m-1][n-1][i]
	}
	return ans % modulo
}

func (c color) String() string {
	chars := map[color]byte{0x00: '-', 0x01: 'r', 0x02: 'g', 0x04: 'b'}
	res := make([]byte, 5)
	for i := range 5 {
		res[4-i] = chars[c&0x07]
		c >>= 3
	}
	return string(res)
}
