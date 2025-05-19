// Source: https://leetcode.com/problems/minimum-domino-rotations-for-equal-row
// Title: Minimum Domino Rotations For Equal Row
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// In a row of dominoes, `tops[i]` and `bottoms[i]` represent the top and bottom halves of the `i^th` domino. (A domino is a tile with two numbers from 1 to 6 - one on each half of the tile.)
//
// We may rotate the `i^th` domino, so that `tops[i]` and `bottoms[i]` swap values.
//
// Return the minimum number of rotations so that all the values in `tops` are the same, or all the values in `bottoms` are the same.
//
// If it cannot be done, return `-1`.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/05/14/domino.png
//
// ```
// Input: tops = [2,1,2,4,2,2], bottoms = [5,2,6,2,3,2]
// Output: 2
// Explanation:
// The first figure represents the dominoes as given by tops and bottoms: before we do any rotations.
// If we rotate the second and fourth dominoes, we can make every value in the top row equal to 2, as indicated by the second figure.
// ```
//
// **Example 2:**
//
// ```
// Input: tops = [3,5,1,2,3], bottoms = [3,6,3,3,4]
// Output: -1
// Explanation:
// In this case, it is not possible to rotate the dominoes to make one row of values equal.
// ```
//
// **Constraints:**
//
// - `2 <= tops.length <= 2 * 10^4`
// - `bottoms.length == tops.length`
// - `1 <= tops[i], bottoms[i] <= 6`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func minDominoRotations(tops []int, bottoms []int) int {
	n := len(tops)

	// Count number
	counter := [6]int{}
	topCounter := [6]int{}
	bottomCounter := [6]int{}
	for i := range n {
		top := tops[i] - 1
		bottom := bottoms[i] - 1

		topCounter[top]++
		bottomCounter[bottom]++

		counter[top]++
		if top != bottom {
			counter[bottom]++
		}
	}

	// Find common number
	common := -1
	for i := range 6 {
		if counter[i] == n {
			common = i
			break
		}
	}
	if common == -1 {
		return -1
	}

	return n - max(topCounter[common], bottomCounter[common])
}

// the common value must be one of the numbers in the first tile
func minDominoRotations2(tops []int, bottoms []int) int {
	n := len(tops)

	// Assume the common number is on the top
	check := func(common int) int {
		topSwap, bottomSwap := 0, 0
		for i := range n {
			top := tops[i]
			bottom := bottoms[i]

			if top != common && bottom != common {
				return n + 1
			}
			if top != common {
				topSwap++
			}
			if bottom != common {
				bottomSwap++
			}
		}
		return min(topSwap, bottomSwap)
	}

	ans := min(check(tops[0]), check(bottoms[0]))
	if ans == n+1 {
		return -1
	}
	return ans
}
