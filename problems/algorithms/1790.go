// Source: https://leetcode.com/problems/check-if-one-string-swap-can-make-strings-equal/
// Title: Check if One String Swap Can Make Strings Equal
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given two strings s1 and s2 of equal length. A string swap is an operation where you choose two indices in a string (not necessarily different) and swap the characters at these indices.
//
// Return true if it is possible to make both strings equal by performing at most one string swap on exactly one of the strings. Otherwise, return false.
//
// Example 1:
//
//   Input: s1 = "bank", s2 = "kanb"
//   Output: true
//   Explanation: For example, swap the first character with the last character of s2 to make "bank".
//
// Example 2:
//
//   Input: s1 = "attack", s2 = "defend"
//   Output: false
//   Explanation: It is impossible to make them equal with one string swap.
//
// Example 3:
//
//   Input: s1 = "kelb", s2 = "kelb"
//   Output: true
//   Explanation: The two strings are already equal, so no string swap operation is required.
//
// Constraints:
//
//   1 <= s1.length, s2.length <= 100
//   s1.length == s2.length
//   s1 and s2 consist of only lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func areAlmostEqual(s1 string, s2 string) bool {
	firstIdx := _findNextDiffer(s1, s2, 0)
	if firstIdx == -1 { // s1 == s2
		return true
	}
	first1, first2 := s1[firstIdx], s2[firstIdx]

	secondIdx := _findNextDiffer(s1, s2, firstIdx+1)
	if secondIdx == -1 { // only one different character
		return false
	}
	second1, second2 := s1[secondIdx], s2[secondIdx]

	if first1 != second2 || first2 != second1 { // Can't swap
		return false
	}
	thirdIdx := _findNextDiffer(s1, s2, secondIdx+1)
	return thirdIdx == -1 // there should not be the third different character
}

func _findNextDiffer(s1, s2 string, idx int) int {
	for i := idx; i < len(s1); i++ {
		if s1[i] != s2[i] {
			return i
		}
	}
	return -1
}
