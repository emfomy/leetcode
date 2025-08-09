// Source: https://leetcode.com/problems/longest-subsequence-repeated-k-times
// Title: Longest Subsequence Repeated k Times
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a string `s` of length `n`, and an integer `k`. You are tasked to find the **longest subsequence repeated** `k` times in string `s`.
//
// A **subsequence** is a string that can be derived from another string by deleting some or no characters without changing the order of the remaining characters.
//
// A subsequence `seq` is **repeated** `k` times in the string `s` if `seq * k` is a subsequence of `s`, where `seq * k` represents a string constructed by concatenating `seq` `k` times.
//
// - For example, `"bba"` is repeated `2` times in the string `"bababcba"`, because the string `"bbabba"`, constructed by concatenating `"bba"` `2` times, is a subsequence of the string `"**b**a**bab**c**ba**"`.
//
// Return the **longest subsequence repeated** `k` times in string `s`. If multiple such subsequences are found, return the **lexicographically largest** one. If there is no such subsequence, return an **empty** string.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/08/30/longest-subsequence-repeat-k-times.png
//
// ```
// Input: s = "letsleetcode", k = 2
// Output: "let"
// Explanation: There are two longest subsequences repeated 2 times: "let" and "ete".
// "let" is the lexicographically largest one.
// ```
//
// **Example 2:**
//
// ```
// Input: s = "bb", k = 2
// Output: "b"
// Explanation: The longest subsequence repeated 2 times is "b".
// ```
//
// **Example 3:**
//
// ```
// Input: s = "ab", k = 2
// Output: ""
// Explanation: There is no subsequence repeated 2 times. Empty string is returned.
// ```
//
// **Constraints:**
//
// - `n == s.length`
// - `2 <= n, k <= 2000`
// - `2 <= n < k * 8`
// - `s` consists of lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// Count all possible seq.
// Note that len(seq) <= n/k.
//
// We loop through all possible seqs, and check if it fit the condition.
func longestSubsequenceRepeatedK(s string, k int) string {
	n := len(s)
	m := n / k

	// Get candidate characters
	freq := make([]int, 26)
	for _, ch := range s {
		freq[ch-'a']++
	}
	chars := make([]byte, 0, 26)
	for ch, cnt := range freq {
		if cnt >= k {
			chars = append(chars, 'a'+byte(ch))
		}
	}

	// Check
	check := func(seq string) bool {
		idx := 0
		count := 0
		for i := range n {
			if s[i] == seq[idx] {
				idx++
				if idx == len(seq) { // find a match
					idx = 0
					count++
					if count == k {
						return true
					}
				}
			}
		}
		return false
	}

	// Loop
	var queue []string
	for _, ch := range chars {
		queue = append(queue, string(ch))
	}

	ans := ""
	for len(queue) > 0 {
		curr := queue[0]
		queue = queue[1:]
		ans = curr

		// Too long, no need to generate next seq
		if len(curr) >= m {
			continue
		}

		// Generate next seq
		for _, ch := range chars {
			next := curr + string(ch)
			if check(next) {
				queue = append(queue, next)
			}
		}
	}

	return ans
}
