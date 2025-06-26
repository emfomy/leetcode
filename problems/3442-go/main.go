// Source: https://leetcode.com/problems/maximum-difference-between-even-and-odd-frequency-i
// Title: Maximum Difference Between Even and Odd Frequency I
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a string `s` consisting of lowercase English letters.
//
// Your task is to find the **maximum** difference `diff = a_1 - a_2` between the frequency of characters `a_1` and `a_2` in the string such that:
//
// - `a_1` has an **odd frequency** in the string.
// - `a_2` has an **even frequency** in the string.
//
// Return this **maximum** difference.
//
// **Example 1:**
//
// ```
// Input: s = "aaaaabbc"
// Output: 3
// Explanation:
// - The character `'a'` has an **odd frequency** of `5`, and `'b'` has an **even frequency** of `2`.
// - The maximum difference is `5 - 2 = 3`.
// ```
//
// **Example 2:**
//
// ```
// Input: s = "abcabcab"
// Output: 1
// Explanation:
// - The character `'a'` has an **odd frequency** of `3`, and `'c'` has an **even frequency** of 2.
// - The maximum difference is `3 - 2 = 1`.
// ```
//
// **Constraints:**
//
// - `3 <= s.length <= 100`
// - `s` consists only of lowercase English letters.
// - `s` contains at least one character with an odd frequency and one with an even frequency.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func maxDifference(s string) int {
	n := len(s)
	freq := make([]int, 26)

	for i := range n {
		freq[s[i]-'a']++
	}

	// max
	maxOdd, minEven := 0, n
	for _, cnt := range freq {
		if cnt > 0 {
			if cnt%2 == 1 {
				maxOdd = max(maxOdd, cnt)
			} else {
				minEven = min(minEven, cnt)
			}
		}
	}

	return maxOdd - minEven
}
