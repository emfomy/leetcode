// Source: https://leetcode.com/problems/counting-words-with-a-given-prefix
// Title: Counting Words With a Given Prefix
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an array of strings `words` and a string `pref`.
//
// Return the number of strings in `words` that contain `pref` as a **prefix**.
//
// A **prefix** of a string `s` is any leading contiguous substring of `s`.
//
// **Example 1:**
//
// ```
// Input: words = ["pay","**at** tention","practice","**at** tend"], `pref `= "at"
// Output: 2
// Explanation: The 2 strings that contain "at" as a prefix are: "**at** tention" and "**at** tend".
// ```
//
// **Example 2:**
//
// ```
// Input: words = ["leetcode","win","loops","success"], `pref `= "code"
// Output: 0
// Explanation: There are no strings that contain "code" as a prefix.
// ```
//
// **Constraints:**
//
// - `1 <= words.length <= 100`
// - `1 <= words[i].length, pref.length <= 100`
// - `words[i]` and `pref` consist of lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import "strings"

func prefixCount(words []string, pref string) int {
	count := 0
	for _, word := range words {
		if strings.HasPrefix(word, pref) {
			count++
		}
	}
	return count
}
