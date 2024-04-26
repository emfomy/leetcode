// Source: https://leetcode.com/problems/determine-if-two-strings-are-close/
// Title: Determine if Two Strings Are Close
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Two strings are considered close if you can attain one from the other using the following operations:
//
// * Operation 1: Swap any two existing characters.
//     For example, abcde -> aecdb
//
// * Operation 2: Transform every occurrence of one existing character into another existing character, and do the same with the other character.
//     For example, aacabb -> bbcbaa (all a's turn into b's, and all b's turn into a's)
//
// You can use the operations on either string as many times as necessary.
//
// Given two strings, word1 and word2, return true if word1 and word2 are close, and false otherwise.
//
// Example 1:
//
//   Input: word1 = "abc", word2 = "bca"
//   Output: true
//   Explanation: You can attain word2 from word1 in 2 operations.
//     Apply Operation 1: "abc" -> "acb"
//     Apply Operation 1: "acb" -> "bca"
//
// Example 2:
//
//   Input: word1 = "a", word2 = "aa"
//   Output: false
//   Explanation: It is impossible to attain word2 from word1, or vice versa, in any number of operations.
//
// Example 3:
//
//   Input: word1 = "cabbba", word2 = "abbccc"
//   Output: true
//   Explanation: You can attain word2 from word1 in 3 operations.
//     Apply Operation 1: "cabbba" -> "caabbb"
//     Apply Operation 2: "caabbb" -> "baaccc"
//     Apply Operation 2: "baaccc" -> "abbccc"
//
// Constraints:
//
//   1 <= word1.length, word2.length <= 10^5
//   word1 and word2 contain only lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"sort"
)

func closeStrings(word1 string, word2 string) bool {
	if len(word1) != len(word2) {
		return false
	}

	// Count characters
	count1 := make([]int, 26)
	count2 := make([]int, 26)
	for _, ch := range word1 {
		count1[ch-'a']++
	}
	for _, ch := range word2 {
		count2[ch-'a']++
	}

	// Compare presence of charaters
	for i := 0; i < 26; i++ {
		if (count1[i] > 0) != (count2[i] > 0) {
			return false
		}
	}

	// Sort character counts
	sort.Ints(count1)
	sort.Ints(count2)

	// Compare character counts
	for i := 0; i < 26; i++ {
		if count1[i] != count2[i] {
			return false
		}
	}
	return true
}
