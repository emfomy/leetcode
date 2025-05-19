// Source: https://leetcode.com/problems/number-of-equivalent-domino-pairs
// Title: Number of Equivalent Domino Pairs
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a list of `dominoes`, `dominoes[i] = [a, b]` is **equivalent to** `dominoes[j] = [c, d]` if and only if either (`a == c` and `b == d`), or (`a == d` and `b == c`) - that is, one domino can be rotated to be equal to another domino.
//
// Return the number of pairs `(i, j)` for which `0 <= i < j < dominoes.length`, and `dominoes[i]` is **equivalent to** `dominoes[j]`.
//
// **Example 1:**
//
// ```
// Input: dominoes = [[1,2],[2,1],[3,4],[5,6]]
// Output: 1
// ```
//
// **Example 2:**
//
// ```
// Input: dominoes = [[1,2],[1,2],[1,1],[1,2],[2,2]]
// Output: 3
// ```
//
// **Constraints:**
//
// - `1 <= dominoes.length <= 4 * 10^4`
// - `dominoes[i].length == 2`
// - `1 <= dominoes[i][j] <= 9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import "fmt"

// Use hash map
func numEquivDominoPairs(dominoes [][]int) int {
	counter := make(map[int]int, 45)

	for _, domino := range dominoes {
		top, bottom := domino[0], domino[1]
		if top > bottom {
			top, bottom = bottom, top
		}
		counter[top*9+bottom]++
	}
	fmt.Println(counter)

	ans := 0
	for _, count := range counter {
		ans += count * (count - 1) / 2
	}
	return ans
}
