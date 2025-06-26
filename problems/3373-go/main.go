// Source: https://leetcode.com/problems/maximize-the-number-of-target-nodes-after-connecting-trees-ii
// Title: Maximize the Number of Target Nodes After Connecting Trees II
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There exist two **undirected **trees with `n` and `m` nodes, labeled from `[0, n - 1]` and `[0, m - 1]`, respectively.
//
// You are given two 2D integer arrays `edges1` and `edges2` of lengths `n - 1` and `m - 1`, respectively, where `edges1[i] = [a_i, b_i]` indicates that there is an edge between nodes `a_i` and `b_i` in the first tree and `edges2[i] = [u_i, v_i]` indicates that there is an edge between nodes `u_i` and `v_i` in the second tree.
//
// Node `u` is **target** to node `v` if the number of edges on the path from `u` to `v` is even.**Note** that a node is always **target** to itself.
//
// Return an array of `n` integers `answer`, where `answer[i]` is the **maximum** possible number of nodes that are **target** to node `i` of the first tree if you had to connect one node from the first tree to another node in the second tree.
//
// **Note** that queries are independent from each other. That is, for every query you will remove the added edge before proceeding to the next query.
//
// **Example 1:**
//
// ```
// Input: edges1 = [[0,1],[0,2],[2,3],[2,4]], edges2 = [[0,1],[0,2],[0,3],[2,7],[1,4],[4,5],[4,6]]
// Output: [8,7,7,8,8]
// Explanation:
// - For `i = 0`, connect node 0 from the first tree to node 0 from the second tree.
// - For `i = 1`, connect node 1 from the first tree to node 4 from the second tree.
// - For `i = 2`, connect node 2 from the first tree to node 7 from the second tree.
// - For `i = 3`, connect node 3 from the first tree to node 0 from the second tree.
// - For `i = 4`, connect node 4 from the first tree to node 4 from the second tree.
// https://assets.leetcode.com/uploads/2024/09/24/3982-1.png
// ```
//
// **Example 2:**
//
// ```
// Input: edges1 = [[0,1],[0,2],[0,3],[0,4]], edges2 = [[0,1],[1,2],[2,3]]
// Output: [3,6,6,6,6]
// Explanation:
// For every `i`, connect node `i` of the first tree with any node of the second tree.
// https://assets.leetcode.com/uploads/2024/09/24/3928-2.png
// ```
//
// **Constraints:**
//
// - `2 <= n, m <= 10^5`
// - `edges1.length == n - 1`
// - `edges2.length == m - 1`
// - `edges1[i].length == edges2[i].length == 2`
// - `edges1[i] = [a_i, b_i]`
// - `0 <= a_i, b_i < n`
// - `edges2[i] = [u_i, v_i]`
// - `0 <= u_i, v_i < m`
// - The input is generated such that `edges1` and `edges2` represent valid trees.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// TLE
//
// We first find the number of even/odd target in tree2.
//
// We can always connect to tree2 from node i and make odd targets in tree2 even targets.
// We can always connect to tree2 from a neighbor of node i and make even targets in tree2 even targets.
// Since n >= 2, such neighbor always exist.
func maxTargetNodes(edges1 [][]int, edges2 [][]int) []int {
	n := len(edges1) + 1
	m := len(edges2) + 1

	// Prepare graph
	graph1 := make([][]int, n)
	graph2 := make([][]int, m)
	for _, edge := range edges1 {
		u, v := edge[0], edge[1]
		graph1[u] = append(graph1[u], v)
		graph1[v] = append(graph1[v], u)
	}
	for _, edge := range edges2 {
		u, v := edge[0], edge[1]
		graph2[u] = append(graph2[u], v)
		graph2[v] = append(graph2[v], u)
	}

	// DFS for count target
	var dfs func(graph [][]int, curr int, prev int) (int, int)
	dfs = func(graph [][]int, curr int, prev int) (int, int) {
		even, odd := 1, 0
		for _, next := range graph[curr] {
			if next != prev {
				nextEven, nextOdd := dfs(graph, next, curr)
				even += nextOdd
				odd += nextEven
			}
		}
		return even, odd
	}

	// Count target in tree2
	even2, odd2 := 0, 0
	for i := range m {
		even, odd := dfs(graph2, i, -1)
		even2 = max(even2, even)
		odd2 = max(odd2, odd)
	}
	target2 := max(even2, odd2)

	// Count target in tree1
	ans := make([]int, n)
	for i := range n {
		even, _ := dfs(graph1, i, -1)
		ans[i] = even + target2
	}

	return ans
}

// We first find the number of even/odd target in tree2.
//
// We can always connect to tree2 from node i and make odd targets in tree2 even targets.
// We can always connect to tree2 from a neighbor of node i and make even targets in tree2 even targets.
// Since n >= 2, such neighbor always exist.
//
// Note that we only need to apply DFS once since the parity of a tree is fixed.
func maxTargetNodes2(edges1 [][]int, edges2 [][]int) []int {
	n := len(edges1) + 1
	m := len(edges2) + 1

	// Prepare graph
	graph1 := make([][]int, n)
	graph2 := make([][]int, m)
	for _, edge := range edges1 {
		u, v := edge[0], edge[1]
		graph1[u] = append(graph1[u], v)
		graph1[v] = append(graph1[v], u)
	}
	for _, edge := range edges2 {
		u, v := edge[0], edge[1]
		graph2[u] = append(graph2[u], v)
		graph2[v] = append(graph2[v], u)
	}

	// DFS for count target in tree1
	parity1 := make([]bool, n)
	var dfs1 func(graph [][]int, curr int, prev int, parity bool) (int, int)
	dfs1 = func(graph [][]int, curr int, prev int, parity bool) (int, int) {
		parity1[curr] = parity
		even, odd := 1, 0
		for _, next := range graph[curr] {
			if next != prev {
				nextEven, nextOdd := dfs1(graph, next, curr, !parity)
				even += nextOdd
				odd += nextEven
			}
		}
		return even, odd
	}

	// DFS for count target in tree2
	var dfs2 func(graph [][]int, curr int, prev int) (int, int)
	dfs2 = func(graph [][]int, curr int, prev int) (int, int) {
		even, odd := 1, 0
		for _, next := range graph[curr] {
			if next != prev {
				nextEven, nextOdd := dfs2(graph, next, curr)
				even += nextOdd
				odd += nextEven
			}
		}
		return even, odd
	}

	// Count target in tree2
	even2, odd2 := dfs2(graph2, 0, -1)
	target2 := max(even2, odd2)

	// Count target in tree1
	even1, odd1 := dfs1(graph1, 0, -1, true)
	ans := make([]int, n)
	for i := range n {
		if parity1[i] {
			ans[i] = even1 + target2
		} else {
			ans[i] = odd1 + target2
		}
	}

	return ans
}
