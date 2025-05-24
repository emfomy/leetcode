// Source: https://leetcode.com/problems/zero-array-transformation-iii
// Title: Zero Array Transformation III
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `nums` of length `n` and a 2D array `queries` where `queries[i] = [l_i, r_i]`.
//
// Each `queries[i]` represents the following action on `nums`:
//
// - Decrement the value at each index in the range `[l_i, r_i]` in `nums` by **at most** 1.
// - The amount by which the value is decremented can be chosen **independently** for each index.
//
// A **Zero Array** is an array with all its elements equal to 0.
//
// Return the **maximum** number of elements that can be removed from `queries`, such that `nums` can still be converted to a **zero array** using the remaining queries. If it is not possible to convert `nums` to a **zero array**, return -1.
//
// **Example 1:**
//
// ```
// Input: nums = [2,0,2], queries = [[0,2],[0,2],[1,1]]
// Output: 1
// Explanation:
// After removing `queries[2]`, `nums` can still be converted to a zero array.
// - Using `queries[0]`, decrement `nums[0]` and `nums[2]` by 1 and `nums[1]` by 0.
// - Using `queries[1]`, decrement `nums[0]` and `nums[2]` by 1 and `nums[1]` by 0.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [1,1,1,1], queries = [[1,3],[0,2],[1,3],[1,2]]
// Output: 2
// Explanation:
// We can remove `queries[2]` and `queries[3]`.
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [1,2,3,4], queries = [[0,3]]
// Output: -1
// Explanation:
// `nums` cannot be converted to a zero array even after using all the queries.
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 10^5`
// - `0 <= nums[i] <= 10^5`
// - `1 <= queries.length <= 10^5`
// - `queries[i].length == 2`
// - `0 <= l_i <= r_i < nums.length`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"container/heap"
	"slices"
)

// Use greedy
//
// Loop through the numbers
// Always pick the query with the largest end
func maxRemoval(nums []int, queries [][]int) int {
	n := len(nums)
	q := len(queries)

	// Sort queries by start
	slices.SortFunc(queries, func(a, b []int) int {
		return a[0] - b[0]
	})

	// Heap
	h := newIntHeap(n)

	// Greedy
	diffs := make([]int, n+1)
	curr := 0
	qIdx := 0
	for i, num := range nums {
		curr += diffs[i]
		num -= curr
		for ; qIdx < q; qIdx++ {
			if queries[qIdx][0] > i {
				break
			}
			heap.Push(h, queries[qIdx][1])
		}

		if num > h.Len() { // not enough query
			return -1
		}
		for ; num > 0; num-- {
			end := heap.Pop(h).(int)
			if end < i {
				return -1
			}
			curr++
			diffs[end+1]--
		}
	}

	return h.Len()
}

type intHeap []int

func (h intHeap) Len() int           { return len(h) }
func (h intHeap) Less(i, j int) bool { return h[i] > h[j] } // max-heap
func (h intHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }

func newIntHeap(n int) *intHeap {
	h := make(intHeap, 0, n)
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
