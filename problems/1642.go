// Source: https://leetcode.com/problems/furthest-building-you-can-reach
// Title: Furthest Building You Can Reach
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array heights representing the heights of buildings, some bricks, and some ladders.
//
// You start your journey from building 0 and move to the next building by possibly using bricks or ladders.
//
// While moving from building i to building i+1 (0-indexed),
//
//   If the current building's height is greater than or equal to the next building's height, you do not need a ladder or bricks.
//   If the current building's height is less than the next building's height, you can either use one ladder or (h[i+1] - h[i]) bricks.
//
// Return the furthest building index (0-indexed) you can reach if you use the given ladders and bricks optimally.
//
// Example 1:
//
//   https://assets.leetcode.com/uploads/2020/10/27/q4.gif
//
//   Input: heights = [4,2,7,6,9,14,12], bricks = 5, ladders = 1
//   Output: 4
//   Explanation:
//     Starting at building 0, you can follow these steps:
//       Go to building 1 without using ladders nor bricks since 4 >= 2.
//       Go to building 2 using 5 bricks. You must use either bricks or ladders because 2 < 7.
//       Go to building 3 without using ladders nor bricks since 7 >= 6.
//       Go to building 4 using your only ladder. You must use either bricks or ladders because 6 < 9.
//     It is impossible to go beyond building 4 because you do not have any more bricks or ladders.
//
// Example 2:
//
//   Input: heights = [4,12,2,7,3,18,20,3,19], bricks = 10, ladders = 2
//   Output: 7
//
// Example 3:
//
//   Input: heights = [14,3,19,3], bricks = 17, ladders = 0
//   Output: 3
//
// Constraints:
//
//   1 <= heights.length <= 10^5
//   1 <= heights[i] <= 10^6
//   0 <= bricks <= 10^9
//   0 <= ladders <= heights.length
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

func furthestBuilding(heights []int, bricks int, ladders int) int {
	n := len(heights)
	usedBricks := newIntHeap(make([]int, 0, n))

	for i := 0; i < n-1; i++ {
		diff := heights[i+1] - heights[i]

		if diff < 0 { // Just jump
			continue
		}

		heap.Push(usedBricks, diff)
		bricks -= diff

		if bricks >= 0 { // Use brick
			continue
		}

		if ladders > 0 { // Use ladder
			ladders--
			bricks += heap.Pop(usedBricks).(int)
		}

		if bricks < 0 {
			return i
		}
	}

	return n - 1
}
