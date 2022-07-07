// Source: https://leetcode.com/problems/longest-consecutive-sequence/
// Title: Longest Consecutive Sequence
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an unsorted array of integers nums, return the length of the longest consecutive elements sequence.
//
// You must write an algorithm that runs in O(n) time.
//
// Example 1:
//
//   Input: nums = [100,4,200,1,3,2]
//   Output: 4
//   Explanation: The longest consecutive elements sequence is [1, 2, 3, 4]. Therefore its length is 4.
//
// Example 2:
//
//   Input: nums = [0,3,7,2,5,8,4,6,0,1]
//   Output: 9
//
// Constraints:
//
//   0 <= nums.length <= 10^5
//   -10^9 <= nums[i] <= 10^9
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"container/heap"
	"math"
)

type intHeap []int

func (h intHeap) Len() int           { return len(h) }
func (h intHeap) Less(i, j int) bool { return h[i] < h[j] }
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

func longestConsecutive(nums []int) int {
	n := len(nums)
	h := newIntHeap(nums)

	res := 0
	currLen := 0
	prevVal := math.MaxInt32
	for i := 0; i < n; i++ {
		currVal := heap.Pop(h).(int)
		if currVal == prevVal {
			continue
		}
		if currVal-prevVal == 1 {
			currLen++
		} else {
			res = _max(res, currLen)
			currLen = 1
		}
		prevVal = currVal
	}
	res = _max(res, currLen)

	return res
}

func _max(a, b int) int {
	if a > b {
		return a
	}
	return b
}
