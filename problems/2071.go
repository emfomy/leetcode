// Source: htthttps://leetcode.com/problems/maximum-number-of-tasks-you-can-assign
// Title: Maximum Number of Tasks You Can Assign
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You have `n` tasks and `m` workers. Each task has a strength requirement stored in a **0-indexed** integer array `tasks`, with the `i^th` task requiring `tasks[i]` strength to complete. The strength of each worker is stored in a **0-indexed** integer array `workers`, with the `j^th` worker having `workers[j]` strength. Each worker can only be assigned to a **single** task and must have a strength **greater than or equal** to the task's strength requirement (i.e., `workers[j] >= tasks[i]`).
//
// Additionally, you have `pills` magical pills that will **increase a worker's strength** by `strength`. You can decide which workers receive the magical pills, however, you may only give each worker **at most one** magical pill.
//
// Given the **0-indexed **integer arrays `tasks` and `workers` and the integers `pills` and `strength`, return the **maximum** number of tasks that can be completed.
//
// **Example 1:**
//
// ```
// Input: tasks = [**3**,**2**,**1**], workers = [**0**,**3**,**3**], pills = 1, strength = 1
// Output: 3
// Explanation:
// We can assign the magical pill and tasks as follows:
// - Give the magical pill to worker 0.
// - Assign worker 0 to task 2 (0 + 1 >= 1)
// - Assign worker 1 to task 1 (3 >= 2)
// - Assign worker 2 to task 0 (3 >= 3)
// ```
//
// **Example 2:**
//
// ```
// Input: tasks = [**5**,4], workers = [**0**,0,0], pills = 1, strength = 5
// Output: 1
// Explanation:
// We can assign the magical pill and tasks as follows:
// - Give the magical pill to worker 0.
// - Assign worker 0 to task 0 (0 + 5 >= 5)
// ```
//
// **Example 3:**
//
// ```
// Input: tasks = [**10**,**15**,30], workers = [**0**,**10**,10,10,10], pills = 3, strength = 10
// Output: 2
// Explanation:
// We can assign the magical pills and tasks as follows:
// - Give the magical pill to worker 0 and worker 1.
// - Assign worker 0 to task 0 (0 + 10 >= 10)
// - Assign worker 1 to task 1 (10 + 10 >= 15)
// The last pill is not given because it will not make any worker strong enough for the last task.
// ```
//
// **Constraints:**
//
// - `n == tasks.length`
// - `m == workers.length`
// - `1 <= n, m <= 5 * 10^4`
// - `0 <= pills <= m`
// - `0 <= tasks[i], workers[j], strength <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"slices"
)

// Use binary search
// If the answer is k, then it is always better to choose the k-smallest tasks and the k-largest workers
//
// To verify k, loop tasks from largest
// If the task if smaller than the largest worker, then assign it
// If not, then assign it to the smallest possible worker with pill
func maxTaskAssign(tasks []int, workers []int, pills int, strength int) int {
	if strength == 0 { // avoid zero division
		pills = 0
		strength = 1
	}

	n, m := len(tasks), len(workers)

	slices.Sort(tasks)
	slices.Sort(workers)

	check := func(k int) bool {
		ws := slices.Clone(workers[m-k:])
		p := 0
		for i, task := range slices.Backward(tasks[:k]) {
			if task <= ws[i] { // not use pill
				ws = ws[:i]
			} else { // use pill
				if p >= pills { // no more pill
					return false
				}

				j, _ := slices.BinarySearch(ws, task-strength)
				if j >= len(ws) { // impossible
					return false
				}
				ws = slices.Delete(ws, j, j+1)
				p++
			}
		}
		return true
	}

	// Binary Search
	// check(lo-1) = true, check(lo=hi) = false
	lo, hi := 0, min(n, m)+1
	for lo < hi {
		mid := (lo + hi) / 2
		if check(mid) {
			lo = mid + 1
		} else {
			hi = mid
		}
	}

	return lo - 1
}
