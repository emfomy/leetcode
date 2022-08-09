// Source: https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/
// Title: Kth Smallest Element in a Sorted Matrix
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an n x n matrix where each of the rows and columns is sorted in ascending order, return the kth smallest element in the matrix.
//
// Note that it is the kth smallest element in the sorted order, not the kth distinct element.
//
// You must find a solution with a memory complexity better than O(n2).
//
// Example 1:
//
//   Input: matrix = [[1,5,9],[10,11,13],[12,13,15]], k = 8
//   Output: 13
//   Explanation: The elements in the matrix are [1,5,9,10,11,12,13,13,15], and the 8th smallest number is 13
//
// Example 2:
//
//   Input: matrix = [[-5]], k = 1
//   Output: -5
//
// Constraints:
//
//   n == matrix.length == matrix[i].length
//   1 <= n <= 300
//   -10^9 <= matrix[i][j] <= 10^9
//   All the rows and columns of matrix are guaranteed to be sorted in non-decreasing order.
//   1 <= k <= n^2
//
// Follow up:
//
//   Could you solve the problem with a constant memory (i.e., O(1) memory complexity)?
//   Could you solve the problem in O(n) time complexity? The solution may be too advanced for an interview but you may find reading this paper fun.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"container/heap"
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

func (h *intHeap) Peak() int {
	if h.Len() == 0 {
		return -1
	}
	return (*h)[0]
}

func kthSmallest(matrix [][]int, k int) int {
	h := newIntHeap(make([]int, 0, k))
	for _, row := range matrix {
		for _, v := range row {
			if h.Len() == k {
				if v > h.Peak() {
					continue
				}
				heap.Pop(h)
			}
			heap.Push(h, v)
		}
	}
	return h.Peak()
}
