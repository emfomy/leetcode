// Source: https://leetcode.com/problems/uncommon-words-from-two-sentences
// Title: Uncommon Words from Two Sentences
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// A sentence is a string of single-space separated words where each word consists only of lowercase letters.
// A word is uncommon if it appears exactly once in one of the sentences, and does not appear in the other sentence.
// Given two sentences s1 and s2, return a list of all the uncommon words. You may return the answer in any order.
//
// Example 1:
//
//   Input: s1 = "this apple is sweet", s2 = "this apple is sour"
//   Output: ["sweet","sour"]
//   Explanation: The word "sweet" appears only in s1, while the word "sour" appears only in s2.
//
// Example 2:
//
//   Input: s1 = "apple apple", s2 = "banana"
//   Output: ["banana"]
//
// Constraints:
//
//   1 <= s1.length, s2.length <= 200
//   s1 and s2 consist of lowercase English letters and spaces.
//   s1 and s2 do not have leading or trailing spaces.
//   All the words in s1 and s2 are separated by a single space.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import "strings"

func uncommonFromSentences(s1 string, s2 string) []string {
	words1 := strings.Split(s1, " ")
	words2 := strings.Split(s2, " ")

	counts := make(map[string]int, len(words1)+len(words2))
	for _, word := range words1 {
		counts[word] += 1
	}
	for _, word := range words2 {
		counts[word] += 1
	}

	res := make([]string, 0, len(words1)+len(words2))
	for word, count := range counts {
		if count == 1 {
			res = append(res, word)
		}
	}

	return res
}
