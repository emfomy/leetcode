// Source: https://leetcode.com/problems/largest-color-value-in-a-directed-graph
// Title: Largest Color Value in a Directed Graph
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There is a **directed graph** of `n` colored nodes and `m` edges. The nodes are numbered from `0` to `n - 1`.
//
// You are given a string `colors` where `colors[i]` is a lowercase English letter representing the **color** of the `i^th` node in this graph (**0-indexed**). You are also given a 2D array `edges` where `edges[j] = [a_j, b_j]` indicates that there is a **directed edge** from node `a_j` to node `b_j`.
//
// A valid **path** in the graph is a sequence of nodes `x_1 -> x_2 -> x_3 -> ... -> x_k` such that there is a directed edge from `x_i` to `x_i+1` for every `1 <= i < k`. The **color value** of the path is the number of nodes that are colored the **most frequently** occurring color along that path.
//
// Return the **largest color value** of any valid path in the given graph, or `-1` if the graph contains a cycle.
//
// **Example 1:**
//
// https://assets.leetcode.com/uploads/2021/04/21/leet1.png
//
// ```
// Input: colors = "abaca", edges = [[0,1],[0,2],[2,3],[3,4]]
// Output: 3
// Explanation: The path 0 -> 2 -> 3 -> 4 contains 3 nodes that are colored `"a" (red in the above image)`.
// ```
//
// **Example 2:**
//
// https://assets.leetcode.com/uploads/2021/04/21/leet2.png
//
// ```
// Input: colors = "a", edges = [[0,0]]
// Output: -1
// Explanation: There is a cycle from 0 to 0.
// ```
//
// **Constraints:**
//
// - `n == colors.length`
// - `m == edges.length`
// - `1 <= n <= 10^5`
// - `0 <= m <= 10^5`
// - `colors` consists of lowercase English letters.
// - `0 <= a_j, b_j< n`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// Use topological sort to find cycle
// Use DP on each color
func largestPathValue(colors string, edges [][]int) int {
	n := len(colors)

	// Prepare the outMap
	// Count in-degrees
	outMap := make([][]int, n)
	inDegrees := make([]int, n)
	for _, edge := range edges {
		a, b := edge[0], edge[1]
		outMap[a] = append(outMap[a], b)
		inDegrees[b]++
	}

	// Prepare the queue
	queue := make([]int, 0, n)
	for node, degree := range inDegrees {
		if degree == 0 {
			queue = append(queue, node)
		}
	}

	// Topological sort
	order := make([]int, 0, n)
	for len(queue) > 0 {
		node := queue[0]
		queue = queue[1:]
		order = append(order, node)

		for _, out := range outMap[node] {
			inDegrees[out]--
			if inDegrees[out] == 0 {
				queue = append(queue, out)
			}
		}
	}

	// Check cycle
	if len(order) < n {
		return -1
	}

	// DP on each color
	dp := make([][26]int, n)
	ans := 0
	for _, node := range order {
		for color := range 26 {
			if int(colors[node]-'a') == color {
				dp[node][color]++
			}
			for _, out := range outMap[node] {
				dp[out][color] = max(dp[out][color], dp[node][color])
			}
			ans = max(ans, dp[node][color])
		}
	}

	return ans
}

// Use topological sort to find cycle
// Use DP on each color
//
// Run topological sort & DP together
func largestPathValue2(colors string, edges [][]int) int {
	n := len(colors)

	// Prepare the outMap
	// Count in-degrees
	outMap := make([][]int, n)
	inDegrees := make([]int, n)
	for _, edge := range edges {
		a, b := edge[0], edge[1]
		outMap[a] = append(outMap[a], b)
		inDegrees[b]++
	}

	// Prepare the queue
	queue := make([]int, 0, n)
	for node, degree := range inDegrees {
		if degree == 0 {
			queue = append(queue, node)
		}
	}

	// Topological sort + DP
	dp := make([][26]int, n)
	ans := 0
	visited := 0
	for len(queue) > 0 {
		node := queue[0]
		queue = queue[1:]
		visited++

		dp[node][colors[node]-'a']++
		for color := range 26 {
			ans = max(ans, dp[node][color])
		}

		for _, out := range outMap[node] {
			inDegrees[out]--
			if inDegrees[out] == 0 {
				queue = append(queue, out)
			}
			for color := range 26 {
				dp[out][color] = max(dp[out][color], dp[node][color])
			}
		}
	}

	// Check cycle
	if visited < n {
		return -1
	}

	return ans
}
