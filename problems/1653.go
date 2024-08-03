// Source: https://leetcode.com/problems/minimum-deletions-to-make-string-balanced
// Title: Minimum Deletions to Make String Balanced
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a string s consisting only of characters 'a' and 'b'​​​​.
//
// You can delete any number of characters in s to make s balanced. s is balanced if there is no pair of indices (i,j) such that i < j and s[i] = 'b' and s[j]= 'a'.
//
// Return the minimum number of deletions needed to make s balanced.
//
// Example 1:
//
//   Input: s = "aababbab"
//   Output: 2
//   Explanation: You can either:
//     Delete the characters at 0-indexed positions 2 and 6 ("aababbab" -> "aaabbb"), or
//     Delete the characters at 0-indexed positions 3 and 6 ("aababbab" -> "aabbbb").
//
// Example 2:
//
//   Input: s = "bbaaaaabb"
//   Output: 2
//   Explanation: The only solution is to delete the first two characters.
//
// Constraints:
//
//   1 <= s.length <= 10^5
//   s[i] is 'a' or 'b'​​.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// Count number of 'a's after given position
// Count number of 'b's before given position
// Find the position the have minimal number 'b's in the left and 'a's in the right.
func minimumDeletions(s string) int {
	// Count total a
	rightA := 0
	for _, c := range s {
		if c == 'a' {
			rightA++
		}
	}

	leftB := 0
	res := rightA
	for _, c := range s {
		if c == 'a' {
			rightA--
		} else {
			leftB++
		}
		res = min(res, leftB+rightA)
	}

	return res
}
