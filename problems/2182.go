// Source: https://leetcode.com/problems/construct-string-with-repeat-limit
// Title: Construct String With Repeat Limit
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a string `s` and an integer `repeatLimit`. Construct a new string `repeatLimitedString` using the characters of `s` such that no letter appears **more than** `repeatLimit` times **in a row**. You do **not** have to use all characters from `s`.
//
// Return the **lexicographically largest** `repeatLimitedString` possible.
//
// A string `a` is **lexicographically larger** than a string `b` if in the first position where `a` and `b` differ, string `a` has a letter that appears later in the alphabet than the corresponding letter in `b`. If the first `min(a.length, b.length)` characters do not differ, then the longer string is the lexicographically larger one.
//
// **Example 1:**
//
// ```
// Input: s = "cczazcc", repeatLimit = 3
// Output: "zzcccac"
// Explanation: We use all of the characters from s to construct the repeatLimitedString "zzcccac".
// The letter 'a' appears at most 1 time in a row.
// The letter 'c' appears at most 3 times in a row.
// The letter 'z' appears at most 2 times in a row.
// Hence, no letter appears more than repeatLimit times in a row and the string is a valid repeatLimitedString.
// The string is the lexicographically largest repeatLimitedString possible so we return "zzcccac".
// Note that the string "zzcccca" is lexicographically larger but the letter 'c' appears more than 3 times in a row, so it is not a valid repeatLimitedString.
// ```
//
// **Example 2:**
//
// ```
// Input: s = "aababab", repeatLimit = 2
// Output: "bbabaa"
// Explanation: We use only some of the characters from s to construct the repeatLimitedString "bbabaa".
// The letter 'a' appears at most 2 times in a row.
// The letter 'b' appears at most 2 times in a row.
// Hence, no letter appears more than repeatLimit times in a row and the string is a valid repeatLimitedString.
// The string is the lexicographically largest repeatLimitedString possible so we return "bbabaa".
// Note that the string "bbabaaa" is lexicographically larger but the letter 'a' appears more than 2 times in a row, so it is not a valid repeatLimitedString.
// ```
//
// **Constraints:**
//
// - `1 <= repeatLimit <= s.length <= 10^5`
// - `s` consists of lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"bytes"
	"fmt"
)

func repeatLimitedString(s string, repeatLimit int) string {
	freq := [26]int{}
	for _, char := range s {
		freq[char-'a']++
	}

	pendingIdx := rune(-1)
	var buffer bytes.Buffer

	for i := rune(25); i >= 0; i-- {
		if freq[i] == 0 {
			continue
		}

		if pendingIdx > 0 {
			buffer.WriteRune('a' + i)
			freq[i]--
			i = pendingIdx
			pendingIdx = -1
		} else {
			for j := 0; j < repeatLimit && freq[i] > 0; j++ {
				buffer.WriteRune('a' + i)
				freq[i]--
			}

			if freq[i] > 0 {
				pendingIdx = i + 1
			}
		}
	}

	return buffer.String()
}

func main() {
	fmt.Println(repeatLimitedString("aababab", 2))
}
