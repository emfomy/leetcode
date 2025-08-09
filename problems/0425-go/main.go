// Source: https://leetcode.com/problems/word-squares
// Title: Word Squares
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array of **unique** strings `words`, return all the **word squares** (https://en.wikipedia.org/wiki/Word_square) you can build from `words`. The same word from `words` can be used **multiple times**. You can return the answer in **any order**.
//
// A sequence of strings forms a valid **word square** if the `k^th` row and column read the same string, where `0 <= k < max(numRows, numColumns)`.
//
// - For example, the word sequence `["ball","area","lead","lady"]` forms a word square because each word reads the same both horizontally and vertically.
//
// **Example 1:**
//
// ```
// Input: words = ["area","lead","wall","lady","ball"]
// Output: [["ball","area","lead","lady"],["wall","area","lead","lady"]]
// Explanation:
// The output consists of two word squares. The order of output does not matter (just the order of words in each word square matters).
// ```
//
// **Example 2:**
//
// ```
// Input: words = ["abat","baba","atan","atal"]
// Output: [["baba","abat","baba","atal"],["baba","abat","baba","atan"]]
// Explanation:
// The output consists of two word squares. The order of output does not matter (just the order of words in each word square matters).
// ```
//
// **Constraints:**
//
// - `1 <= words.length <= 1000`
// - `1 <= words[i].length <= 4`
// - All `words[i]` have the same length.
// - `words[i]` consists of only lowercase English letters.
// - All `words[i]` are **unique**.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"strings"
)

// Backtracking
func wordSquares(words []string) [][]string {
	n := len(words[0])

	var ans [][]string
	rows := make([]string, n)

	var backtrack func(k int)
	backtrack = func(k int) {
		if k == n {
			square := make([]string, n)
			copy(square, rows)
			ans = append(ans, square)
			return
		}

	LOOP:
		for _, word := range words {
			for i, row := range rows[:k] {
				if row[k] != word[i] {
					continue LOOP
				}
			}
			rows[k] = word
			backtrack(k + 1)
		}
	}

	backtrack(0)

	return ans
}

// Backtracking + prefix map
func wordSquares2(words []string) [][]string {
	n := len(words[0])

	prefixMap := make(map[string][]string)
	prefixMap[""] = words
	for _, word := range words {
		for i := 1; i <= n; i++ {
			prefixMap[word[:i]] = append(prefixMap[word[:i]], word)
		}
	}

	var ans [][]string
	rows := make([]string, n)

	var backtrack func(k int)
	backtrack = func(k int) {
		if k == n {
			square := make([]string, n)
			copy(square, rows)
			ans = append(ans, square)
			return
		}

		prefix := strings.Builder{}
		for _, row := range rows[:k] {
			prefix.WriteByte(row[k])
		}

		for _, word := range prefixMap[prefix.String()] {
			rows[k] = word
			backtrack(k + 1)
		}
	}

	backtrack(0)

	return ans
}
