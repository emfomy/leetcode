// Source: https://leetcode.com/problems/number-of-ways-to-arrive-at-destination
// Title: Number of Ways to Arrive at Destination
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are in a city that consists of `n` intersections numbered from `0` to `n - 1` with **bi-directional** roads between some intersections. The inputs are generated such that you can reach any intersection from any other intersection and that there is at most one road between any two intersections.
//
// You are given an integer `n` and a 2D integer array `roads` where `roads[i] = [u_i, v_i, time_i]` means that there is a road between intersections `u_i` and `v_i` that takes `time_i` minutes to travel. You want to know in how many ways you can travel from intersection `0` to intersection `n - 1` in the **shortest amount of time**.
//
// Return the **number of ways** you can arrive at your destination in the **shortest amount of time**. Since the answer may be large, return it **modulo** `10^9 + 7`.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2025/02/14/1976_corrected.png
//
// ```
// Input: n = 7, roads = [[0,6,7],[0,1,2],[1,2,3],[1,3,3],[6,3,3],[3,5,1],[6,5,1],[2,5,1],[0,4,5],[4,6,2]]
// Output: 4
// Explanation: The shortest amount of time it takes to go from intersection 0 to intersection 6 is 7 minutes.
// The four ways to get there in 7 minutes are:
// - 0 ➝ 6
// - 0 ➝ 4 ➝ 6
// - 0 ➝ 1 ➝ 2 ➝ 5 ➝ 6
// - 0 ➝ 1 ➝ 3 ➝ 5 ➝ 6
// ```
//
// **Example 2:**
//
// ```
// Input: n = 2, roads = [[1,0,10]]
// Output: 1
// Explanation: There is only one way to go from intersection 0 to intersection 1, and it takes 10 minutes.
// ```
//
// **Constraints:**
//
// - `1 <= n <= 200`
// - `n - 1 <= roads.length <= n * (n - 1) / 2`
// - `roads[i].length == 3`
// - `0 <= u_i, v_i <= n - 1`
// - `1 <= time_i <= 10^9`
// - `u_i != v_i`
// - There is at most one road connecting any two intersections.
// - You can reach any intersection from any other intersection.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"container/heap"
	"math"
)

const modulo = int(1e9 + 7)

// Use Dijkstra Algorithm + Min Heap
func countPaths(n int, roads [][]int) int {
	graph := make([][]roadType, n)
	for _, road := range roads {
		u, v, w := road[0], road[1], road[2]
		graph[u] = append(graph[u], roadType{to: v, time: w})
		graph[v] = append(graph[v], roadType{to: u, time: w})
	}

	h := newRoadHeap(len(roads))
	minTime := make([]int, n)
	count := make([]int, n)
	for i := range n {
		minTime[i] = math.MaxInt
	}

	// Start
	minTime[0] = 0
	count[0] = 1
	heap.Push(h, roadType{to: 0, time: 0})

	// Loop
	for h.Len() > 0 {
		curr := heap.Pop(h).(roadType)
		if curr.time > minTime[n-1] { // finished
			break
		}
		if curr.time > minTime[curr.to] { // outdated road
			continue
		}

		for _, next := range graph[curr.to] {
			next.time += curr.time
			if next.time < minTime[next.to] { // found shorter path
				minTime[next.to] = next.time
				count[next.to] = count[curr.to]
				heap.Push(h, next)
			} else if next.time == minTime[next.to] { // found same-length path
				count[next.to] = (count[next.to] + count[curr.to]) % modulo
			}
		}
	}

	return count[n-1]
}

type roadType struct {
	to   int
	time int
}

type roadHeap []roadType

func (h roadHeap) Len() int           { return len(h) }
func (h roadHeap) Less(i, j int) bool { return h[i].time < h[j].time } // min-heap
func (h roadHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }

func newRoadHeap(n int) *roadHeap {
	h := make(roadHeap, 0, n)
	heap.Init(&h)
	return &h
}

func (h *roadHeap) Push(x interface{}) {
	*h = append(*h, x.(roadType))
}

func (h *roadHeap) Pop() interface{} {
	n := len(*h)
	x := (*h)[n-1]
	*h = (*h)[:n-1]
	return x
}
