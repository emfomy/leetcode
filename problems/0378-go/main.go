// Source: https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix
// Title: Kth Smallest Element in a Sorted Matrix
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an `n x n` `matrix` where each of the rows and columns is sorted in ascending order, return the `k^th` smallest element in the matrix.
//
// Note that it is the `k^th` smallest element **in the sorted order**, not the `k^th` **distinct** element.
//
// You must find a solution with a memory complexity better than `O(n^2)`.
//
// **Example 1:**
//
// ```
// Input: matrix = [[1,5,9],[10,11,13],[12,13,15]], k = 8
// Output: 13
// Explanation: The elements in the matrix are [1,5,9,10,11,12,13,**13**,15], and the 8^th smallest number is 13
// ```
//
// **Example 2:**
//
// ```
// Input: matrix = [[-5]], k = 1
// Output: -5
// ```
//
// **Constraints:**
//
// - `n == matrix.length == matrix[i].length`
// - `1 <= n <= 300`
// - `-10^9 <= matrix[i][j] <= 10^9`
// - All the rows and columns of `matrix` are **guaranteed** to be sorted in **non-decreasing order**.
// - `1 <= k <= n^2`
//
// **Follow up:**
//
// - Could you solve the problem with a constant memory (i.e., `O(1)` memory complexity)?
// - Could you solve the problem in `O(n)` time complexity? The solution may be too advanced for an interview but you may find reading http://www.cse.yorku.ca/~andy/pubs/X+Y.pdf fun.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"github.com/emirpasic/gods/trees/binaryheap"
	"github.com/emirpasic/gods/utils"
)

// Heap
func kthSmallest(matrix [][]int, k int) int {
	heap := binaryheap.NewWith(func(a, b any) int { return -utils.IntComparator(a, b) })
	for _, row := range matrix {
		for _, v := range row {
			if heap.Size() == k {
				top, _ := heap.Peek()
				if v > top.(int) {
					continue
				}
				heap.Pop()
			}
			heap.Push(v)
		}
	}
	ans, _ := heap.Peek()
	return ans.(int)
}

// Binary search
func kthSmallest2(matrix [][]int, k int) int {
	n := len(matrix)

	check := func(x int) bool {
		sum, col := 0, n-1
		for _, row := range matrix {
			for ; col >= 0 && row[col] > x; col-- {
			}
			sum += col + 1
		}
		return sum < k
	}

	// check(lo-1) = true, check(lo=hi) = false
	lo, hi := matrix[0][0], matrix[n-1][n-1]
	for lo < hi {
		mid := lo + (hi-lo)/2
		if check(mid) {
			lo = mid + 1
		} else {
			hi = mid
		}
	}

	return lo
}
