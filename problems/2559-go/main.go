// Source: https://leetcode.com/problems/count-vowel-strings-in-ranges
// Title: Count Vowel Strings in Ranges
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a **0-indexed** array of strings `words` and a 2D array of integers `queries`.
//
// Each query `queries[i] = [l_i, r_i]` asks us to find the number of strings present in the range `l_i` to `r_i` (both **inclusive** ) of `words` that start and end with a vowel.
//
// Return an array `ans` of size `queries.length`, where `ans[i]` is the answer to the `i`^th query.
//
// **Note** that the vowel letters are `'a'`, `'e'`, `'i'`, `'o'`, and `'u'`.
//
// **Example 1:**
//
// ```
// Input: words = ["aba","bcb","ece","aa","e"], queries = [[0,2],[1,4],[1,1]]
// Output: [2,3,0]
// Explanation: The strings starting and ending with a vowel are "aba", "ece", "aa" and "e".
// The answer to the query [0,2] is 2 (strings "aba" and "ece").
// to query [1,4] is 3 (strings "ece", "aa", "e").
// to query [1,1] is 0.
// We return [2,3,0].
// ```
//
// **Example 2:**
//
// ```
// Input: words = ["a","e","i"], queries = [[0,2],[0,1],[2,2]]
// Output: [3,2,1]
// Explanation: Every string satisfies the conditions, so we return [3,2,1].```
//
// **Constraints:**
//
// - `1 <= words.length <= 10^5`
// - `1 <= words[i].length <= 40`
// - `words[i]` consists only of lowercase English letters.
// - `sum(words[i].length) <= 3 * 10^5`
// - `1 <= queries.length <= 10^5`
// - `0 <= l_i <= r_i <words.length`
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func isVowel(ch byte) bool {
	return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u'
}

func vowelStrings(words []string, queries [][]int) []int {
	vowelWordCount := make([]int, len(words)+1)

	count := 0
	for i, word := range words {
		if isVowel(word[0]) && isVowel(word[len(word)-1]) {
			count++
		}
		vowelWordCount[i+1] = count
	}

	res := make([]int, 0, len(queries))
	for _, query := range queries {
		left, right := query[0], query[1]
		res = append(res, vowelWordCount[right+1]-vowelWordCount[left])
	}

	return res
}
