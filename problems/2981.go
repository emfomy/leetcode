// Source: https://leetcode.com/problems/find-longest-special-substring-that-occurs-thrice-i
// Title: Find Longest Special Substring That Occurs Thrice I
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a string `s` that consists of lowercase English letters.
//
// A string is called **special**  if it is made up of only a single character. For example, the string `"abc"` is not special, whereas the strings `"ddd"`, `"zz"`, and `"f"` are special.
//
// Return the length of the **longest special substring**  of `s` which occurs **at least thrice** , or `-1` if no special substring occurs at least thrice.
//
// A **substring**  is a contiguous **non-empty**  sequence of characters within a string.
//
// **Example 1:**
//
// ```
// Input: s = "aaaa"
// Output: 2
// Explanation: The longest special substring which occurs thrice is "aa": substrings "**aa** aa", "a**aa** a", and "aa**aa** ".
// It can be shown that the maximum length achievable is 2.
// ```
//
// **Example 2:**
//
// ```
// Input: s = "abcdef"
// Output: -1
// Explanation: There exists no special substring which occurs at least thrice. Hence return -1.
// ```
//
// **Example 3:**
//
// ```
// Input: s = "abcaba"
// Output: 1
// Explanation: The longest special substring which occurs thrice is "a": substrings "**a** bcaba", "abc**a** ba", and "abcab**a** ".
// It can be shown that the maximum length achievable is 1.
// ```
//
// **Constraints:**
//
// - `3 <= s.length <= 50`
// - `s` consists of only lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func maximumLength(s string) int {
	n := len(s)

	res := -1

	// Loop for substring length
LoopLength:
	for l := 1; l <= n; l++ {
		count := [26]int{}

		// Loop for substrings
	LoopSubstr:
		for i := 0; i <= n-l; i++ {

			// Check if is special
			ch := s[i]
			for j := 1; j < l; j++ {
				if s[i+j] != ch {
					continue LoopSubstr
				}
			}

			idx := ch - 'a'
			count[idx]++
			if count[idx] == 3 {
				res = l
				continue LoopLength
			}
		}
	}

	return res
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// fn should be be arr[mid] < target for bisect left
// fn should be be arr[mid] <= target for bisect right
func bisectFunc(fn func(int) bool, lo, hi int) int {
	for lo < hi {
		mid := (lo + hi) / 2
		if fn(mid) {
			lo = mid + 1
		} else {
			hi = mid
		}
	}
	return lo
}

// Binary search
func maximumLength2(s string) int {
	n := len(s)

	lo := 1
	hi := n

	fn := func(l int) bool {
		count := [26]int{}

		// Loop for substrings
	Loop:
		for i := 0; i <= n-l; i++ {

			// Check if is special
			ch := s[i]
			for j := 1; j < l; j++ {
				if s[i+j] != ch {
					continue Loop
				}
			}

			idx := ch - 'a'
			count[idx]++
			if count[idx] == 3 {
				return true
			}
		}
		return false
	}

	// Binary search
	res := -1
	for lo < hi {
		mid := (lo + hi) / 2
		if fn(mid) {
			res = mid
			lo = mid + 1
		} else {
			hi = mid
		}
	}

	return res
}
