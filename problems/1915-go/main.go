// Source: https://leetcode.com/problems/number-of-wonderful-substrings
// Title: Number of Wonderful Substrings
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// A wonderful string is a string where at most one letter appears an odd number of times.
// For example, "ccjjc" and "abab" are wonderful, but "ab" is not.
//   * Given a string word that consists of the first ten lowercase English letters ('a' through 'j'), return the number of wonderful non-empty substrings in word. If the same substring appears multiple times in word, then count each occurrence separately.
// A substring is a contiguous sequence of characters in a string.
//
// Example 1:
//
//   Input: word = "aba"
//   Output: 4
//   Explanation:
//     The four wonderful substrings are underlined below:
//       * "aba" -> "a"
//       * "aba" -> "b"
//       * "aba" -> "a"
//       * "aba" -> "aba"
//
// Example 2:
//
//   Input: word = "aabb"
//   Output: 9
//   Explanation: The nine wonderful substrings are underlined below:
//     * "aabb" -> "a"
//     * "aabb" -> "aa"
//     * "aabb" -> "aab"
//     * "aabb" -> "aabb"
//     * "aabb" -> "a"
//     * "aabb" -> "abb"
//     * "aabb" -> "b"
//     * "aabb" -> "bb"
//     * "aabb" -> "b"
//
// Example 3:
//
//   Input: word = "he"
//   Output: 2
//   Explanation: The two wonderful substrings are underlined below:
//     * "he" -> "h"
//     * "he" -> "e"
//
// Constraints:
//
//   1 <= word.length <= 10^5
//   word consists of lowercase English letters from 'a' to 'j'.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"fmt"
	"math/bits"
	"strconv"
)

var alphaMap = map[byte]uint{
	'a': 1 << 0,
	'b': 1 << 1,
	'c': 1 << 2,
	'd': 1 << 3,
	'e': 1 << 4,
	'f': 1 << 5,
	'g': 1 << 6,
	'h': 1 << 7,
	'i': 1 << 8,
	'j': 1 << 9,
}

func wonderfulSubstrings(word string) int64 {
	n := len(word)
	l, r := 0, 1

	res := int64(0)

	alphaCount := alphaMap[word[0]]

	for {
		fmt.Println(l, r, word[l:r], strconv.FormatUint(uint64(alphaCount), 2), bits.OnesCount(alphaCount))
		// Check if substr is wonderful
		if bits.OnesCount(alphaCount) <= 1 {
			res++
			if r >= n {
				break
			}
			alphaCount ^= alphaMap[word[r]]
			r++
		} else {
			alphaCount ^= alphaMap[word[l]]
			l++
			if l == r {
				if r >= n {
					break
				}
				alphaCount ^= alphaMap[word[r]]
				r++
			}
		}
	}

	return res
}
