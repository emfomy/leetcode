// Source: https://leetcode.com/problems/string-matching-in-an-array
// Title: String Matching in an Array
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array of string `words`, return all strings in `words` that is a **substring** of another word. You can return the answer in **any order**.
//
// A **substring** is a contiguous sequence of characters within a string
//
// **Example 1:**
//
// ```
// Input: words = ["mass","as","hero","superhero"]
// Output: ["as","hero"]
// Explanation: "as" is substring of "mass" and "hero" is substring of "superhero".
// ["hero","as"] is also a valid answer.
// ```
//
// **Example 2:**
//
// ```
// Input: words = ["leetcode","et","code"]
// Output: ["et","code"]
// Explanation: "et", "code" are substring of "leetcode".
// ```
//
// **Example 3:**
//
// ```
// Input: words = ["blue","green","bu"]
// Output: []
// Explanation: No string of words is substring of another string.
// ```
//
// **Constraints:**
//
// - `1 <= words.length <= 100`
// - `1 <= words[i].length <= 30`
// - `words[i]` contains only lowercase English letters.
// - All the strings of `words` are **unique**.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"fmt"
	"strings"
)

// Brute Force
func stringMatching(words []string) []string {
	res := make([]string, 0, len(words))

	for i, sub := range words {
		for j, main := range words {
			if i == j {
				continue
			}

			if strings.Contains(main, sub) {
				res = append(res, sub)
				break
			}
		}
	}

	return res
}

// KMP Algorithm
func stringMatching2(words []string) []string {
	res := make([]string, 0, len(words))

	for i, sub := range words {
		lps := _makeLPS(sub)
		for j, main := range words {
			if i == j {
				continue
			}

			if _isSubstr(sub, main, lps) {
				res = append(res, sub)
				break
			}
		}
	}

	return res
}

func _makeLPS(word string) []int {
	l := len(word)
	lps := make([]int, l)

	currIdx := 1
	maxLen := 0
	for currIdx < l {
		if word[currIdx] == word[maxLen] {
			maxLen++
			lps[currIdx] = maxLen
			currIdx++
		} else if maxLen > 0 {
			maxLen = lps[maxLen-1]
		} else {
			currIdx++
		}
	}

	return lps
}

func _isSubstr(sub, main string, lps []int) bool {
	mainLen := len(main)
	subLen := len(sub)

	mainIdx := 0
	subIdx := 0

	for mainIdx < mainLen {
		if main[mainIdx] == sub[subIdx] {
			mainIdx++
			subIdx++
			if subIdx == subLen {
				return true
			}
		} else if subIdx > 0 {
			subIdx = lps[subIdx-1]
		} else {
			mainIdx++
		}
	}

	return false
}

func main() {
	fmt.Println(stringMatching([]string{"mass", "as", "hero", "superhero"}))
}
