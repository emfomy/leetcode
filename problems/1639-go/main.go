// Source: https://leetcode.com/problems/number-of-ways-to-form-a-target-string-given-a-dictionary
// Title: Number of Ways to Form a Target String Given a Dictionary
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a list of strings of the **same length** `words` and a string `target`.
//
// Your task is to form `target` using the given `words` under the following rules:
//
// - `target` should be formed from left to right.
// - To form the `i^th` character (**0-indexed** ) of `target`, you can choose the `k^th` character of the `j^th` string in `words` if `target[i] = words[j][k]`.
// - Once you use the `k^th` character of the `j^th` string of `words`, you **can no longer** use the `x^th` character of any string in `words` where `x <= k`. In other words, all characters to the left of or at index `k` become unusuable for every string.
// - Repeat the process until you form the string `target`.
//
// **Notice** that you can use **multiple characters** from the **same string** in `words` provided the conditions above are met.
//
// Return the number of ways to form `target` from `words`. Since the answer may be too large, return it **modulo** `10^9 + 7`.
//
// **Example 1:**
//
// ```
// Input: words = ["acca","bbbb","caca"], target = "aba"
// Output: 6
// Explanation: There are 6 ways to form target.
// "aba" -> index 0 ("acca"), index 1 ("bbbb"), index 3 ("caca")
// "aba" -> index 0 ("acca"), index 2 ("bbbb"), index 3 ("caca")
// "aba" -> index 0 ("acca"), index 1 ("bbbb"), index 3 ("acca")
// "aba" -> index 0 ("acca"), index 2 ("bbbb"), index 3 ("acca")
// "aba" -> index 1 ("caca"), index 2 ("bbbb"), index 3 ("acca")
// "aba" -> index 1 ("caca"), index 2 ("bbbb"), index 3 ("caca")
// ```
//
// **Example 2:**
//
// ```
// Input: words = ["abba","baab"], target = "bab"
// Output: 4
// Explanation: There are 4 ways to form target.
// "bab" -> index 0 ("baab"), index 1 ("baab"), index 2 ("abba")
// "bab" -> index 0 ("baab"), index 1 ("baab"), index 3 ("baab")
// "bab" -> index 0 ("baab"), index 2 ("baab"), index 3 ("baab")
// "bab" -> index 1 ("abba"), index 2 ("baab"), index 3 ("baab")
// ```
//
// **Constraints:**
//
// - `1 <= words.length <= 1000`
// - `1 <= words[i].length <= 1000`
// - All strings in `words` have the same length.
// - `1 <= target.length <= 1000`
// - `words[i]` and `target` contain only lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

const modulo = int(1e9 + 7)

// 2D-DP
func numWays(words []string, target string) int {
	ni := len(target)
	nj := len(words[0])

	// Count chars in each positions
	counts := make([][26]int, nj)
	for _, word := range words {
		for j := range word {
			counts[j][word[j]-'a']++
		}
	}

	dp := make([][]int, ni)
	for i := range ni {
		dp[i] = make([]int, nj)
	}

	{ // i = 0
		ch := target[0] - 'a'
		for j := range nj {
			dp[0][j] = counts[j][ch]
		}
		for j := 1; j < nj; j++ {
			dp[0][j] += dp[0][j-1]
			dp[0][j] %= modulo
		}
	}

	for i := 1; i < ni; i++ {
		ch := target[i] - 'a'
		for j := 1; j < nj; j++ {
			dp[i][j] = counts[j][ch] * dp[i-1][j-1]
		}
		for j := 1; j < nj; j++ {
			dp[i][j] += dp[i][j-1]
			dp[i][j] %= modulo
		}
	}

	return dp[ni-1][nj-1]
}

// 1D-DP
func numWays2(words []string, target string) int {
	ni := len(target)
	nj := len(words[0])

	// Count chars in each positions
	counts := make([][26]int, nj)
	for _, word := range words {
		for j := range word {
			counts[j][word[j]-'a']++
		}
	}

	prev := make([]int, nj)
	curr := make([]int, nj)

	{ // i = 0
		ch := target[0] - 'a'
		for j := range nj {
			curr[j] = counts[j][ch]
		}
		for j := 1; j < nj; j++ {
			curr[j] += curr[j-1]
			curr[j] %= modulo
		}
	}

	for i := 1; i < ni; i++ {
		curr, prev = prev, curr
		for j := range nj {
			curr[j] = 0
		}
		ch := target[i] - 'a'
		for j := 1; j < nj; j++ {
			curr[j] = counts[j][ch] * prev[j-1]
		}
		for j := 1; j < nj; j++ {
			curr[j] += curr[j-1]
			curr[j] %= modulo
		}
	}

	return curr[nj-1]
}

// 1D-DP
func numWays3(words []string, target string) int {
	ni := len(target)
	nj := len(words[0])

	// Escape
	if ni > nj {
		return 0
	}

	// Count chars in each positions
	counts := make([][26]int, nj)
	for _, word := range words {
		for j := range word {
			counts[j][word[j]-'a']++
		}
	}

	// DP
	nk := nj - ni + 1
	prev := make([]int, nk)
	curr := make([]int, nk)

	{ // i = 0
		ch := target[0] - 'a'
		for j := range nk {
			curr[j] = counts[j][ch]
		}
		for j := 1; j < nk; j++ {
			curr[j] += curr[j-1]
		}
	}

	for i := 1; i < ni; i++ {
		curr, prev = prev, curr

		ch := target[i] - 'a'
		for j := 0; j < nk; j++ {
			curr[j] = (counts[i+j][ch] * prev[j]) % modulo
		}
		for j := 1; j < nk; j++ {
			curr[j] += curr[j-1]
		}
	}

	return curr[nk-1] % modulo
}
