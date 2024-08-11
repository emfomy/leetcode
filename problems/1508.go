// Source: https://leetcode.com/problems/range-sum-of-sorted-subarray-sums
// Title: Range Sum of Sorted Subarray Sums
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given the array nums consisting of n positive integers. You computed the sum of all non-empty continuous subarrays from the array and then sorted them in non-decreasing order, creating a new array of n * (n + 1) / 2 numbers.
//
// Return the sum of the numbers from index left to index right (indexed from 1), inclusive, in the new array. Since the answer can be a huge number return it modulo 10^9 + 7.
//
// Example 1:
//
//   Input: nums = [1,2,3,4], n = 4, left = 1, right = 5
//   Output: 13
//   Explanation: All subarray sums are 1, 3, 6, 10, 2, 5, 9, 3, 7, 4. After sorting them in non-decreasing order we have the new array [1, 2, 3, 3, 4, 5, 6, 7, 9, 10]. The sum of the numbers from index le = 1 to ri = 5 is 1 + 2 + 3 + 3 + 4 = 13.
//
// Example 2:
//
//   Input: nums = [1,2,3,4], n = 4, left = 3, right = 4
//   Output: 6
//   Explanation: The given array is the same as example 1. We have the new array [1, 2, 3, 3, 4, 5, 6, 7, 9, 10]. The sum of the numbers from index le = 3 to ri = 4 is 3 + 3 = 6.
//
// Example 3:
//
//   Input: nums = [1,2,3,4], n = 4, left = 1, right = 10
//   Output: 50
//
// Constraints:
//
//   n == nums.length
//   1 <= nums.length <= 1000
//   1 <= nums[i] <= 100
//   1 <= left <= right <= n * (n + 1) / 2
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"container/heap"
)

type pair struct {
	sum   int
	left  int
	right int
}

type pairHeap []pair

func (h pairHeap) Len() int           { return len(h) }
func (h pairHeap) Less(i, j int) bool { return h[i].sum < h[j].sum } // we want min-heap
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

func (h *pairHeap) Peak() *pair {
	if h.Len() == 0 {
		return nil
	}
	return &(*h)[0]
}

const modulo = int(1e9 + 7)

func rangeSum(nums []int, n int, left int, right int) int {
	sumPairs := make([]pair, n)
	for idx, num := range nums {
		sumPairs[idx] = pair{sum: num, right: idx}
	}
	sumHeap := newPairHeap(sumPairs)

	left--
	res := 0
	for i := 0; i < right; i++ {
		item := heap.Pop(sumHeap).(pair)

		if i >= left {
			res += item.sum
			res %= modulo
		}

		item.right++
		if item.right < n {
			item.sum += nums[item.right]
			heap.Push(sumHeap, item)
		}
	}

	return res
}
