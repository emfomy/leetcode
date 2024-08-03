// Source: https://leetcode.com/problems/check-if-a-string-contains-all-binary-codes-of-size-k
// Title: Check If a String Contains All Binary Codes of Size K
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a binary string s and an integer k, return true if every binary code of length k is a substring of s. Otherwise, return false.
//
// Example 1:
//
//   Input: s = "00110110", k = 2
//   Output: true
//   Explanation: The binary codes of length 2 are "00", "01", "10" and "11". They can be all found as substrings at indices 0, 1, 3 and 2 respectively.
//
// Example 2:
//
//   Input: s = "0110", k = 1
//   Output: true
//   Explanation: The binary codes of length 1 are "0" and "1", it is clear that both exist as a substring.
//
// Example 3:
//
//   Input: s = "0110", k = 2
//   Output: false
//   Explanation: The binary code "00" is of length 2 and does not exist in the array.
//
// Constraints:
//
//   1 <= s.length <= 5 * 10^5
//   s[i] is either '0' or '1'.
//   1 <= k <= 20
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"strconv"
)

type void struct{}

func hasAllCodes(s string, k int) bool {
	n := 1 << k // 2^k
	l := len(s)
	set := make(map[int]void, n)

	for i := 0; i <= l-k; i++ {
		num, _ := strconv.ParseInt(s[i:i+k], 2, 32)
		set[int(num)] = void{}
	}

	return len(set) == n
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

func hasAllCodes2(s string, k int) bool {
	n := 1 << k // 2^k
	l := len(s)

	// length too short
	if l < n-k+1 {
		return false
	}

	set := make([]int, n)
	leading := n >> 1 // binary 10..00 with length k

	num := 0
	for i, c := range s[:k] {
		if c == '1' {
			num |= 1 << i
		}
	}
	set[num] = 1

	for _, c := range s[k:] {
		num >>= 1
		if c == '1' {
			num |= leading
		}
		set[num] = 1
	}

	sum := 0
	for _, b := range set {
		sum += b
	}

	return sum == n
}
