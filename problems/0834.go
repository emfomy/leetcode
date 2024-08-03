// Source: https://leetcode.com/problems/sum-of-distances-in-tree
// Title: Sum of Distances in Tree
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There is an undirected connected tree with n nodes labeled from 0 to n-1 and n-1 edges.
// You are given the integer n and the array edges where edges[i] = [a_i, b_i] indicates that there is an edge between nodes a_i and b_i in the tree.
// Return an array answer of length n where answer[i] is the sum of the distances between the ith node in the tree and all other nodes.
//
// Example 1:
//
//   https://assets.leetcode.com/uploads/2021/07/23/lc-sumdist1.jpg
//
//   Input: n = 6, edges = [[0,1],[0,2],[2,3],[2,4],[2,5]]
//   Output: [8,12,6,10,10,10]
//   Explanation:
//     The tree is shown above.
//     We can see that dist(0,1) + dist(0,2) + dist(0,3) + dist(0,4) + dist(0,5)
//     equals 1 + 1 + 2 + 2 + 2 = 8.
//     Hence, answer[0] = 8, and so on.
//
// Example 2:
//
//   https://assets.leetcode.com/uploads/2021/07/23/lc-sumdist2.jpg
//
//   Input: n = 1, edges = []
//   Output: [0]
//
// Example 3:
//
//   https://assets.leetcode.com/uploads/2021/07/23/lc-sumdist3.jpg
//
//   Input: n = 2, edges = [[1,0]]
//   Output: [1,1]
//
// Constraints:
//
//   1 <= n <= 3 * 10^4
//   edges.length == n-1
//   edges[i].length == 2
//   0 <= a_i, b_i < n
//   a_i != b_i
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// Step 1:
//
//	Apply reverse traversal to calculate the distance sum for child edges of each node.
//	Also track the number of descendants of each node.
//
// Step 2:
//
//	Apply traversal to calculate the distance sum for parent edge of each node.
func sumOfDistancesInTree(n int, edges [][]int) []int {
	node_dist := make([]int, n)
	node_count := make([]int, n)

	edge_dist := make([][]int, n)
	for i := 0; i < n; i++ {
		edge_dist[i] = make([]int, n)
	}
	edge_count := make([][]int, n)
	for i := 0; i < n; i++ {
		edge_count[i] = make([]int, n)
	}

	// Prepare graph
	graph := make([][]int, n)
	for i := 0; i < n; i++ {
		graph[i] = make([]int, 0)
	}

	for _, edge := range edges {
		a, b := edge[0], edge[1]
		graph[a] = append(graph[a], b)
		graph[b] = append(graph[b], a)
	}

	// Step 1: Reverse Traversal
	var dfs1 = func(parent, a int) {}
	dfs1 = func(parent, a int) {
		for _, b := range graph[a] {
			if b == parent {
				continue
			}

			dfs1(a, b)

			edge_dist[a][b] = node_dist[b] + node_count[b] + 1
			edge_count[a][b] = node_count[b] + 1
			node_dist[a] += edge_dist[a][b]
			node_count[a] += edge_count[a][b]
		}
	}

	dfs1(-1, 0)

	// Step 2: Traversal
	var dfs2 = func(parent, a int) {}
	dfs2 = func(parent, a int) {
		for _, b := range graph[a] {
			if b == parent {
				continue
			}

			_dist := node_dist[a] - edge_dist[a][b]
			_count := node_count[a] - edge_count[a][b]
			edge_dist[b][a] = _dist + _count + 1
			edge_count[b][a] = _count + 1
			node_dist[b] += edge_dist[b][a]
			node_count[b] += edge_count[b][a]

			dfs2(a, b)
		}
	}

	dfs2(-1, 0)

	return node_dist
}

// Same as above, but remove all edge data.
// In step 2, after moving through the edge,
// the total distance is recuded by the number of descendants of the child node,
// and is increased by the number of the other nodes.
func sumOfDistancesInTree2(n int, edges [][]int) []int {
	node_dist := make([]int, n)
	node_count := make([]int, n)
	for i := 0; i < n; i++ {
		node_count[i] = 1
	}

	// Prepare graph
	graph := make([][]int, n)
	for i := 0; i < n; i++ {
		graph[i] = make([]int, 0)
	}

	for _, edge := range edges {
		a, b := edge[0], edge[1]
		graph[a] = append(graph[a], b)
		graph[b] = append(graph[b], a)
	}

	// Step 1: Reverse Traversal
	var dfs1 = func(parent, a int) {}
	dfs1 = func(parent, a int) {
		for _, b := range graph[a] {
			if b == parent {
				continue
			}
			dfs1(a, b)
			node_dist[a] += node_dist[b] + node_count[b]
			node_count[a] += node_count[b]
		}
	}

	dfs1(-1, 0)

	// Step 2: Traversal
	var dfs2 = func(parent, a int) {}
	dfs2 = func(parent, a int) {
		for _, b := range graph[a] {
			if b == parent {
				continue
			}
			node_dist[b] = node_dist[a] - node_count[b] + (n - node_count[b])
			dfs2(a, b)
		}
	}

	dfs2(-1, 0)

	return node_dist
}
