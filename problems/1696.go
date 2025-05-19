// Source: https://leetcode.com/problems/jump-game-vi
// Title: Jump Game VI
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a 0-indexed integer array nums and an integer k.
//
// You are initially standing at index 0. In one move, you can jump at most k steps forward without going outside the boundaries of the array. That is, you can jump from index i to any index in the range [i + 1, min(n - 1, i + k)] inclusive.
//
// You want to reach the last index of the array (index n - 1). Your score is the sum of all nums[j] for each index j you visited in the array.
//
// Return the maximum score you can get.
//
// Example 1:
//
//   Input: nums = [1,-1,-2,4,-7,3], k = 2
//   Output: 7
//   Explanation: You can choose your jumps forming the subsequence [1,-1,4,3] (underlined above). The sum is 7.
//
// Example 2:
//
//   Input: nums = [10,-5,-2,4,0,3], k = 3
//   Output: 17
//   Explanation: You can choose your jumps forming the subsequence [10,4,3] (underlined above). The sum is 17.
//
// Example 3:
//
//   Input: nums = [1,-5,-20,4,-1,3,-6,-3], k = 2
//   Output: 0
//
// Constraints:
//
//   1 <= nums.length, k <= 10^5
//   -10^4 <= nums[i] <= 10^4
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"container/heap"
)

type pair struct {
	idx int
	val int
}

type pairHeap []pair

func (h pairHeap) Len() int           { return len(h) }
func (h pairHeap) Less(i, j int) bool { return h[i].val > h[j].val } // max-heap
func (h pairHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }

func newPairHeap(arr []pair) *pairHeap {
	h := pairHeap(arr)
	heap.Init(&h)
	return &h
}

func (h *pairHeap) Push(x interface{}) {
	*h = append(*h, x.(pair))
}

func (h *pairHeap) Pop() interface{} {
	n := len(*h)
	x := (*h)[n-1]
	*h = (*h)[:n-1]
	return x
}

func (h *pairHeap) Peak() pair {
	if h.Len() == 0 {
		return pair{}
	}
	return (*h)[0]
}

func maxResult(nums []int, k int) int {
	n := len(nums)

	dp := newPairHeap(make([]pair, 0, n))

	curr := pair{
		idx: 0,
		val: nums[0],
	}
	dp.Push(curr)

	for i := 1; i < n; i++ {
		prev := dp.Peak()
		for i-prev.idx > k {
			heap.Pop(dp)
			prev = dp.Peak()
		}
		curr = pair{
			idx: i,
			val: nums[i] + prev.val,
		}
		heap.Push(dp, curr)
	}

	return curr.val
}
