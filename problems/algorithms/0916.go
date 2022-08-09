// Source: https://leetcode.com/problems/word-subsets/
// Title: Word Subsets
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given two string arrays words1 and words2.
//
// A string b is a subset of string a if every letter in b occurs in a including multiplicity.
//
//   For example, "wrr" is a subset of "warrior" but is not a subset of "world".
//
// A string a from words1 is universal if for every string b in words2, b is a subset of a.
//
// Return an array of all the universal strings in words1. You may return the answer in any order.
//
// Example 1:
//
//   Input: words1 = ["amazon","apple","facebook","google","leetcode"], words2 = ["e","o"]
//   Output: ["facebook","google","leetcode"]
//
// Example 2:
//
//   Input: words1 = ["amazon","apple","facebook","google","leetcode"], words2 = ["l","e"]
//   Output: ["apple","google","leetcode"]
//
// Constraints:
//
//   1 <= words1.length, words2.length <= 10^4
//   1 <= words1[i].length, words2[i].length <= 10
//   words1[i] and words2[i] consist only of lowercase English letters.
//   All the strings of words1 are unique.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func wordSubsets(words1 []string, words2 []string) []string {
	countAll := make([]int, 26)

	for _, word := range words2 {
		count := make([]int, 26)
		for _, ch := range word {
			count[ch-'a']++
		}

		for ch, num := range count {
			countAll[ch] = _max(countAll[ch], num)
		}
	}

	res := make([]string, 0, len(words1))

OUTER:
	for _, word := range words1 {
		count := make([]int, 26)
		for _, ch := range word {
			count[ch-'a']++
		}

		for ch, num := range countAll {
			if count[ch] < num {
				continue OUTER
			}
		}
		res = append(res, word)
	}

	return res
}

func _max(a, b int) int {
	if a > b {
		return a
	}
	return b
}
