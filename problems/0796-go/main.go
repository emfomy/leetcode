// Source: https://leetcode.com/problems/rotate-string
// Title: Rotate String
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given two strings `s` and `goal`, return `true` if and only if `s` can become `goal` after some number of **shifts** on `s`.
//
// A **shift** on `s` consists of moving the leftmost character of `s` to the rightmost position.
//
// - For example, if `s = "abcde"`, then it will be `"bcdea"` after one shift.
//
// **Example 1:**
//
// ```
// Input: s = "abcde", goal = "cdeab"
// Output: true
// ```
//
// **Example 2:**
//
// ```
// Input: s = "abcde", goal = "abced"
// Output: false
// ```
//
// **Constraints:**
//
// - `1 <= s.length, goal.length <= 100`
// - `s` and `goal` consist of lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import "strings"

func rotateString(s string, goal string) bool {
	return (len(s) == len(goal)) && strings.Contains(s+s, goal)
}
