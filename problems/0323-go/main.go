// Source: https://leetcode.com/problems/number-of-connected-components-in-an-undirected-graph
// Title: Number of Connected Components in an Undirected Graph
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You have a graph of `n` nodes. You are given an integer `n` and an array `edges` where `edges[i] = [a_i, b_i]` indicates that there is an edge between `a_i` and `b_i` in the graph.
//
// Return the number of connected components in the graph.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/03/14/conn1-graph.jpg
//
// ```
// Input: n = 5, edges = [[0,1],[1,2],[3,4]]
// Output: 2
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2021/03/14/conn2-graph.jpg
//
// ```
// Input: n = 5, edges = [[0,1],[1,2],[2,3],[3,4]]
// Output: 1
// ```
//
// **Constraints:**
//
// - `1 <= n <= 2000`
// - `1 <= edges.length <= 5000`
// - `edges[i].length == 2`
// - `0 <= a_i <= b_i < n`
// - `a_i != b_i`
// - There are no repeated edges.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

type unionFind struct {
	parent []int
	rank   []int
	count  int // components
}

func newUnionFind(n int) *unionFind {
	parent := make([]int, n)
	rank := make([]int, n)

	for i := range n {
		parent[i] = i
	}

	return &unionFind{
		parent: parent,
		rank:   rank,
		count:  n,
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

	// Ensure rank(x) >= rank(y)
	if uf.rank[x] < uf.rank[y] {
		x, y = y, x
	}

	// Merge y into x
	uf.parent[y] = x
	if uf.rank[x] == uf.rank[y] {
		uf.rank[x]++
	}

	uf.count--
}

func countComponents(n int, edges [][]int) int {
	uf := newUnionFind(n)

	for _, edge := range edges {
		uf.union(edge[0], edge[1])
	}

	return uf.count
}
