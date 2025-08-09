// Source: https://leetcode.com/problems/minimum-score-after-removals-on-a-tree
// Title: Minimum Score After Removals on a Tree
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There is an undirected connected tree with `n` nodes labeled from `0` to `n - 1` and `n - 1` edges.
//
// You are given a **0-indexed** integer array `nums` of length `n` where `nums[i]` represents the value of the `i^th` node. You are also given a 2D integer array `edges` of length `n - 1` where `edges[i] = [a_i, b_i]` indicates that there is an edge between nodes `a_i` and `b_i` in the tree.
//
// Remove two **distinct** edges of the tree to form three connected components. For a pair of removed edges, the following steps are defined:
//
// - Get the XOR of all the values of the nodes for **each** of the three components respectively.
// - The **difference** between the **largest** XOR value and the **smallest** XOR value is the **score** of the pair.
//
// - For example, say the three components have the node values: `[4,5,7]`, `[1,9]`, and `[3,3,3]`. The three XOR values are `4 ^ 5 ^ 7 = **6**`, `1 ^ 9 = **8**`, and `3 ^ 3 ^ 3 = **3**`. The largest XOR value is `8` and the smallest XOR value is `3`. The score is then `8 - 3 = 5`.
//
// Return the **minimum** score of any possible pair of edge removals on the given tree.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2022/05/03/ex1drawio.png
//
// ```
// Input: nums = [1,5,5,4,11], edges = [[0,1],[1,2],[1,3],[3,4]]
// Output: 9
// Explanation: The diagram above shows a way to make a pair of removals.
// - The 1^st component has nodes [1,3,4] with values [5,4,11]. Its XOR value is 5 ^ 4 ^ 11 = 10.
// - The 2^nd component has node [0] with value [1]. Its XOR value is 1 = 1.
// - The 3^rd component has node [2] with value [5]. Its XOR value is 5 = 5.
// The score is the difference between the largest and smallest XOR value which is 10 - 1 = 9.
// It can be shown that no other pair of removals will obtain a smaller score than 9.
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2022/05/03/ex2drawio.png
//
// ```
// Input: nums = [5,5,2,4,4,2], edges = [[0,1],[1,2],[5,2],[4,3],[1,3]]
// Output: 0
// Explanation: The diagram above shows a way to make a pair of removals.
// - The 1^st component has nodes [3,4] with values [4,4]. Its XOR value is 4 ^ 4 = 0.
// - The 2^nd component has nodes [1,0] with values [5,5]. Its XOR value is 5 ^ 5 = 0.
// - The 3^rd component has nodes [2,5] with values [2,2]. Its XOR value is 2 ^ 2 = 0.
// The score is the difference between the largest and smallest XOR value which is 0 - 0 = 0.
// We cannot obtain a smaller score than 0.
// ```
//
// **Constraints:**
//
// - `n == nums.length`
// - `3 <= n <= 1000`
// - `1 <= nums[i] <= 10^8`
// - `edges.length == n - 1`
// - `edges[i].length == 2`
// - `0 <= a_i, b_i < n`
// - `a_i != b_i`
// - `edges` represents a valid tree.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"math"
)

// Use DFS to compute XOR for each subtree.
// Denote V(x) to be the value of a subtree rooted at x.
//
// Loop through all edge pair (e1, e2).
// We use lower node id to represent the edges.
//
// If e1 is an ancestor of e2, then the three parts are
// V(0) ^ V(e1), V(e1) ^ V(e2), V(e2).
//
// If e2 is an ancestor of e1, then the three parts are
// V(0) ^ V(e2), V(e2) ^ V(e1), V(e1).
//
// Otherwise, then the three parts are
// V(0) ^ V(e1) ^ V(e1), V(e1), V(e2).
func minimumScore(nums []int, edges [][]int) int {
	n := len(nums)

	// Graph
	graph := make(map[int][]int, n)
	for _, edge := range edges {
		a, b := edge[0], edge[1]
		graph[a] = append(graph[a], b)
		graph[b] = append(graph[b], a)
	}

	// DFS Subtree XOR
	scores := make([]int, n)
	ins := make([]int, n)
	outs := make([]int, n)

	cnt := 0
	var dfs func(root int, parent int)
	dfs = func(root int, parent int) {
		cnt++
		ins[root] = cnt
		scores[root] = nums[root]

		for _, sub := range graph[root] {
			if sub != parent {
				dfs(sub, root)
				scores[root] ^= scores[sub]
			}
		}

		cnt++
		outs[root] = cnt
	}
	dfs(0, -1)

	// Ancestor check
	isAncestor := func(u, v int) bool {
		return ins[u] < ins[v] && outs[u] > outs[v]
	}

	// Score
	getScore := func(part1, part2, part3 int) int {
		return max(part1, part2, part3) - min(part1, part2, part3)
	}

	// Loop
	ans := math.MaxInt
	for i := 1; i < n; i++ {
		for j := i + 1; j < n; j++ {
			var score int
			if isAncestor(i, j) {
				score = getScore(scores[0]^scores[i], scores[i]^scores[j], scores[j])
			} else if isAncestor(j, i) {
				score = getScore(scores[0]^scores[j], scores[j]^scores[i], scores[i])
			} else {
				score = getScore(scores[0]^scores[i]^scores[j], scores[i], scores[j])
			}
			ans = min(ans, score)
		}
	}

	return ans
}
