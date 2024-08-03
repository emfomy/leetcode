// Source: https://leetcode.com/problems/find-and-replace-pattern
// Title: Find and Replace Pattern
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a list of strings words and a string pattern, return a list of words[i] that match pattern. You may return the answer in any order.
//
// A word matches the pattern if there exists a permutation of letters p so that after replacing every letter x in the pattern with p(x), we get the desired word.
//
// Recall that a permutation of letters is a bijection from letters to letters: every letter maps to another letter, and no two letters map to the same letter.
//
// Example 1:
//
//   Input: words = ["abc","deq","mee","aqq","dkd","ccc"], pattern = "abb"
//   Output: ["mee","aqq"]
//   Explanation:
//     "mee" matches the pattern because there is a permutation {a -> m, b -> e, ...}.
//     "ccc" does not match the pattern because {a -> c, b -> c, ...} is not a permutation, since a and b map to the same letter.
//
// Example 2:
//
//   Input: words = ["a","b","c"], pattern = "a"
//   Output: ["a","b","c"]
//
// Constraints:
//
//   1 <= pattern.length <= 20
//   1 <= words.length <= 50
//   words[i].length == pattern.length
//   pattern and words[i] are lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func findAndReplacePattern(words []string, pattern string) []string {
	l := len(pattern)

	res := make([]string, 0, len(words))

OUTER:
	for _, word := range words {
		wMap := make(map[byte]byte) // map word to pattern
		pSet := make(map[byte]bool) // set of pattern words

		for i := 0; i < l; i++ {
			w := word[i]
			p := pattern[i]

			if _, ok := wMap[w]; !ok {
				if pSet[p] {
					continue OUTER
				}
				wMap[w] = p
				pSet[p] = true
				continue
			}

			if wMap[w] != p {
				continue OUTER
			}
		}
		res = append(res, word)
	}

	return res
}
