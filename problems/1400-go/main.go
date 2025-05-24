// Source: https://leetcode.com/problems/construct-k-palindrome-strings
// Title: Construct K Palindrome Strings
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a string `s` and an integer `k`, return `true` if you can use all the characters in `s` to construct `k` palindrome strings or `false` otherwise.

// **Example 1:**

// ```
// Input: s = "annabelle", k = 2
// Output: true
// Explanation: You can construct two palindromes using all characters in s.
// Some possible constructions "anna" + "elble", "anbna" + "elle", "anellena" + "b"
// ```

// **Example 2:**

// ```
// Input: s = "leetcode", k = 3
// Output: false
// Explanation: It is impossible to construct 3 palindromes using all the characters of s.
// ```

// **Example 3:**

// ```
// Input: s = "true", k = 4
// Output: true
// Explanation: The only possible solution is to put each character in a separate string.
// ```

// **Constraints:**

// - `1 <= s.length <= 10^5`
// - `s` consists of lowercase English letters.
// - `1 <= k <= 10^5`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// A palindrome can contain at most one alphabet with odd numbers
// We only need to count the alphabets in `s`
// and find if the number of odd alphabets is less than `k`.
func canConstruct(s string, k int) bool {
	if len(s) < k {
		return false
	}

	counts := [26]bool{}
	for i := 0; i < len(s); i++ {
		ch := s[i] - 'a'
		counts[ch] = !counts[ch]
	}

	odds := 0
	for i := 0; i < 26; i++ {
		if counts[i] {
			odds++
		}
	}

	return odds <= k
}
