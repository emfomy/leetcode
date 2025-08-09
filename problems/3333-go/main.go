// Source: https://leetcode.com/problems/find-the-original-typed-string-ii
// Title: Find the Original Typed String II
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Alice is attempting to type a specific string on her computer. However, she tends to be clumsy and **may** press a key for too long, resulting in a character being typed **multiple** times.
//
// You are given a string `word`, which represents the **final** output displayed on Alice's screen. You are also given a **positive** integer `k`.
//
// Return the total number of possible original strings that Alice might have intended to type, if she was trying to type a string of size **at least** `k`.
//
// Since the answer may be very large, return it **modulo** `10^9 + 7`.
//
// **Example 1:**
//
// ```
// Input: word = "aabbccdd", k = 7
// Output: 5
// Explanation:
// The possible strings are: `"aabbccdd"`, `"aabbccd"`, `"aabbcdd"`, `"aabccdd"`, and `"abbccdd"`.
// ```
//
// **Example 2:**
//
// ```
// Input: word = "aabbccdd", k = 8
// Output: 1
// Explanation:
// The only possible string is `"aabbccdd"`.
// ```
//
// **Example 3:**
//
// ```
// Input: word = "aaabbb", k = 3
// Output: 8
// ```
//
// **Constraints:**
//
// - `1 <= word.length <= 5 * 10^5`
// - `word` consists only of lowercase English letters.
// - `1 <= k <= 2000`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

const modulo = int(1e9 + 7)

// Use DP, O(n + k^3), TLE
//
// First convert the word into chunks of characters.
// For example, abbcccdddd is represents as [1, 2, 3, 4] (repeated lengths).
//
// Define DP(i, j) be the number of words using first i chunks with length j.
func possibleStringCount(word string, k int) int {
	n := len(word)
	if k > n {
		return 0
	}

	// Convert to chunk
	var chunks []int
	chunks = append(chunks, 1)
	for i := 1; i < n; i++ {
		if word[i] == word[i-1] {
			chunks[len(chunks)-1]++
		} else {
			chunks = append(chunks, 1)
		}
	}

	// Count total
	ans := 1
	for _, chunk := range chunks {
		ans *= chunk
		ans %= modulo
	}

	// Check
	k -= len(chunks)
	if k <= 0 {
		return ans
	}

	// DP
	curr := make([]int, k)
	curr[0] = 1
	for _, chunk := range chunks {
		next := make([]int, k)
		for j := range chunk {
			for i := range k - j {
				if curr[i] == 0 {
					break
				}
				next[i+j] += curr[i]
				next[i+j] %= modulo
			}
		}
		curr = next
	}

	for _, count := range curr {
		ans += modulo - count
		ans %= modulo
	}

	return ans % modulo
}

// Use DP, O(n + k^2)
//
// First convert the word into chunks of characters.
// For example, abbcccdddd is represents as C = [1, 2, 3, 4] (repeated lengths).
//
// Note that we can subtract k by len(C) and C[i] by 1,
// since each chunk must have at least one character.
//
// Define F(l, i) be the number of words using first l chunks with length i.
// We have F(0, 0) = 1 and F(l, i) = Sum[j = 0 to C(l)-1] F(l-1, i-j)
// Note that we only need to compute for i < (k - len(C))
//
// This DP has O(k^3) complexity.
// However, we only need to compute the sum of the last l.
//
// Define G(l, i) = Sum[j = 0 to i] F(l, j)
// Then F(l, i) = Sum[j = 0 to C(l)-1] F(l-1, i-j)
// .            = Sum[j = i-C(l)+1 to i] F(l-1, j)
// .            = G(l-1, i) - G(l-1, i-C(l))
// This reduce the complexity to O(k^2)
func possibleStringCount2(word string, k int) int {
	n := len(word)
	if k > n {
		return 0
	}

	// Convert to chunk
	var chunks []int
	chunks = append(chunks, 1)
	for i := 1; i < n; i++ {
		if word[i] == word[i-1] {
			chunks[len(chunks)-1]++
		} else {
			chunks = append(chunks, 1)
		}
	}

	// Count total
	ans := 1
	for _, chunk := range chunks {
		ans *= chunk
		ans %= modulo
	}

	// Check
	k -= len(chunks)
	if k <= 0 {
		return ans
	}

	// DP
	currG := make([]int, k)
	for i := range k {
		currG[i] = 1
	}

	for _, chunk := range chunks {
		nextF := make([]int, k)
		nextG := make([]int, k)
		for i := range k {
			nextF[i] = currG[i]
			if i-chunk >= 0 {
				nextF[i] = (currG[i] - currG[i-chunk] + modulo) % modulo
			}
		}
		nextG[0] = nextF[0]
		for i := range k - 1 {
			nextG[i+1] = (nextG[i] + nextF[i+1]) % modulo
		}
		currG = nextG
	}

	return (ans - currG[k-1] + modulo) % modulo
}
