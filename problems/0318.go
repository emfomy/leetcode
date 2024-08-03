// Source: https://leetcode.com/problems/maximum-product-of-word-lengths
// Title: Maximum Product of Word Lengths
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a string array words, return the maximum value of length(word[i]) * length(word[j]) where the two words do not share common letters. If no such two words exist, return 0.
//
// Example 1:
//
//   Input: words = ["abcw","baz","foo","bar","xtfn","abcdef"]
//   Output: 16
//   Explanation: The two words can be "abcw", "xtfn".
//
// Example 2:
//
//   Input: words = ["a","ab","abc","d","cd","bcd","abcd"]
//   Output: 4
//   Explanation: The two words can be "ab", "cd".
//
// Example 3:
//
//   Input: words = ["a","aa","aaa","aaaa"]
//   Output: 0
//   Explanation: No such pair of words.
//
// Constraints:
//
//   2 <= words.length <= 1000
//   1 <= words[i].length <= 1000
//   words[i] consists only of lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func maxProduct(words []string) int {
	nums := make([]uint, len(words))
	for i, word := range words {
		nums[i] = _wordToInt(word)
	}

	res := 0
	for i := 0; i < len(nums); i++ {
		for j := i + 1; j < len(nums); j++ {
			if (nums[i] & nums[j]) == uint(0) { // no common letters
				res = _max(res, len(words[i])*len(words[j]))
			}
		}
	}

	return res
}

// Store letters in integer
func _wordToInt(word string) uint {
	res := uint(0)
	for _, c := range word {
		res |= 1 << (c - 'a')
	}
	return res
}

func _max(a, b int) int {
	if a > b {
		return a
	}
	return b
}
