// Source: https://leetcode.com/problems/redundant-connection
// Title: Redundant Connection
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// In this problem, a tree is an **undirected graph** that is connected and has no cycles.
//
// You are given a graph that started as a tree with `n` nodes labeled from `1` to `n`, with one additional edge added. The added edge has two **different** vertices chosen from `1` to `n`, and was not an edge that already existed. The graph is represented as an array `edges` of length `n` where `edges[i] = [a_i, b_i]` indicates that there is an edge between nodes `a_i` and `b_i` in the graph.
//
// Return an edge that can be removed so that the resulting graph is a tree of `n` nodes. If there are multiple answers, return the answer that occurs last in the input.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/05/02/reduntant1-1-graph.jpg
//
// ```
// Input: edges = [[1,2],[1,3],[2,3]]
// Output: [2,3]
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2021/05/02/reduntant1-2-graph.jpg
//
// ```
// Input: edges = [[1,2],[2,3],[3,4],[1,4],[1,5]]
// Output: [1,4]
// ```
//
// **Constraints:**
//
// - `n == edges.length`
// - `3 <= n <= 1000`
// - `edges[i].length == 2`
// - `1 <= a_i < b_i <= edges.length`
// - `a_i != b_i`
// - There are no repeated edges.
// - The given graph is connected.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// According the condition, there is only one cycle in this graph.
//
// We can use topological sort to find the cycle
func findRedundantConnection(edges [][]int) []int {
	n := len(edges)

	// Prepare the graph
	graph := make([]map[int]bool, n)
	for i := range n {
		graph[i] = make(map[int]bool)
	}
	for _, edge := range edges {
		a, b := edge[0], edge[1]
		graph[a-1][b] = true
		graph[b-1][a] = true
	}

	// Prepare the queue
	queue := make([]int, 0, n)
	for i := range n {
		if len(graph[i]) == 1 {
			queue = append(queue, i+1)
		}
	}

	// Loop through the queue
	for len(queue) > 0 {
		curr := queue[0]
		queue = queue[1:]

		for next := range graph[curr-1] {
			delete(graph[next-1], curr)
			if len(graph[next-1]) == 1 {
				queue = append(queue, next)
			}
		}
		graph[curr-1] = nil
	}

	for i := n - 1; i >= 0; i-- {
		edge := edges[i]
		a, b := edge[0], edge[1]
		if graph[a-1][b] {
			return []int{a, b}
		}
	}
	return nil
}

// According the condition, there is only one cycle in this graph.
//
// We can use union-find to find the cycle
// If we union two node with the same parent,
// That edge must form an edge (and is redundent).
func findRedundantConnection2(edges [][]int) []int {
	n := len(edges)

	// Initialize
	parent := make([]int, n+1)
	rank := make([]int, n+1)
	for i := range n + 1 {
		parent[i] = i
	}

	// Find
	var find func(int) int
	find = func(x int) int {
		if parent[x] != x {
			parent[x] = find(parent[x])
		}
		return parent[x]
	}

	// Union, return if the parent are the same
	var union func(int, int) bool
	union = func(x, y int) bool {
		x = find(x)
		y = find(y)

		if x == y {
			return true
		}

		if rank[x] > rank[y] {
			x, y = y, x
		}

		parent[y] = x
		if rank[x] == rank[y] {
			rank[x]++
		}
		return false
	}

	// Loop through the edges
	for _, edge := range edges {
		a, b := edge[0], edge[1]
		if union(a, b) {
			return edge
		}
	}

	return nil
}
