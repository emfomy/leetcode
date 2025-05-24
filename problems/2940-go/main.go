// Source: https://leetcode.com/problems/find-building-where-alice-and-bob-can-meet
// Title: Find Building Where Alice and Bob Can Meet
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a **0-indexed** array `heights` of positive integers, where `heights[i]` represents the height of the `i^th` building.
//
// If a person is in building `i`, they can move to any other building `j` if and only if `i < j` and `heights[i] < heights[j]`.
//
// You are also given another array `queries` where `queries[i] = [a_i, b_i]`. On the `i^th` query, Alice is in building `a_i` while Bob is in building `b_i`.
//
// Return an array `ans` where `ans[i]` is **the index of the leftmost building** where Alice and Bob can meet on the `i^th` query. If Alice and Bob cannot move to a common building on query `i`, set `ans[i]` to `-1`.
//
// **Example 1:**
//
// ```
// Input: heights = [6,4,8,5,2,7], queries = [[0,1],[0,3],[2,4],[3,4],[2,2]]
// Output: [2,5,-1,5,2]
// Explanation: In the first query, Alice and Bob can move to building 2 since heights[0] < heights[2] and heights[1] < heights[2].
// In the second query, Alice and Bob can move to building 5 since heights[0] < heights[5] and heights[3] < heights[5].
// In the third query, Alice cannot meet Bob since Alice cannot move to any other building.
// In the fourth query, Alice and Bob can move to building 5 since heights[3] < heights[5] and heights[4] < heights[5].
// In the fifth query, Alice and Bob are already in the same building.
// For ans[i] != -1, It can be shown that ans[i] is the leftmost building where Alice and Bob can meet.
// For ans[i] == -1, It can be shown that there is no building where Alice and Bob can meet.
// ```
//
// **Example 2:**
//
// ```
// Input: heights = [5,3,8,2,6,1,4,6], queries = [[0,7],[3,5],[5,2],[3,0],[1,6]]
// Output: [7,6,-1,4,6]
// Explanation: In the first query, Alice can directly move to Bob's building since heights[0] < heights[7].
// In the second query, Alice and Bob can move to building 6 since heights[3] < heights[6] and heights[5] < heights[6].
// In the third query, Alice cannot meet Bob since Bob cannot move to any other building.
// In the fourth query, Alice and Bob can move to building 4 since heights[3] < heights[4] and heights[0] < heights[4].
// In the fifth query, Alice can directly move to Bob's building since heights[1] < heights[6].
// For ans[i] != -1, It can be shown that ans[i] is the leftmost building where Alice and Bob can meet.
// For ans[i] == -1, It can be shown that there is no building where Alice and Bob can meet.
// ```
//
// **Constraints:**
//
// - `1 <= heights.length <= 5 * 10^4`
// - `1 <= heights[i] <= 10^9`
// - `1 <= queries.length <= 5 * 10^4`
// - `queries[i] = [a_i, b_i]`
// - `0 <= a_i, b_i <= heights.length - 1`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"container/heap"
)

// TLE
func leftmostBuildingQueries(heights []int, queries [][]int) []int {
	n := len(heights)
	res := make([]int, 0, len(queries))

loop:
	for _, query := range queries {
		a, b := query[0], query[1]

		// WLOG, assume a <= b
		if a > b {
			a, b = b, a
		}

		// Pick b if a = b or ha < hb
		ha, hb := heights[a], heights[b]
		if a == b || ha < hb {
			res = append(res, b)
			continue loop
		}

		// Find hc > ha
		// Note thant since ha >= hb, we have hc > hb
		for c := b + 1; c < n; c++ {
			if heights[c] > ha {
				res = append(res, c)
				continue loop
			}
		}
		res = append(res, -1)
	}

	return res
}

type deferType struct {
	height int
	idx    int
}

type deferHeap []deferType

func (h deferHeap) Len() int           { return len(h) }
func (h deferHeap) Less(i, j int) bool { return h[i].height < h[j].height } // min-heap
func (h deferHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }

func newDeferHeap(n int) *deferHeap {
	arr := make([]deferType, 0, n)
	h := deferHeap(arr)
	heap.Init(&h)
	return &h
}

func (h *deferHeap) Push(x interface{}) {
	*h = append(*h, x.(deferType))
}

func (h *deferHeap) Pop() interface{} {
	n := len(*h)
	x := (*h)[n-1]
	*h = (*h)[:n-1]
	return x
}

func (h *deferHeap) Peak() *deferType {
	if h.Len() == 0 {
		return nil
	}
	return &(*h)[0]
}

func leftmostBuildingQueries2(heights []int, queries [][]int) []int {
	n := len(heights)
	m := len(queries)

	deffered := make([][]deferType, n)
	for i := range n {
		deffered[i] = make([]deferType, 0)
	}

	res := make([]int, m)
	for i := range m {
		res[i] = -1
	}

	for idx, query := range queries {
		a, b := query[0], query[1]
		if a > b { // WLOG, assume a <= b
			a, b = b, a
		}

		if a == b || heights[a] < heights[b] {
			res[idx] = b
		} else {
			deffered[b] = append(deffered[b], deferType{
				height: heights[a],
				idx:    idx,
			})
		}
	}

	pq := newDeferHeap(m)
	for b, dqueries := range deffered {
		for _, query := range dqueries {
			heap.Push(pq, query)
		}

		for pq.Len() > 0 && pq.Peak().height < heights[b] {
			res[pq.Peak().idx] = b
			heap.Pop(pq)
		}
	}

	return res
}
