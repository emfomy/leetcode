// Source: https://leetcode.com/problems/maximize-the-number-of-target-nodes-after-connecting-trees-i
// Title: Maximize the Number of Target Nodes After Connecting Trees I
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There exist two **undirected **trees with `n` and `m` nodes, with **distinct** labels in ranges `[0, n - 1]` and `[0, m - 1]`, respectively.
//
// You are given two 2D integer arrays `edges1` and `edges2` of lengths `n - 1` and `m - 1`, respectively, where `edges1[i] = [a_i, b_i]` indicates that there is an edge between nodes `a_i` and `b_i` in the first tree and `edges2[i] = [u_i, v_i]` indicates that there is an edge between nodes `u_i` and `v_i` in the second tree. You are also given an integer `k`.
//
// Node `u` is **target** to node `v` if the number of edges on the path from `u` to `v` is less than or equal to `k`. **Note** that a node is always **target** to itself.
//
// Return an array of `n` integers `answer`, where `answer[i]` is the **maximum** possible number of nodes **target** to node `i` of the first tree if you have to connect one node from the first tree to another node in the second tree.
//
// **Note** that queries are independent from each other. That is, for every query you will remove the added edge before proceeding to the next query.
//
// **Example 1:**
//
// ```
// Input: edges1 = [[0,1],[0,2],[2,3],[2,4]], edges2 = [[0,1],[0,2],[0,3],[2,7],[1,4],[4,5],[4,6]], k = 2
// Output: [9,7,9,8,8]
// Explanation:
// - For `i = 0`, connect node 0 from the first tree to node 0 from the second tree.
// - For `i = 1`, connect node 1 from the first tree to node 0 from the second tree.
// - For `i = 2`, connect node 2 from the first tree to node 4 from the second tree.
// - For `i = 3`, connect node 3 from the first tree to node 4 from the second tree.
// - For `i = 4`, connect node 4 from the first tree to node 4 from the second tree.
// https://assets.leetcode.com/uploads/2024/09/24/3982-1.png
// ```
//
// **Example 2:**
//
// ```
// Input: edges1 = [[0,1],[0,2],[0,3],[0,4]], edges2 = [[0,1],[1,2],[2,3]], k = 1
// Output: [6,3,3,3,3]
// Explanation:
// For every `i`, connect node `i` of the first tree with any node of the second tree.
// https://assets.leetcode.com/uploads/2024/09/24/3928-2.png
// ```
//
// **Constraints:**
//
// - `2 <= n, m <= 1000`
// - `edges1.length == n - 1`
// - `edges2.length == m - 1`
// - `edges1[i].length == edges2[i].length == 2`
// - `edges1[i] = [a_i, b_i]`
// - `0 <= a_i, b_i < n`
// - `edges2[i] = [u_i, v_i]`
// - `0 <= u_i, v_i < m`
// - The input is generated such that `edges1` and `edges2` represent valid trees.
// - `0 <= k <= 1000`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// For each node `i` in tree1,
// it is always better to connect from `i` to the tree2.
//
// We first find the maximum number of target in tree2.
func maxTargetNodes(edges1 [][]int, edges2 [][]int, k int) []int {
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
	var dfs func(graph [][]int, curr int, prev int, depth int) int
	dfs = func(graph [][]int, curr int, prev int, depth int) int {
		if depth > k {
			return 0
		}

		count := 1
		for _, next := range graph[curr] {
			if next != prev {
				count += dfs(graph, next, curr, depth+1)
			}
		}
		return count
	}

	// Count target in tree2
	target2 := 0
	for i := range m {
		target2 = max(target2, dfs(graph2, i, -1, 1))
	}

	// Count target in tree1
	ans := make([]int, n)
	for i := range n {
		ans[i] = target2 + dfs(graph1, i, -1, 0)
	}

	return ans
}
