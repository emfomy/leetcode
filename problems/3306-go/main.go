// Source: https://leetcode.com/problems/count-of-substrings-containing-every-vowel-and-k-consonants-ii
// Title: Count of Substrings Containing Every Vowel and K Consonants II
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a string `word` and a **non-negative** integer `k`.
//
// Return the total number of substrings of `word` that contain every vowel (`'a'`, `'e'`, `'i'`, `'o'`, and `'u'`) **at least** once and **exactly** `k` consonants.
//
// A **substring** is a contiguous non-empty sequence of characters within a string.
//
// **Example 1:**
//
// ````
// Input: word = "aeioqq", k = 1
// Output: 0
// Explanation:
// There is no substring with every vowel.
// ```
//
// **Example 2:**
//
// ````
// Input: word = "aeiou", k = 0
// Output: 1
// Explanation:
// The only substring with every vowel and zero consonants is `word[0..4]`, which is `"aeiou"`.
// ````
//
// **Example 3:**
//
// ````
// Input: word = "ieaouqqieaouqq", k = 1
// Output: 3
// Explanation:
// The substrings with every vowel and one consonant are:
// - `word[0..5]`, which is `"ieaouq"`.
// - `word[6..11]`, which is `"qieaou"`.
// - `word[7..12]`, which is `"ieaouq"`.
// ````
//
// **Constraints:**
//
// - `5 <= word.length <= 2 * 10^5`
// - `word` consists only of lowercase English letters.
// - `0 <= k <= word.length - 5`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// Sliding Windows
func countOfSubstrings(word string, k int) int64 {
	n := len(word)
	res := int64(0)

	vowels := make(map[byte]int, 5)
	consonants := int(0)

	isVowel := func(c byte) bool {
		return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'
	}

	nextConsonants := make([]int, n)
	nextIdx := n
	for i := n - 1; i >= 0; i-- {
		nextConsonants[i] = nextIdx
		if !isVowel(word[i]) {
			nextIdx = i
		}
	}

	start, end := 0, 0
	for end < n {
		endChar := word[end]
		if isVowel(endChar) {
			vowels[endChar]++
		} else {
			consonants++
		}

		for consonants > k {
			startChar := word[start]
			if isVowel(startChar) {
				vowels[startChar]--
				if vowels[startChar] == 0 {
					delete(vowels, startChar)
				}
			} else {
				consonants--
			}
			start++
		}

		for start < n && len(vowels) == 5 && consonants == k {
			res += int64(nextConsonants[end] - end)
			startChar := word[start]
			if isVowel(startChar) {
				vowels[startChar]--
				if vowels[startChar] == 0 {
					delete(vowels, startChar)
				}
			} else {
				consonants--
			}
			start++
		}

		end++
	}

	return res
}
