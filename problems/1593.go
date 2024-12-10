// Source: https://leetcode.com/problems/split-a-string-into-the-max-number-of-unique-substrings
// Split a String Into the Max Number of Unique Substrings
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a string s, return the maximum number of unique substrings that the given string can be split into.
// You can split string s into any list of non-empty substrings, where the concatenation of the substrings forms the original string. However, you must split the substrings such that all of them are unique.
// A substring is a contiguous sequence of characters within a string.
//
// Example 1:
//
//   Input: s = "ababccc"
//   Output: 5
//   Explanation: One way to split maximally is ['a', 'b', 'ab', 'c', 'cc']. Splitting like ['a', 'b', 'a', 'b', 'c', 'cc'] is not valid as you have 'a' and 'b' multiple times.
//
// Example 2:
//
//   Input: s = "aba"
//   Output: 2
//   Explanation: One way to split maximally is ['a', 'ba'].
//
// Example 3:
//
//   Input: s = "aa"
//   Output: 1
//   Explanation: It is impossible to split the string any further.
//
// Constraints:
//
//   1 <= s.length <= 16
//   s contains only lower case English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// Loop for all possible splits
func maxUniqueSplit(s string) int {
	n := len(s) - 1
	m := uint(1) << n

	res := 0

OUTER:
	for bits := uint(0); bits < m; bits++ {
		words := make(map[string]bool, n+1)

		// Construct split
		substr := ""
		for b := 0; b < n; b++ { // loop for bits
			substr += string(s[b])
			if (bits >> b & 1) == 1 {
				if words[substr] {
					continue OUTER
				}
				words[substr] = true
				substr = ""
			}
		}
		substr += string(s[n])
		if words[substr] {
			continue OUTER
		}
		words[substr] = true

		res = max(res, len(words))
	}

	return res
}

// Backtracking
func maxUniqueSplit2(s string) int {
	n := len(s)
	seen := make(map[string]bool, 1<<n)

	var backtrack func(start int) int
	backtrack = func(start int) int {
		if start == n {
			return 0
		}

		maxSplits := 0
		for end := start + 1; end <= n; end++ {
			word := s[start:end]
			if seen[word] {
				continue
			}

			seen[word] = true
			maxSplits = max(maxSplits, 1+backtrack(end))
			seen[word] = false
		}
		return maxSplits
	}

	return backtrack(0)
}
