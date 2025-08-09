// Source: https://leetcode.com/problems/shortest-way-to-form-string
// Title: Shortest Way to Form String
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// A **subsequence** of a string is a new string that is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (i.e., `"ace"` is a subsequence of `"abcde"` while `"aec"` is not).
//
// Given two strings `source` and `target`, return the minimum number of **subsequences** of `source` such that their concatenation equals `target`. If the task is impossible, return `-1`.
//
// **Example 1:**
//
// ```
// Input: source = "abc", target = "abcbc"
// Output: 2
// Explanation: The target "abcbc" can be formed by "abc" and "bc", which are subsequences of source "abc".
// ```
//
// **Example 2:**
//
// ```
// Input: source = "abc", target = "acdbc"
// Output: -1
// Explanation: The target string cannot be constructed from the subsequences of source string due to the character "d" in target string.
// ```
//
// **Example 3:**
//
// ```
// Input: source = "xyz", target = "xzyxz"
// Output: 3
// Explanation: The target string can be constructed as follows "xz" + "y" + "xz".
// ```
//
// **Constraints:**
//
// - `1 <= source.length, target.length <= 1000`
// - `source` and `target` consist of lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func shortestWay(source string, target string) int {
	n, m := len(target), len(source)

	count := 1
	i := 0
	j, used := 0, false
	for i < n {
		if j == m {
			if !used {
				return -1
			}
			count++
			j, used = 0, false
			continue
		}

		if target[i] == source[j] {
			i++
			used = true
		}
		j++
	}

	return count
}
