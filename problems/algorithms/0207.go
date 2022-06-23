// Source: https://leetcode.com/problems/course-schedule/
// Title: Course Schedule
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There are a total of numCourses courses you have to take, labeled from 0 to numCourses-1. You are given an array prerequisites where prerequisites[i] = [a_i, b_i] indicates that you must take course b_i first if you want to take course a_i.
//
// For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.

// Return true if you can finish all courses. Otherwise, return false.
//
// Example 1:
//
//   Input: numCourses = 2, prerequisites = [[1,0]]
//   Output: true
//   Explanation:
//     There are a total of 2 courses to take.
//     To take course 1 you should have finished course 0. So it is possible.
//
// Example 2:
//
//   Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
//   Output: false
//   Explanation:
//     There are a total of 2 courses to take.
//     To take course 1 you should have finished course 0, and to take course 0 you should also have finished course 1. So it is impossible.
//
// Constraints:
//
//   1 <= numCourses <= 2000
//   0 <= prerequisites.length <= 5000
//   prerequisites[i].length == 2
//   0 <= a_i, b_i < numCourses
//   All the pairs prerequisites[i] are unique.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// Use DFS to detect cycle
func canFinish(numCourses int, prerequisites [][]int) bool {
	// Create graph
	graph := make([][]int, numCourses) // map pre to posts
	for i := 0; i < numCourses; i++ {
		graph[i] = []int{}
	}

	for _, pair := range prerequisites {
		post, pre := pair[0], pair[1]
		graph[pre] = append(graph[pre], post)
	}

	// DFS
	visited := make([]bool, numCourses)
	finished := make([]bool, numCourses)
	for i := 0; i < numCourses; i++ {
		if ok := _dfs(graph, visited, finished, i); !ok {
			return false
		}
	}
	return true
}

func _dfs(graph [][]int, visited, finished []bool, curr int) bool {
	if finished[curr] { // this node has been visited, skip it
		return true
	}
	if visited[curr] { // met a node which is visiting i.e. cycle detected
		return false
	}

	visited[curr] = true
	for _, next := range graph[curr] {
		if ok := _dfs(graph, visited, finished, next); !ok {
			return false
		}
	}
	finished[curr] = true

	return true
}
