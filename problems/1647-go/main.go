// Source: https://leetcode.com/problems/minimum-deletions-to-make-character-frequencies-unique
// Title: Minimum Deletions to Make Character Frequencies Unique
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// A string s is called good if there are no two different characters in s that have the same frequency.
//
// Given a string s, return the minimum number of characters you need to delete to make s good.
//
// The frequency of a character in a string is the number of times it appears in the string. For example, in the string "aab", the frequency of 'a' is 2, while the frequency of 'b' is 1.
//
// Example 1:
//
//   Input: s = "aab"
//   Output: 0
//   Explanation: s is already good.
//
// Example 2:
//
//   Input: s = "aaabbbcc"
//   Output: 2
//   Explanation:
//     You can delete two 'b's resulting in the good string "aaabcc".
//     Another way it to delete one 'b' and one 'c' resulting in the good string "aaabbc".
//
// Example 3:
//
//   Input: s = "ceabaacb"
//   Output: 2
//   Explanation:
//     You can delete both 'c's resulting in the good string "eabaab".
//     Note that we only care about characters that are still in the string at the end (i.e. frequency of 0 is ignored).
//
// Constraints:
//
//   1 <= s.length <= 10^5
//   s contains only lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"container/heap"
)

type intHeap []int

func (h intHeap) Len() int           { return len(h) }
func (h intHeap) Less(i, j int) bool { return h[i] > h[j] } // max-heap
func (h intHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }

func newIntHeap(arr []int) *intHeap {
	h := intHeap(arr)
	heap.Init(&h)
	return &h
}

func (h *intHeap) Push(x interface{}) {
	*h = append(*h, x.(int))
}

func (h *intHeap) Pop() interface{} {
	n := len(*h)
	x := (*h)[n-1]
	*h = (*h)[:n-1]
	return x
}

func minDeletions(s string) int {
	counts := make([]int, 26) // map char to its count

	// Count chars
	for i := 0; i < len(s); i++ {
		ch := s[i] - 'a'
		counts[ch]++
	}

	// Make heap
	countHeap := newIntHeap(counts)

	res := 0
	prevCount := 100_000

	for countHeap.Len() > 0 && prevCount > 0 {
		count := heap.Pop(countHeap).(int)
		if count >= prevCount {
			prevCount--
			res += count - prevCount
		} else {
			prevCount = count
		}
	}

	for countHeap.Len() > 0 {
		count := heap.Pop(countHeap).(int)
		res += count
	}

	return res
}
