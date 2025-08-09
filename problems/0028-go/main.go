// Source: https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string
// Title: Find the Index of the First Occurrence in a String
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given two strings `needle` and `haystack`, return the index of the first occurrence of `needle` in `haystack`, or `-1` if `needle` is not part of `haystack`.
//
// **Example 1:**
//
// ```
// Input: haystack = "sadbutsad", needle = "sad"
// Output: 0
// Explanation: "sad" occurs at index 0 and 6.
// The first occurrence is at index 0, so we return 0.
// ```
//
// **Example 2:**
//
// ```
// Input: haystack = "leetcode", needle = "leeto"
// Output: -1
// Explanation: "leeto" did not occur in "leetcode", so we return -1.
// ```
//
// **Constraints:**
//
// - `1 <= haystack.length, needle.length <= 10^4`
// - `haystack` and `needle` consist of only lowercase English characters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import "strings"

func strStr(text string, pattern string) int {
	return strings.Index(text, pattern)
}

// Naive
func strStr2(text string, pattern string) int {
	n, m := len(text), len(pattern)
	if n < m {
		return -1
	}

	for i := range n - m + 1 {
		if text[i:i+m] == pattern {
			return i
		}
	}
	return -1
}

// Rabin-Karp Algorithm
//
// Use char sum as hash
func strStr3(text string, pattern string) int {
	n, m := len(text), len(pattern)
	if n < m {
		return -1
	}

	needleHash := 0
	for i := range m {
		needleHash += int(pattern[i])
	}

	windowHash := 0
	for i := range m - 1 {
		windowHash += int(text[i])
	}

	for i := range n - m + 1 {
		windowHash += int(text[i+m-1])
		if windowHash == needleHash && text[i:i+m] == pattern {
			return i
		}
		windowHash -= int(text[i])
	}
	return -1
}

// KMP Algorithm
func strStr4(text string, pattern string) int {
	n, m := len(text), len(pattern)
	if n < m {
		return -1
	}

	// Build KPS
	lps := make([]int, m)
	{
		i, j := 1, 0
		for i < m {
			if pattern[i] == pattern[j] {
				j++
				lps[i] = j
				i++
			} else if j > 0 {
				j = lps[j-1]
			} else {
				lps[i] = 0
				i++
			}
		}
	}

	// Find substring
	i, j := 0, 0
	for i < n {
		if text[i] == pattern[j] {
			i++
			j++
			if j == m {
				return i - m
			}
		} else if j > 0 {
			j = lps[j-1]
		} else {
			i++
		}
	}

	return -1
}
