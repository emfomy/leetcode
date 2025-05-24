// Source: https://leetcode.com/problems/substring-with-concatenation-of-all-words
// Title: Substring with Concatenation of All Words
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a string s and an array of strings words of the same length. Return all starting indices of substring(s) in s that is a concatenation of each word in words exactly once, in any order, and without any intervening characters.
//
// You can return the answer in any order.
//
// Example 1:
//
//   Input: s = "barfoothefoobarman", words = ["foo","bar"]
//   Output: [0,9]
//   Explanation: Substrings starting at index 0 and 9 are "barfoo" and "foobar" respectively.
//   The output order does not matter, returning [9,0] is fine too.
//
// Example 2:
//
//   Input: s = "wordgoodgoodgoodbestword", words = ["word","good","best","word"]
//   Output: []
//
// Example 3:
//
//   Input: s = "barfoofoobarthefoobarman", words = ["bar","foo","the"]
//   Output: [6,9,12]
//
// Constraints:
//
//   1 <= s.length <= 10^4
//   1 <= words.length <= 5000
//   1 <= words[i].length <= 30
//   s and words[i] consist of lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func findSubstring(s string, words []string) []int {
	wordCount := make(map[string]int, len(words))
	for _, word := range words {
		wordCount[word]++
	}

	sLen := len(s)
	wLen := len(words[0])
	nWords := len(words)
	subLen := nWords * wLen

	res := make([]int, 0, nWords)
	for i := 0; i <= sLen-subLen; i++ {
		tmp := _copyMap(wordCount)
		ok := true
		for j := i; j < i+subLen; j += wLen {
			word := s[j : j+wLen]
			tmp[word]--
			if tmp[word] < 0 {
				ok = false
				break
			}
		}
		if ok {
			res = append(res, i)
		}
	}

	return res
}

func _copyMap(src map[string]int) map[string]int {
	dst := make(map[string]int, len(src))
	for k, v := range src {
		dst[k] = v
	}
	return dst
}
