// Source: https://leetcode.com/problems/find-minimum-diameter-after-merging-two-trees
// Title: Find Minimum Diameter After Merging Two Trees
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There exist two **undirected ** trees with `n` and `m` nodes, numbered from `0` to `n - 1` and from `0` to `m - 1`, respectively. You are given two 2D integer arrays `edges1` and `edges2` of lengths `n - 1` and `m - 1`, respectively, where `edges1[i] = [a_i, b_i]` indicates that there is an edge between nodes `a_i` and `b_i` in the first tree and `edges2[i] = [u_i, v_i]` indicates that there is an edge between nodes `u_i` and `v_i` in the second tree.
//
// You must connect one node from the first tree with another node from the second tree with an edge.
//
// Return the **minimum** possible **diameter** of the resulting tree.
//
// The **diameter** of a tree is the length of the longest path between any two nodes in the tree.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2024/04/22/example11-transformed.png
//
// Input: edges1 = [[0,1],[0,2],[0,3]], edges2 = [[0,1]]
//
// Output: 3
//
// Explanation:
//
// We can obtain a tree of diameter 3 by connecting node 0 from the first tree with any node from the second tree.
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2024/04/22/example211.png
//
// Input: edges1 = [[0,1],[0,2],[0,3],[2,4],[2,5],[3,6],[2,7]], edges2 = [[0,1],[0,2],[0,3],[2,4],[2,5],[3,6],[2,7]]
//
// Output: 5
//
// Explanation:
//
// We can obtain a tree of diameter 5 by connecting node 0 from the first tree with node 0 from the second tree.
//
// **Constraints:**
//
// - `1 <= n, m <= 10^5`
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

// Result = ceil(diameter1 / 2) + ceil(diameter2 / 2) + 1
func minimumDiameterAfterMerge(edges1 [][]int, edges2 [][]int) int {
	graph1 := _newGraph(edges1)
	diameter1 := _diameter(graph1)

	graph2 := _newGraph(edges2)
	diameter2 := _diameter(graph2)

	newDismater := ((diameter1 + 1) / 2) + ((diameter2 + 1) / 2) + 1

	return max(newDismater, diameter1, diameter2)
}

// Compute diameter
// Pick a random node p.
// Find the farthest point a from p.
// Then find the farthest point b from a.
// dist(a, b) is the diameter.
//
// Prove:
// https://codeforces.com/blog/entry/101271
func _diameter(graph [][]int) int {
	a, _ := _maxDistance(graph, 0, -1)
	_, dist := _maxDistance(graph, a, -1)
	return dist
}

func _maxDistance(graph [][]int, node int, from int) (int, int) {
	maxNode, maxDist := node, 0
	for _, next := range graph[node] {
		if next == from {
			continue
		}
		if leafNode, leafDist := _maxDistance(graph, next, node); leafDist >= maxDist {
			maxNode = leafNode
			maxDist = leafDist + 1
		}
	}
	return maxNode, maxDist
}

func _newGraph(edges [][]int) [][]int {
	n := len(edges) + 1
	graph := make([][]int, n)

	for _, edge := range edges {
		x, y := edge[0], edge[1]
		graph[x] = append(graph[x], y)
		graph[y] = append(graph[y], x)
	}

	return graph
}
