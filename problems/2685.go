// Source: https://leetcode.com/problems/count-the-number-of-complete-components
// Title: Count the Number of Complete Components
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer `n`. There is an **undirected** graph with `n` vertices, numbered from `0` to `n - 1`. You are given a 2D integer array `edges` where `edges[i] = [a_i, b_i]` denotes that there exists an **undirected** edge connecting vertices `a_i` and `b_i`.
//
// Return the number of **complete connected components** of the graph.
//
// A **connected component** is a subgraph of a graph in which there exists a path between any two vertices, and no vertex of the subgraph shares an edge with a vertex outside of the subgraph.
//
// A connected component is said to be **complete** if there exists an edge between every pair of its vertices.
//
// **Example 1:**
//
// https://assets.leetcode.com/uploads/2023/04/11/screenshot-from-2023-04-11-23-31-23.png
//
// ```
// Input: n = 6, edges = [[0,1],[0,2],[1,2],[3,4]]
// Output: 3
// Explanation: From the picture above, one can see that all of the components of this graph are complete.
// ```
//
// **Example 2:**
//
// https://assets.leetcode.com/uploads/2023/04/11/screenshot-from-2023-04-11-23-32-00.png
//
// ```
// Input: n = 6, edges = [[0,1],[0,2],[1,2],[3,4],[3,5]]
// Output: 1
// Explanation: The component containing vertices 0, 1, and 2 is complete since there is an edge between every pair of two vertices. On the other hand, the component containing vertices 3, 4, and 5 is not complete since there is no edge between vertices 4 and 5. Thus, the number of complete components in this graph is 1.
// ```
//
// **Constraints:**
//
// - `1 <= n <= 50`
// - `0 <= edges.length <= n * (n - 1) / 2`
// - `edges[i].length == 2`
// - `0 <= a_i, b_i <= n - 1`
// - `a_i != b_i`
// - There are no repeated edges.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// Use Union-Find to find the connected component
func countCompleteComponents(n int, edges [][]int) int {
	// Count degree
	degree := make([]int, n)
	for _, edge := range edges {
		degree[edge[0]]++
		degree[edge[1]]++
	}

	// Find connected component
	uf := newUnionFind(n)
	for _, edge := range edges {
		uf.union(edge[0], edge[1])
	}

	// Check degree is equal to size
	incomplete := make([]bool, n) // node x is incomplete
	for x := range n {
		p := uf.find(x)
		if x != p {
			incomplete[x] = true
		}
		if degree[x] != uf.size[p]-1 {
			incomplete[p] = true
		}
	}

	// Count result
	res := 0
	for x := range n {
		if !incomplete[x] {
			res++
		}
	}
	return res
}

type unionFind struct {
	parent []int
	size   []int
}

func newUnionFind(n int) *unionFind {
	parent := make([]int, n)
	size := make([]int, n)

	for i := range n {
		parent[i] = i
		size[i] = 1
	}

	return &unionFind{
		parent: parent,
		size:   size,
	}
}

func (uf *unionFind) find(x int) int {
	if uf.parent[x] != x {
		uf.parent[x] = uf.find(uf.parent[x])
	}
	return uf.parent[x]
}

func (uf *unionFind) union(x, y int) {
	x = uf.find(x)
	y = uf.find(y)
	if x == y {
		return
	}

	// Ensure size(x) >= size(y)
	if uf.size[x] < uf.size[y] {
		x, y = y, x
	}

	// Merge y into x
	uf.parent[y] = x
	uf.size[x] += uf.size[x]
}
