// Source: https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended-ii
// Title: Maximum Number of Events That Can Be Attended II
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an array of `events` where `events[i] = [startDay_i, endDay_i, value_i]`. The `i^th` event starts at `startDay_i`_ and ends at `endDay_i`, and if you attend this event, you will receive a value of `value_i`. You are also given an integer `k` which represents the maximum number of events you can attend.
//
// You can only attend one event at a time. If you choose to attend an event, you must attend the **entire** event. Note that the end day is **inclusive**: that is, you cannot attend two events where one of them starts and the other ends on the same day.
//
// Return the **maximum sum** of values that you can receive by attending events.
//
// **Example 1:**
//
// https://assets.leetcode.com/uploads/2021/01/10/screenshot-2021-01-11-at-60048-pm.png
//
// ```
// Input: events = [[1,2,4],[3,4,3],[2,3,1]], k = 2
// Output: 7
// Explanation: Choose the green events, 0 and 1 (0-indexed) for a total value of 4 + 3 = 7.```
//
// **Example 2:**
//
// https://assets.leetcode.com/uploads/2021/01/10/screenshot-2021-01-11-at-60150-pm.png
//
// ```
// Input: events = [[1,2,4],[3,4,3],[2,3,10]], k = 2
// Output: 10
// Explanation: Choose event 2 for a total value of 10.
// Notice that you cannot attend any other event as they overlap, and that you do **not** have to attend k events.```
//
// **Example 3:**
//
// **https://assets.leetcode.com/uploads/2021/01/10/screenshot-2021-01-11-at-60703-pm.png
//
// ```
// Input: events = [[1,1,1],[2,2,2],[3,3,3],[4,4,4]], k = 3
// Output: 9
// Explanation: Although the events do not overlap, you can only attend 3 events. Pick the highest valued three.```
//
// **Constraints:**
//
// - `1 <= k <= events.length`
// - `1 <= k * events.length <= 10^6`
// - `1 <= startDay_i <= endDay_i <= 10^9`
// - `1 <= value_i <= 10^6`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"slices"
	"sort"
)

// Use DP + Binary Search
//
// # We first sort the events by its start time
//
// Let dp(i, l) be the maximum values for attending l of first i events.
//
// For each event, we may either attend it or skip it.
// If we skip it, we move the next event.
// If we attend it, we use binary search to find next available event (i.e. start after this event's end time).
func maxValue(events [][]int, k int) int {
	n := len(events)

	// Sort by start time
	slices.SortFunc(events, func(a, b []int) int {
		return a[0] - b[0]
	})

	// DP memory
	dp := make([][]int, k)
	for j := range k {
		dp[j] = make([]int, n)
		for i := range n {
			dp[j][i] = -1
		}
	}

	// Binary search next index
	findNextIdx := func(idx int) int {
		shift := idx + 1
		return shift + sort.Search(n-shift, func(i int) bool {
			return events[idx][1] < events[shift+i][0]
		})
	}

	// DFS
	var dfs func(currIdx int, count int) int
	dfs = func(currIdx int, count int) int {
		if count == k || currIdx == n {
			return 0
		}
		if dp[count][currIdx] != -1 { // use memorized value
			return dp[count][currIdx]
		}

		// Binary search next index
		nextIdx := findNextIdx(currIdx)

		// DP
		dp[count][currIdx] = max(
			dfs(currIdx+1, count),                    // skip this event
			dfs(nextIdx, count+1)+events[currIdx][2], // attend this event
		)
		return dp[count][currIdx]
	}

	return dfs(0, 0)
}

// Use DP + Binary Search
//
// We also cache binary search result
func maxValue2(events [][]int, k int) int {
	n := len(events)

	// Sort by start time
	slices.SortFunc(events, func(a, b []int) int {
		return a[0] - b[0]
	})

	// Find next indices
	nextIdxs := make([]int, n)
	for idx := range n {
		nextIdxs[idx] = idx + 1 + sort.Search(n-idx-1, func(i int) bool {
			return events[idx][1] < events[idx+1+i][0]
		})
	}

	// DP memory
	dp := make([][]int, k)
	for j := range k {
		dp[j] = make([]int, n)
		for i := range n {
			dp[j][i] = -1
		}
	}

	// DFS
	var dfs func(currIdx int, count int) int
	dfs = func(idx int, count int) int {
		if count == k || idx == n {
			return 0
		}
		if dp[count][idx] != -1 { // use memorized value
			return dp[count][idx]
		}

		// DP
		dp[count][idx] = max(
			dfs(idx+1, count), // skip this event
			dfs(nextIdxs[idx], count+1)+events[idx][2], // attend this event
		)
		return dp[count][idx]
	}

	return dfs(0, 0)
}
