// Source: https://leetcode.com/problems/divide-nodes-into-the-maximum-number-of-groups
// Title: Divide Nodes Into the Maximum Number of Groups
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a positive integer `n` representing the number of nodes in an **undirected** graph. The nodes are labeled from `1` to `n`.
//
// You are also given a 2D integer array `edges`, where `edges[i] = [a_i, b_i]` indicates that there is a **bidirectional** edge between nodes `a_i` and `b_i`. **Notice** that the given graph may be disconnected.
//
// Divide the nodes of the graph into `m` groups (**1-indexed**) such that:
//
// - Each node in the graph belongs to exactly one group.
// - For every pair of nodes in the graph that are connected by an edge `[a_i, b_i]`, if `a_i` belongs to the group with index `x`, and `b_i` belongs to the group with index `y`, then `|y - x| = 1`.
//
// Return the maximum number of groups (i.e., maximum `m`) into which you can divide the nodes. Return `-1` if it is impossible to group the nodes with the given conditions.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2022/10/13/example1.png
//
// ```
// Input: n = 6, edges = [[1,2],[1,4],[1,5],[2,6],[2,3],[4,6]]
// Output: 4
// Explanation: As shown in the image we:
// - Add node 5 to the first group.
// - Add node 1 to the second group.
// - Add nodes 2 and 4 to the third group.
// - Add nodes 3 and 6 to the fourth group.
// We can see that every edge is satisfied.
// It can be shown that that if we create a fifth group and move any node from the third or fourth group to it, at least on of the edges will not be satisfied.
// ```
//
// **Example 2:**
//
// ```
// Input: n = 3, edges = [[1,2],[2,3],[3,1]]
// Output: -1
// Explanation: If we add node 1 to the first group, node 2 to the second group, and node 3 to the third group to satisfy the first two edges, we can see that the third edge will not be satisfied.
// It can be shown that no grouping is possible.
// ```
//
// **Constraints:**
//
// - `1 <= n <= 500`
// - `1 <= edges.length <= 10^4`
// - `edges[i].length == 2`
// - `1 <= a_i, b_i <= n`
// - `a_i != b_i`
// - There is at most one edge between any pair of vertices.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// The problem is solvable iff it is bipartite
// If the graph is disconnected, we can solve the problem indenpently and sum the results.
// For connected graph, the maximum number of the groups if equal to the diameter
func magnificentSets(n int, edges [][]int) int {
	// Prepare the graph
	graph := make([][]int, n)
	for _, edge := range edges {
		a, b := edge[0]-1, edge[1]-1
		graph[a] = append(graph[a], b)
		graph[b] = append(graph[b], a)
	}

	// Bipartite
	part := make([]int, n) // connected component index
	numPart := 0

	isBipartite := func() bool {
		visited := make([]bool, n)
		color := make([]bool, n)

		// DFS
		var dfs func(int, bool) bool
		dfs = func(a int, col bool) bool {
			if visited[a] {
				return color[a] == col
			}

			visited[a] = true
			color[a] = col
			part[a] = numPart
			for _, b := range graph[a] {
				if !dfs(b, !col) {
					return false
				}
			}

			return true
		}

		// Loop
		for a := range n {
			if visited[a] {
				continue
			}
			if !dfs(a, false) {
				return false
			}
			numPart++
		}
		return true
	}
	if !isBipartite() {
		return -1
	}

	// Depth
	getDepth := func(src int) int {
		visited := make([]bool, n)

		// BFS
		depth := 0
		curr := []int{src}

		for len(curr) > 0 {
			next := make([]int, 0, n)
			for _, a := range curr {
				if visited[a] {
					continue
				}
				visited[a] = true
				for _, b := range graph[a] {
					if visited[b] {
						continue
					}
					next = append(next, b)
				}
			}

			curr = next
			depth++
		}

		return depth
	}

	// Diameter
	diameters := make([]int, numPart)
	for a := range n {
		diameters[part[a]] = max(diameters[part[a]], getDepth(a))
	}

	res := 0
	for _, diameter := range diameters {
		res += diameter
	}

	return res
}
