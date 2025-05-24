// Source: https://leetcode.com/problems/final-array-state-after-k-multiplication-operations-i
// Title: Final Array State After K Multiplication Operations I
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `nums`, an integer `k`, and an integer `multiplier`.
//
// You need to perform `k` operations on `nums`. In each operation:
//
// - Find the **minimum** value `x` in `nums`. If there are multiple occurrences of the minimum value, select the one that appears **first**.
// - Replace the selected minimum value `x` with `x * multiplier`.
//
// Return an integer array denoting the final state of `nums` after performing all `k` operations.
//
// **Example 1:**
//
// ```
// Input: nums = [2,1,3,5,6], k = 5, multiplier = 2
//
// Output: [8,4,6,5,6]
//
// Explanation:
//
// | Operation         | Result          |
// |-------------------|-----------------|
// | After operation 1 | [2, 2, 3, 5, 6] |
// | After operation 2 | [4, 2, 3, 5, 6] |
// | After operation 3 | [4, 4, 3, 5, 6] |
// | After operation 4 | [4, 4, 6, 5, 6] |
// | After operation 5 | [8, 4, 6, 5, 6] |
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [1,2], k = 3, multiplier = 4
//
// Output: [16,8]
//
// Explanation:
//
// | Operation         | Result  |
// |-------------------|---------|
// | After operation 1 | [4, 2]  |
// | After operation 2 | [4, 8]  |
// | After operation 3 | [16, 8] |
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 100`
// - `1 <= nums[i] <= 100`
// - `1 <= k <= 10`
// - `1 <= multiplier <= 5`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"container/heap"
)

type pairType struct {
	num int
	idx int
}

type pairHeap []pairType

func (h pairHeap) Len() int { return len(h) }
func (h pairHeap) Less(i, j int) bool { // min-heap
	if h[i].num != h[j].num {
		return h[i].num < h[j].num
	}
	return h[i].idx < h[j].idx
}
func (h pairHeap) Swap(i, j int) { h[i], h[j] = h[j], h[i] }

func newPairHeap(arr []int) *pairHeap {
	h := make(pairHeap, 0, len(arr))
	for idx, num := range arr {
		h = append(h, pairType{
			num: num,
			idx: idx,
		})
	}
	heap.Init(&h)
	return &h
}

func (h *pairHeap) Push(x interface{}) {
	*h = append(*h, x.(pairType))
}

func (h *pairHeap) Pop() interface{} {
	n := len(*h)
	x := (*h)[n-1]
	*h = (*h)[:n-1]
	return x
}

func getFinalState(nums []int, k int, multiplier int) []int {
	h := newPairHeap(nums)

	for i := 0; i < k; i++ {
		pair := heap.Pop(h).(pairType)
		pair.num *= multiplier
		nums[pair.idx] *= multiplier
		heap.Push(h, pair)
	}

	return nums
}
