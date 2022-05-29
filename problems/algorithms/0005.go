// Source: https://leetcode.com/problems/longest-palindromic-substring/
// Title: Longest Palindromic Substring
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.
//
// Example 1:
//
//   Input: "babad"
//   Output: "bab"
//   Note: "aba" is also a valid answer.
//
// Example 2:
//
//   Input: "cbbd"
//   Output: "bb"
//
// Constraints:
//
//   1 <= s.length <= 1000
//   s consist of only digits and English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func longestPalindrome(s string) string {
	n := len(s)
	res := s[0:1]

	// Check palindromic substring centered at i
	for i := 1; i < n-1; i++ {
		for j, k := i-1, i+1; j >= 0 && k < n; {
			if s[j] != s[k] {
				break
			}
			k++
			if k-j > len(res) {
				res = s[j:k]
			}
			j--
		}
	}

	// Check palindromic substring centered at i+0.5
	for i := 0; i < n-1; i++ {
		for j, k := i, i+1; j >= 0 && k < n; {
			if s[j] != s[k] {
				break
			}
			k++
			if k-j > len(res) {
				res = s[j:k]
			}
			j--
		}
	}

	return res
}
