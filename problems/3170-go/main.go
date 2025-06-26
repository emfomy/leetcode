// Source: https://leetcode.com/problems/lexicographically-minimum-string-after-removing-stars
// Title: Lexicographically Minimum String After Removing Stars
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a string `s`. It may contain any number of `'*'` characters. Your task is to remove all `'*'` characters.
//
// While there is a `'*'`, do the following operation:
//
// - Delete the leftmost `'*'` and the **smallest** non-`'*'` character to its left. If there are several smallest characters, you can delete any of them.
//
// Return the **lexicographically smallest** resulting string after removing all `'*'` characters.
//
// A string a is **lexicographically smaller** than a string b if in the first position where a and b differ, string a has a letter that appears earlier in the alphabet than the corresponding letter in b.
// If the first min(a.length, b.length) characters do not differ, then the shorter string is the lexicographically smaller one.
//
// **Example 1:**
//
// ```
// Input: s = "aaba*"
// Output: "aab"
// Explanation:
// We should delete one of the `'a'` characters with `'*'`. If we choose `s[3]`, `s` becomes the lexicographically smallest.
// ```
//
// **Example 2:**
//
// ```
// Input: s = "abc"
// Output: "abc"
// Explanation:
// There is no `'*'` in the string.
// ```
//
// **Constraints:**
//
// - `1 <= s.length <= 10^5`
// - `s` consists only of lowercase English letters and `'*'`.
// - The input is generated such that it is possible to delete all `'*'` characters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"github.com/emirpasic/gods/trees/binaryheap"
)

// It is always better to remove the right most letter.
func clearStars(s string) string {
	n := len(s)

	// Heap
	type itemType struct {
		ch  byte
		idx int
	}
	heap := binaryheap.NewWith(func(a, b any) int {
		aa, bb := a.(itemType), b.(itemType)
		if aa.ch != bb.ch {
			return int(aa.ch) - int(bb.ch)
		}
		return bb.idx - aa.idx
	})

	// Simulation
	removed := make([]bool, n)
	for idx := range s {
		ch := s[idx]
		if ch != '*' {
			heap.Push(itemType{ch: ch, idx: idx})
			continue
		}
		removed[idx] = true

		// Remove letter
		item, ok := heap.Pop()
		if !ok {
			continue
		}
		removed[item.(itemType).idx] = true
	}

	// Answer
	ans := make([]byte, 0, n)
	for i := range n {
		if !removed[i] {
			ans = append(ans, s[i])
		}
	}

	return string(ans)
}
