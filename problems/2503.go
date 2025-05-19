// Source: https://leetcode.com/problems/maximum-number-of-points-from-grid-queries
// Title: Maximum Number of Points From Grid Queries
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an `m x n` integer matrix `grid` and an array `queries` of size `k`.
//
// Find an array `answer` of size `k` such that for each integer `queries[i]` you start in the **top left** cell of the matrix and repeat the following process:
//
// - If `queries[i]` is **strictly** greater than the value of the current cell that you are in, then you get one point if it is your first time visiting this cell, and you can move to any **adjacent** cell in all `4` directions: up, down, left, and right.
// - Otherwise, you do not get any points, and you end this process.
//
// After the process, `answer[i]` is the **maximum** number of points you can get. **Note** that for each query you are allowed to visit the same cell **multiple** times.
//
// Return the resulting array `answer`.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2025/03/15/image1.png
//
// ```
// Input: grid = [[1,2,3],[2,5,7],[3,5,1]], queries = [5,6,2]
// Output: [5,8,1]
// Explanation: The diagrams above show which cells we visit to get points for each query.```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2022/10/20/yetgriddrawio-2.png
//
// ```
// Input: grid = [[5,2,1],[1,1,2]], queries = [3]
// Output: [0]
// Explanation: We can not get any points because the value of the top left cell is already greater than or equal to 3.
// ```
//
// **Constraints:**
//
// - `m == grid.length`
// - `n == grid[i].length`
// - `2 <= m, n <= 1000`
// - `4 <= m * n <= 10^5`
// - `k == queries.length`
// - `1 <= k <= 10^4`
// - `1 <= grid[i][j], queries[i] <= 10^6`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"container/heap"
	"fmt"
	"slices"
)

// Use BFS + Heap
func maxPoints(grid [][]int, queries []int) []int {
	m, n := len(grid), len(grid[0])
	q := len(queries)
	res := make([]int, q)

	dirs := [][2]int{
		{-1, 0},
		{1, 0},
		{0, -1},
		{0, 1},
	}

	// Sort queries
	idxs := make([]int, q)
	for k := range q {
		idxs[k] = k
	}
	slices.SortFunc(idxs, func(a, b int) int {
		return queries[a] - queries[b]
	})

	// BFS
	visited := make([][]bool, m)
	for i := range m {
		visited[i] = make([]bool, n)
	}

	h := newNodeHeap(m * n)
	heap.Push(h, nodeType{x: 0, y: 0, val: grid[0][0]})
	visited[0][0] = true

	count := 0
	for i := range q {
		idx := idxs[i]
		query := queries[idx]

		for h.Len() > 0 && (*h)[0].val < query {
			curr := heap.Pop(h).(nodeType)
			x, y := curr.x, curr.y
			count++

			for _, dir := range dirs {
				xx, yy := x+dir[0], y+dir[1]
				if xx < 0 || xx >= m || yy < 0 || yy >= n {
					continue
				}
				if visited[xx][yy] {
					continue
				}
				visited[xx][yy] = true
				heap.Push(h, nodeType{x: xx, y: yy, val: grid[xx][yy]})
			}
		}
		res[idx] = count
	}

	return res
}

type nodeType struct {
	x   int
	y   int
	val int
}

type nodeHeap []nodeType

func (h nodeHeap) Len() int           { return len(h) }
func (h nodeHeap) Less(i, j int) bool { return h[i].val < h[j].val } // min-heap
func (h nodeHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }

func newNodeHeap(mn int) *nodeHeap {
	h := make(nodeHeap, 0, mn)
	heap.Init(&h)
	return &h
}

func (h *nodeHeap) Push(x interface{}) {
	*h = append(*h, x.(nodeType))
}

func (h *nodeHeap) Pop() interface{} {
	n := len(*h)
	x := (*h)[n-1]
	*h = (*h)[:n-1]
	return x
}

func main() {
	fmt.Println(maxPoints(
		[][]int{
			{123491, 95183, 131119, 576084, 779700, 886039, 564610},
			{835246, 594630, 752204, 976312, 431928, 916878, 37773},
			{602559, 675, 8018, 72760, 560850, 132858, 416126},
			{787316, 77587, 784798, 797907, 769783, 143785, 378185},
			{362862, 754648, 212843, 813454, 552332, 10700, 266493},
			{970387, 690405, 956929, 172955, 952240, 156111, 403784},
			{916537, 511212, 795823, 716447, 470772, 943050, 542971},
			{449416, 742776, 952272, 447280, 190229, 354861, 256967},
			{682983, 738563, 29191, 379588, 802026, 480129, 88803},
			{200621, 935415, 758897, 430413, 947532, 642396, 281230},
			{11009, 169593, 224388, 165812, 668820, 197039, 370824},
			{69652, 613219, 858695, 278982, 688142, 592221, 573682},
			{169510, 983952, 45500, 536012, 460040, 22352, 30370},
			{80353, 162875, 946697, 861329, 680011, 716224, 528454},
			{752578, 92518, 914849, 76979, 957241, 215103, 428977},
			{882979, 485485, 371229, 191577, 428367, 22769, 668112},
		},
		[]int{
			581002, 174698,
		},
	))
}
