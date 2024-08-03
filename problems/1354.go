// Source: https://leetcode.com/problems/construct-target-array-with-multiple-sums
// Title: Construct Target Array With Multiple Sums
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an array target of n integers. From a starting array arr consisting of n 1's, you may perform the following procedure :
//
// let x be the sum of all elements currently in your array.
// choose index i, such that 0 <= i < n and set the value of arr at index i to x.
// You may repeat this procedure as many times as needed.
// Return true if it is possible to construct the target array from arr, otherwise, return false.
//
// Example 1:
//
//   Input: target = [9,3,5]
//   Output: true
//   Explanation:
//     Start with arr = [1, 1, 1]
//     [1, 1, 1], sum = 3 choose index 1
//     [1, 3, 1], sum = 5 choose index 2
//     [1, 3, 5], sum = 9 choose index 0
//     [9, 3, 5] Done
//
// Example 2:
//
//   Input: target = [1,1,1,2]
//   Output: false
//   Explanation: Impossible to create target array from [1,1,1,1].
//
// Example 3:
//
//   Input: target = [8,5]
//   Output: true
//
// Constraints:
//
// n == target.length
// 1 <= n <= 5 * 10^4
// 1 <= target[i] <= 10^9
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"container/heap"
	"sort"
)

type intHeap []int

func (h intHeap) Len() int           { return len(h) }
func (h intHeap) Less(i, j int) bool { return h[i] > h[j] } // we want max-heap
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

// Do it backward
// Start from target array.
// Let v be the largest number and substract it by sum-v.
// Loop until reach all ones.
func isPossible(target []int) bool {
	n := len(target)
	if n == 1 { // Edge case
		return target[0] == 1
	}

	sort.Ints(target)
	store := newIntHeap(target)

	// Sum array
	sum := 0
	for _, v := range *store {
		sum += v
	}

	for true {
		val := heap.Pop(store).(int)
		sum -= val

		if val == 1 || sum == 1 {
			return true
		}

		if sum > val || sum == 0 || val%sum == 0 {
			return false
		}

		val %= sum
		sum += val
		heap.Push(store, val)
	}

	return true
}
