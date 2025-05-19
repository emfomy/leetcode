// Source: https://leetcode.com/problems/letter-tile-possibilities
// Title: Letter Tile Possibilities
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You have `n` `tiles`, where each tile has one letter `tiles[i]` printed on it.
//
// Return the number of possible non-empty sequences of letters you can make using the letters printed on those `tiles`.
//
// **Example 1:**
//
// ```
// Input: tiles = "AAB"
// Output: 8
// Explanation: The possible sequences are "A", "B", "AA", "AB", "BA", "AAB", "ABA", "BAA".
// ```
//
// **Example 2:**
//
// ```
// Input: tiles = "AAABBC"
// Output: 188
// ```
//
// **Example 3:**
//
// ```
// Input: tiles = "V"
// Output: 1
// ```
//
// **Constraints:**
//
// - `1 <= tiles.length <= 7`
// - `tiles` consists of uppercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// Backtrack
func numTilePossibilities(tiles string) int {
	charFreq := make([]int, 26)

	for _, tile := range tiles {
		charFreq[tile-'A']++
	}

	var backtrack func() int
	backtrack = func() int {
		count := 0
		for i := range charFreq {
			if charFreq[i] == 0 {
				continue
			}

			count++
			charFreq[i]--
			count += backtrack()
			charFreq[i]++
		}
		return count
	}

	return backtrack()
}

// Math
var _factorials = []int{1, 1, 2, 6, 24, 120, 720, 5040}

func numTilePossibilities2(tiles string) int {
	charFreq := make([]int, 26)

	for _, tile := range tiles {
		charFreq[tile-'A']++
	}

	count := 0

	freqs := make([]int, 26)
	var recursion func(ch int)
	recursion = func(ch int) {
		if ch == 26 {
			size := 0
			denom := 1
			for _, freq := range freqs {
				size += freq
				denom *= _factorials[freq]
			}
			count += _factorials[size] / denom
			return
		}

		for freq := range charFreq[ch] + 1 {
			freqs[ch] = freq
			recursion(ch + 1)
		}
	}

	recursion(0)

	return count - 1 // remove zero length result
}
