// Source: https://leetcode.com/problems/domino-and-tromino-tiling
// Title: Domino and Tromino Tiling
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You have two types of tiles: a `2 x 1` domino shape and a tromino shape. You may rotate these shapes.
// https://assets.leetcode.com/uploads/2021/07/15/lc-domino.jpg
// Given an integer n, return the number of ways to tile an `2 x n` board. Since the answer may be very large, return it **modulo** `10^9 + 7`.
//
// In a tiling, every square must be covered by a tile. Two tilings are different if and only if there are two 4-directionally adjacent cells on the board such that exactly one of the tilings has both squares occupied by a tile.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/07/15/lc-domino1.jpg
//
// ```
// Input: n = 3
// Output: 5
// Explanation: The five different ways are show above.
// ```
//
// **Example 2:**
//
// ```
// Input: n = 1
// Output: 1
// ```
//
// **Constraints:**
//
// - `1 <= n <= 1000`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

const modulo = int(1e9 + 7)

// Use DP
//
// Denote F[i] be an 2*i board.
// Denote U[i]/L[i] be F[i] with an extra upper/lower square.
//
// From F[i], add 1 vertical domino => F[i+1]
// From F[i], add 2 horizontal dominoes => F[i+2]
// From F[i], add 1 upper tromino => U[i+1]
// From F[i], add 1 lower tromino => L[i+1]
//
// From U[i], add 1 lower domino => L[I+1]
// From U[i], add 1 tromino => F[I+2]
//
// From L[i], add 1 horizontal domino => U[I+1]
// From L[i], add 1 tromino => F[I+2]
//
// Note that U and L are symmetry, we don't need to compute separately
func numTilings(n int) int {
	prevFlat, prevLower := 1, 1 // i = 1
	currFlat, currLower := 2, 2 // i = 2
	if n == 1 {
		return prevFlat
	}
	if n == 2 {
		return currFlat
	}

	for i := 3; i <= n; i++ {
		nextFlat := (currFlat + prevFlat + 2*prevLower) % modulo
		nextLower := (currFlat + currLower) % modulo

		prevFlat, prevLower = currFlat, currLower
		currFlat, currLower = nextFlat, nextLower
	}

	return currFlat
}
