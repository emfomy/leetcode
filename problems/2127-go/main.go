// Source: https://leetcode.com/problems/maximum-employees-to-be-invited-to-a-meeting
// Title: Maximum Employees to Be Invited to a Meeting
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// A company is organizing a meeting and has a list of `n` employees, waiting to be invited. They have arranged for a large **circular** table, capable of seating **any number** of employees.
//
// The employees are numbered from `0` to `n - 1`. Each employee has a **favorite** person and they will attend the meeting **only if** they can sit next to their favorite person at the table. The favorite person of an employee is **not** themself.
//
// Given a **0-indexed** integer array `favorite`, where `favorite[i]` denotes the favorite person of the `i^th` employee, return the **maximum number of employees** that can be invited to the meeting.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/12/14/ex1.png
//
// ```
// Input: favorite = [2,2,1,2]
// Output: 3
// Explanation:
// The above figure shows how the company can invite employees 0, 1, and 2, and seat them at the round table.
// All employees cannot be invited because employee 2 cannot sit beside employees 0, 1, and 3, simultaneously.
// Note that the company can also invite employees 1, 2, and 3, and give them their desired seats.
// The maximum number of employees that can be invited to the meeting is 3.
// ```
//
// **Example 2:**
//
// ```
// Input: favorite = [1,2,0]
// Output: 3
// Explanation:
// Each employee is the favorite person of at least one other employee, and the only way the company can invite them is if they invite every employee.
// The seating arrangement will be the same as that in the figure given in example 1:
// - Employee 0 will sit between employees 2 and 1.
// - Employee 1 will sit between employees 0 and 2.
// - Employee 2 will sit between employees 1 and 0.
// The maximum number of employees that can be invited to the meeting is 3.
// ```
//
// **Example 3:**
// https://assets.leetcode.com/uploads/2021/12/14/ex2.png
//
// ```
// Input: favorite = [3,0,1,4,1]
// Output: 4
// Explanation:
// The above figure shows how the company will invite employees 0, 1, 3, and 4, and seat them at the round table.
// Employee 2 cannot be invited because the two spots next to their favorite employee 1 are taken.
// So the company leaves them out of the meeting.
// The maximum number of employees that can be invited to the meeting is 4.
// ```
//
// **Constraints:**
//
// - `n == favorite.length`
// - `2 <= n <= 10^5`
// - `0 <= favorite[i] <=n - 1`
// - `favorite[i] != i`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// First we create a indirect graph, where the edge indicate the favorite relationship.
//
// There are two possible tables:
// 1. It could be a cycle. A -> B -> C -> ... -> A
// 2. It could be multiple 2-cycle with arms. (A -> B -> ... -> C <-> D <- E <- ... <- ) * k
func maximumInvitations(favorite []int) int {
	n := len(favorite)

	favoriteRev := make([][]int, n)
	for i := range n {
		favoriteRev[favorite[i]] = append(favoriteRev[favorite[i]], i)
	}

	visited := make([]bool, n)
	twoCycles := make([][2]int, 0, n)

	// Find a cycle, returns the end node and the distance
	findCycle := func(node int) (int, int) {
		dist := 0
		for true {
			if visited[node] {
				break
			}
			dist++
			visited[node] = true
			node = favorite[node]
		}
		return node, dist
	}

	// Find the target node, returns the distance
	findNode := func(node, target int) int {
		dist := 0
		for true {
			if node == target {
				break
			}
			dist++
			node = favorite[node]
		}
		return dist
	}

	// Finc cycles
	maxCycle := 0
	for start := range n {
		if visited[start] {
			continue
		}

		end, endDist := findCycle(start)
		midDist := findNode(start, end)

		cycleSize := endDist - midDist

		maxCycle = max(maxCycle, cycleSize)
		if cycleSize == 2 {
			twoCycles = append(twoCycles, [2]int{end, favorite[end]})
		}
	}

	var dfs func(int) int
	dfs = func(node int) int {
		dist := 0
		for _, next := range favoriteRev[node] {
			dist = max(dist, dfs(next)+1)
		}
		return dist
	}

	// Extend two-cycles
	twoCycleTotal := 0
	for _, pair := range twoCycles {
		a, b := pair[0], pair[1]

		aDist := 0
		for _, next := range favoriteRev[a] {
			if next == b {
				continue
			}
			aDist = max(aDist, dfs(next)+1)
		}

		bDist := 0
		for _, next := range favoriteRev[b] {
			if next == a {
				continue
			}
			bDist = max(bDist, dfs(next)+1)
		}

		twoCycleTotal += aDist + bDist + 2
	}

	return max(maxCycle, twoCycleTotal)
}

// Same as above. We need to find the cycles.
//
// Here we use topological sort to find the cycles.
// Note that topological sort only works on DAGs(Directed Acyclic Graphs),
// but we can still use it to eliminate non-cycle nodes.
//
// We first put all node with 0-in-degree in a queue.
// Loop through the queue, removing the edges,
// and put nodes that become 0-in-degree into the queue.
// After the algorithm, all the nodes left in the graph are cycles.
//
// In order to find the arm length,
// we also track the depth from the leaves in the algorithm.
func maximumInvitations2(favorite []int) int {
	n := len(favorite)

	depth := make([]int, n)

	// Count in-degrees
	inDegrees := make([]int, n)
	for node := range n {
		inDegrees[favorite[node]]++
	}

	// Prepare the queue
	queue := make([]int, 0, n)
	for node := range n {
		if inDegrees[node] == 0 {
			queue = append(queue, node)
		}
	}

	// Loop through the queue
	for len(queue) > 0 {
		node := queue[0]
		queue = queue[1:]

		next := favorite[node]
		depth[next] = max(depth[next], depth[node]+1)
		inDegrees[next]--

		if inDegrees[next] == 0 {
			queue = append(queue, next)
		}
	}

	// Find cycle size
	maxCycle := 0
	twoCycleTotal := 0
	for node := range n {
		if inDegrees[node] == 0 {
			continue
		}

		// Find cycle size
		cycleSize := 0
		curr := node
		for inDegrees[curr] != 0 {
			inDegrees[curr] = 0
			cycleSize++
			curr = favorite[curr]
		}
		maxCycle = max(maxCycle, cycleSize)

		if cycleSize == 2 {
			twoCycleTotal += depth[node] + depth[favorite[node]] + 2
		}

	}

	return max(maxCycle, twoCycleTotal)
}
