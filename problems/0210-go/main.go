// Source: https://leetcode.com/problems/course-schedule-ii
// Title: Course Schedule II
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There are a total of numCourses courses you have to take, labeled from 0 to numCourses-1. You are given an array prerequisites where prerequisites[i] = [a_i, b_i] indicates that you must take course b_i first if you want to take course a_i.
//
// For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.
//
// Return the ordering of courses you should take to finish all courses. If there are many valid answers, return any of them. If it is impossible to finish all courses, return an empty array.
//
// Example 1:
//
//   Input: numCourses = 2, prerequisites = [[1,0]]
//   Output: [0,1]
//   Explanation: There are a total of 2 courses to take. To take course 1 you should have finished course 0. So the correct course order is [0,1].
//
// Example 2:
//
//   Input: numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
//   Output: [0,2,1,3]
//   Explanation:
//     There are a total of 4 courses to take. To take course 3 you should have finished both courses 1 and 2. Both courses 1 and 2 should be taken after you finished course 0.
//     So one correct course order is [0,1,2,3]. Another correct ordering is [0,2,1,3].
//
// Example 3:
//
//   Input: numCourses = 1, prerequisites = []
//   Output: [0]
//
// Constraints:
//
//   1 <= numCourses <= 2000
//   0 <= prerequisites.length <= numCourses * (numCourses-1)
//   prerequisites[i].length == 2
//   0 <= a_i, b_i < numCourses
//   a_i != b_i
//   All the pairs [a_i, b_i] are distinct.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"sort"
)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Use inward degree
func findOrder(numCourses int, prerequisites [][]int) []int {
	// Create graph
	inDegrees := make([]int, numCourses)
	outEdges := make([][]int, numCourses)
	for _, pair := range prerequisites {
		post, pre := pair[0], pair[1]
		inDegrees[post]++
		outEdges[pre] = append(outEdges[pre], post)
	}

	res := make([]int, numCourses)
	for i := 0; i < numCourses; i++ {
		res[i] = i
	}

	// Take course that don't have prerequisites first
	numVisited := 0
	for numVisited < numCourses {

		// Order by inward degrees
		sort.Slice(res[numVisited:], func(i, j int) bool {
			return inDegrees[res[i+numVisited]] < inDegrees[res[j+numVisited]]
		})

		// Cycle deleted
		if inDegrees[res[numVisited]] != 0 {
			return nil
		}

		for ; numVisited < numCourses; numVisited++ {
			id := res[numVisited]
			if inDegrees[id] != 0 {
				break
			}
			res[numVisited] = id
			for _, postId := range outEdges[id] {
				inDegrees[postId]--
			}
		}
	}

	return res
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Use DFS
// A course without prerequisites should be taken first
// Note that here we reverse the graph
func findOrder2(numCourses int, prerequisites [][]int) []int {
	// Create graph
	graph := make([][]int, numCourses) // map post to pres
	for i := 0; i < numCourses; i++ {
		graph[i] = []int{}
	}

	for _, pair := range prerequisites {
		post, pre := pair[0], pair[1]
		graph[post] = append(graph[post], pre)
	}

	// DFS
	res := make([]int, 0, numCourses)
	visited := make([]bool, numCourses)
	finished := make([]bool, numCourses)
	for i := 0; i < numCourses; i++ {
		if ok := _dfs(graph, visited, finished, i, &res); !ok {
			return nil
		}
	}

	return res
}

func _dfs(graph [][]int, visited, finished []bool, curr int, res *[]int) bool {
	if finished[curr] { // this node has been visited, skip it
		return true
	}
	if visited[curr] { // met a node which is visiting i.e. cycle detected
		return false
	}

	visited[curr] = true
	for _, next := range graph[curr] {
		if ok := _dfs(graph, visited, finished, next, res); !ok {
			return false
		}
	}
	finished[curr] = true
	*res = append(*res, curr)

	return true
}
