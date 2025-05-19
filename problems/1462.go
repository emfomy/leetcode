// Source: https://leetcode.com/problems/course-schedule-iv
// Title: Course Schedule IV
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There are a total of `numCourses` courses you have to take, labeled from `0` to `numCourses - 1`. You are given an array `prerequisites` where `prerequisites[i] = [a_i, b_i]` indicates that you **must** take course `a_i` first if you want to take course `b_i`.
//
// - For example, the pair `[0, 1]` indicates that you have to take course `0` before you can take course `1`.
//
// Prerequisites can also be **indirect**. If course `a` is a prerequisite of course `b`, and course `b` is a prerequisite of course `c`, then course `a` is a prerequisite of course `c`.
//
// You are also given an array `queries` where `queries[j] = [u_j, v_j]`. For the `j^th` query, you should answer whether course `u_j` is a prerequisite of course `v_j` or not.
//
// Return a boolean array `answer`, where `answer[j]` is the answer to the `j^th` query.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/05/01/courses4-1-graph.jpg
//
// ```
// Input: numCourses = 2, prerequisites = [[1,0]], queries = [[0,1],[1,0]]
// Output: [false,true]
// Explanation: The pair [1, 0] indicates that you have to take course 1 before you can take course 0.
// Course 0 is not a prerequisite of course 1, but the opposite is true.
// ```
//
// **Example 2:**
//
// ```
// Input: numCourses = 2, prerequisites = [], queries = [[1,0],[0,1]]
// Output: [false,false]
// Explanation: There are no prerequisites, and each course is independent.
// ```
//
// **Example 3:**
// https://assets.leetcode.com/uploads/2021/05/01/courses4-3-graph.jpg
//
// ```
// Input: numCourses = 3, prerequisites = [[1,2],[1,0],[2,0]], queries = [[1,0],[1,2]]
// Output: [true,true]
// ```
//
// **Constraints:**
//
// - `2 <= numCourses <= 100`
// - `0 <= prerequisites.length <= (numCourses * (numCourses - 1) / 2)`
// - `prerequisites[i].length == 2`
// - `0 <= a_i, b_i <= numCourses - 1`
// - `a_i != b_i`
// - All the pairs `[a_i, b_i]` are **unique**.
// - The prerequisites graph has no cycles.
// - `1 <= queries.length <= 10^4`
// - `0 <= u_i, v_i <= numCourses - 1`
// - `u_i != v_i`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// Use topological sort
func checkIfPrerequisite(numCourses int, prerequisites [][]int, queries [][]int) []bool {
	// Prepare the graph
	postMap := make([][]int, numCourses)
	for _, prerequisite := range prerequisites {
		a, b := prerequisite[0], prerequisite[1]
		postMap[a] = append(postMap[a], b)
	}

	// Count in-degrees
	inDegrees := make([]int, numCourses)
	for _, prerequisite := range prerequisites {
		b := prerequisite[1]
		inDegrees[b]++
	}

	// Prepare the queue
	queue := make([]int, 0, numCourses)
	for class := range numCourses {
		if inDegrees[class] == 0 {
			queue = append(queue, class)
		}
	}

	// Prepare the matrix
	isPre := make([][]bool, numCourses)
	for i := range numCourses {
		isPre[i] = make([]bool, numCourses)
	}

	// Loop through the queue
	for len(queue) > 0 {
		class := queue[0]
		queue = queue[1:]

		for _, postClass := range postMap[class] {
			isPre[postClass][class] = true

			for pre, val := range isPre[class] {
				if val {
					isPre[postClass][pre] = true
				}
			}

			inDegrees[postClass]--
			if inDegrees[postClass] == 0 {
				queue = append(queue, postClass)
			}
		}
	}

	// Loop through the queries
	res := make([]bool, 0, len(queries))
	for _, query := range queries {
		a, b := query[0], query[1]
		res = append(res, isPre[b][a])
	}

	return res
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

type bitset struct {
	low  uint64 // used for 1~64 bits
	high uint64 // used for 64~128 bits
}

func (b *bitset) union(other bitset) {
	b.low |= other.low
	b.high |= other.high
}

func (b *bitset) set(bit int) {
	if bit < 64 {
		b.low |= 1 << bit
	} else {
		b.high |= 1 << (bit - 64)
	}
}

func (b bitset) get(bit int) bool {
	if bit < 64 {
		return b.low&(1<<bit) != 0
	} else {
		return b.high&(1<<(bit-64)) != 0
	}
}

// Use topological sort
//
// Use bit-set to optimise
func checkIfPrerequisite2(numCourses int, prerequisites [][]int, queries [][]int) []bool {
	// Prepare the graph
	postMap := make([][]int, numCourses)
	for _, prerequisite := range prerequisites {
		a, b := prerequisite[0], prerequisite[1]
		postMap[a] = append(postMap[a], b)
	}

	// Count in-degrees
	inDegrees := make([]int, numCourses)
	for _, prerequisite := range prerequisites {
		b := prerequisite[1]
		inDegrees[b]++
	}

	// Prepare the queue
	queue := make([]int, 0, numCourses)
	for class := range numCourses {
		if inDegrees[class] == 0 {
			queue = append(queue, class)
		}
	}

	// Prepare the matrix
	isPre := make([]bitset, numCourses)

	// Loop through the queue
	for len(queue) > 0 {
		class := queue[0]
		queue = queue[1:]

		for _, postClass := range postMap[class] {
			isPre[postClass].set(class)
			isPre[postClass].union(isPre[class])

			inDegrees[postClass]--
			if inDegrees[postClass] == 0 {
				queue = append(queue, postClass)
			}
		}
	}

	// Loop through the queries
	res := make([]bool, 0, len(queries))
	for _, query := range queries {
		a, b := query[0], query[1]
		res = append(res, isPre[b].get(a))
	}

	return res
}
