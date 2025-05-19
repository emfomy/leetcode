// Source: https://leetcode.com/problems/number-of-substrings-containing-all-three-characters
// Title: Number of Substrings Containing All Three Characters
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a string `s`consisting only of characters a, b and c.
//
// Return the number of substrings containing **at least** one occurrence of all these characters a, b and c.
//
// **Example 1:**
//
// ```
// Input: s = "abcabc"
// Output: 10
// Explanation: The substrings containingat leastone occurrence of the charactersa,bandc are "abc", "abca", "abcab", "abcabc", "bca", "bcab", "bcabc", "cab", "cabc" and "abc" (**again**).
// ```
//
// **Example 2:**
//
// ```
// Input: s = "aaacb"
// Output: 3
// Explanation: The substrings containingat leastone occurrence of the charactersa,bandc are "aaacb", "aacb" and "acb".
// ```
//
// **Example 3:**
//
// ```
// Input: s = "abc"
// Output: 1
// ```
//
// **Constraints:**
//
// - `3 <= s.length <= 5 x 10^4`
// - `s`only consists ofa, b or ccharacters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func numberOfSubstrings(s string) int {
	n := len(s)
	res := 0

	counts := [3]int{}

	start, end := 0, 0
	for end < n {
		counts[s[end]-'a']++
		for start < n && counts[0] > 0 && counts[1] > 0 && counts[2] > 0 {
			res += n - end
			counts[s[start]-'a']--
			start++
		}
		end++
	}

	return res
}

// For each end position, all substrings from 0~end and min(lastSeen)~end are valid.
func numberOfSubstrings2(s string) int {
	res := 0

	lastSeen := [3]int{-1, -1, -1}

	for idx, char := range s {
		lastSeen[char-'a'] = idx
		res += min(lastSeen[0], lastSeen[1], lastSeen[2]) + 1
	}

	return res
}
