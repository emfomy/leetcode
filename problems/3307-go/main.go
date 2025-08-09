// Source: https://leetcode.com/problems/find-the-k-th-character-in-string-game-ii
// Title: Find the K-th Character in String Game II
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Alice and Bob are playing a game. Initially, Alice has a string `word = "a"`.
//
// You are given a **positive** integer `k`. You are also given an integer array `operations`, where `operations[i]` represents the **type** of the `i^th` operation.
//
// Now Bob will ask Alice to perform **all** operations in sequence:
//
// - If `operations[i] == 0`, **append** a copy of `word` to itself.
// - If `operations[i] == 1`, generate a new string by **changing** each character in `word` to its **next** character in the English alphabet, and **append** it to the original `word`. For example, performing the operation on `"c"` generates `"cd"` and performing the operation on `"zb"` generates `"zbac"`.
//
// Return the value of the `k^th` character in `word` after performing all the operations.
//
// **Note** that the character `'z'` can be changed to `'a'` in the second type of operation.
//
// **Example 1:**
//
// ```
// Input: k = 5, operations = [0,0,0]
// Output: "a"
// Explanation:
// Initially, `word == "a"`. Alice performs the three operations as follows:
// - Appends `"a"` to `"a"`, `word` becomes `"aa"`.
// - Appends `"aa"` to `"aa"`, `word` becomes `"aaaa"`.
// - Appends `"aaaa"` to `"aaaa"`, `word` becomes `"aaaaaaaa"`.
// ```
//
// **Example 2:**
//
// ```
// Input: k = 10, operations = [0,1,0,1]
// Output: "b"
// Explanation:
// Initially, `word == "a"`. Alice performs the four operations as follows:
// - Appends `"a"` to `"a"`, `word` becomes `"aa"`.
// - Appends `"bb"` to `"aa"`, `word` becomes `"aabb"`.
// - Appends `"aabb"` to `"aabb"`, `word` becomes `"aabbaabb"`.
// - Appends `"bbccbbcc"` to `"aabbaabb"`, `word` becomes `"aabbaabbbbccbbcc"`.
// ```
//
// **Constraints:**
//
// - `1 <= k <= 10^14`
// - `1 <= operations.length <= 100`
// - `operations[i]` is either 0 or 1.
// - The input is generated such that `word` has **at least** `k` characters after all operations.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"math/bits"
	"slices"
)

// Let word(i) be the word after i-th operation.
// We have word(0)[0] = 'a'
// Note that len(word(i)) is 2^(i+1).
//
// To compute word(i)[j],
// If j < len(word(i-1)) = 2^i, then word(i)[j] = word(i-1)[j].
// Otherwise, if op(i) = 0, word(i)[j] = word(i-1)[j-2^i].
// Otherwise, if op(i) = 1, word(i)[j] = word(i-1)[j-2^i]-1.
func kthCharacter(k int64, operations []int) byte {
	l := uint64(k - 1)
	shift := 0
	for i, op := range slices.Backward(operations) {
		if bits.Len64(l)-1 < i {
			continue
		}
		l -= (uint64(1) << i)
		shift += op
	}

	return 'a' + byte(shift%26)
}

// First let l = k-1
// Define ans(l) be the answer for l.
// We have ans(0) = 'a'.
// For l > 0, say the leading bit of l is 4 (i.e. 4 <= l < 8),
// then ans(l) = ans(l-4) + op
// Now we can use recursion to find the result.
//
// Note that we can find the result directly by count the bits of l.
func kthCharacter2(k int64, operations []int) byte {
	l := uint64(k - 1)
	step := 0
	for i := range bits.Len64(l) {
		if (l>>i)&1 == 1 {
			step += operations[i]
		}
	}
	return 'a' + byte(step%26)
}
