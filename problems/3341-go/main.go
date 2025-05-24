// Source: https://leetcode.com/problems/find-minimum-time-to-reach-last-room-i
// Title: Find Minimum Time to Reach Last Room I
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There is a dungeon with `n x m`` rooms arranged as a grid.
//
// You are given a 2D array `moveTime`` of size `n x m``, where `moveTime[i][j]`` represents the **minimum** time in seconds when you can **start moving** to that room. You start from the room `(0, 0)`` at time `t = 0`` and can move to an **adjacent** room. Moving between adjacent rooms takes exactly one second.
//
// Return the **minimum** time to reach the room `(n - 1, m - 1)``.
//
// Two rooms are **adjacent** if they share a common wall, either horizontally or vertically.
//
// **Example 1:**
//
// ```
// Input: moveTime = [[0,4],[4,4]]
// Output: 6
// Explanation:
// The minimum time required is 6 seconds.
// - At time `t == 4``, move from room `(0, 0)`` to room `(1, 0)`` in one second.
// - At time `t == 5``, move from room `(1, 0)`` to room `(1, 1)`` in one second.
// ````
//
// **Example 2:**
//
// ```
// Input: moveTime = [[0,0,0],[0,0,0]]
// Output: 3
// Explanation:
// The minimum time required is 3 seconds.
// - At time `t == 0``, move from room `(0, 0)`` to room `(1, 0)`` in one second.
// - At time `t == 1``, move from room `(1, 0)`` to room `(1, 1)`` in one second.
// - At time `t == 2``, move from room `(1, 1)`` to room `(1, 2)`` in one second.
// ```
//
// **Example 3:**
//
// ```
// Input: moveTime = [[0,1],[1,2]]
// Output: 3
// ```
//
// **Constraints:**
//
// - `2 <= n == moveTime.length <= 50``
// - `2 <= m == moveTime[i].length <= 50``
// - `0 <= moveTime[i][j] <= 10^9``
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"container/heap"
)

type roomType struct {
	x int
	y int
	t int
}

type roomHeap []roomType

func (h roomHeap) Len() int           { return len(h) }
func (h roomHeap) Less(i, j int) bool { return h[i].t < h[j].t } // min-heap
func (h roomHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }

func newRoomHeap(n, m int) *roomHeap {
	h := make(roomHeap, 0, m*n)
	heap.Init(&h)
	return &h
}

func (h *roomHeap) Push(x interface{}) {
	*h = append(*h, x.(roomType))
}

func (h *roomHeap) Pop() interface{} {
	n := len(*h)
	x := (*h)[n-1]
	*h = (*h)[:n-1]
	return x
}

func minTimeToReach(moveTime [][]int) int {
	n, m := len(moveTime), len(moveTime[0])
	h := newRoomHeap(n, m)

	visited := make([][]bool, n)
	for i := range n {
		visited[i] = make([]bool, m)
	}

	// Run
	dirs := [][2]int{
		{1, 0},
		{0, 1},
		{-1, 0},
		{0, -1},
	}
	heap.Push(h, roomType{x: 0, y: 0, t: 0}) // start at (0, 0)
	for h.Len() > 0 {
		room := heap.Pop(h).(roomType)
		x, y, t := room.x, room.y, room.t

		if x == n-1 && y == m-1 {
			return t
		}

		if visited[x][y] {
			continue
		}
		visited[x][y] = true

		for _, dir := range dirs {
			x2, y2 := x+dir[0], y+dir[1]
			if 0 <= x2 && x2 < n && 0 <= y2 && y2 < m && !visited[x2][y2] {
				heap.Push(h, roomType{
					x: x2,
					y: y2,
					t: max(t, moveTime[x2][y2]) + 1,
				})
			}
		}
	}

	return -1
}
