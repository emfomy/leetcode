// Source: https://leetcode.com/problems/two-best-non-overlapping-events
// Title: Two Best Non-Overlapping Events
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a **0-indexed** 2D integer array of `events` where `events[i] = [startTime_i, endTime_i, value_i]`. The `i^th` event starts at `startTime_i` and ends at `endTime_i`, and if you attend this event, you will receive a value of `value_i`. You can choose **at most** **two** **non-overlapping** events to attend such that the sum of their values is **maximized**.
//
// Return this **maximum** sum.
//
// Note that the start time and end time is **inclusive** : that is, you cannot attend two events where one of them starts and the other ends at the same time. More specifically, if you attend an event with end time `t`, the next event must start at or after `t + 1`.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/09/21/picture5.png
//
// ```
// Input: events = [[1,3,2],[4,5,2],[2,4,3]]
// Output: 4
// Explanation: Choose the green events, 0 and 1 for a sum of 2 + 2 = 4.
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2021/09/21/picture1.png
//
// ```
// Input: events = [[1,3,2],[4,5,2],[1,5,5]]
// Output: 5
// Explanation: Choose event 2 for a sum of 5.
// ```
//
// **Example 3:**
// https://assets.leetcode.com/uploads/2021/09/21/picture3.png
//
// ```
// Input: events = [[1,5,3],[1,5,1],[6,6,5]]
// Output: 8
// Explanation: Choose events 0 and 2 for a sum of 3 + 5 = 8.```
//
// **Constraints:**
//
// - `2 <= events.length <= 10^5`
// - `events[i].length == 3`
// - `1 <= startTime_i <= endTime_i <= 10^9`
// - `1 <= value_i <= 10^6`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"slices"
)

// fn should be be arr[mid] < target for bisect left
// fn should be be arr[mid] <= target for bisect right
func bisectFunc(fn func(int) bool, lo, hi int) int {
	for lo < hi {
		mid := (lo + hi) / 2
		if fn(mid) {
			lo = mid + 1
		} else {
			hi = mid
		}
	}
	return lo
}

// Sort by start time
func maxTwoEvents(events [][]int) int {
	n := len(events)

	// Sort by value
	slices.SortFunc(events, func(a []int, b []int) int {
		return a[0] - b[0]
	})

	// Make suffixMax array
	suffixMax := make([]int, n) // the max-valued event starts after event[i]
	suffixMax[n-1] = events[n-1][2]
	for i := n - 2; i >= 0; i-- {
		suffixMax[i] = max(suffixMax[i+1], events[i][2])
	}

	// Loop
	maxSum := 0
	for i := 0; i < n; i++ {
		// Binary search for event start after event[i]'s end
		left := i + 1
		right := n - 1
		found := -1
		for left <= right {
			mid := (left + right) / 2
			if events[mid][0] > events[i][1] {
				found = mid
				right = mid - 1
			} else {
				left = mid + 1
			}
		}

		if found != -1 {
			maxSum = max(maxSum, events[i][2]+suffixMax[found])
		} else {
			maxSum = max(maxSum, events[i][2])
		}
	}

	return maxSum
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Sort by value
func maxTwoEvents2(events [][]int) int {
	type pairType struct {
		start int
		end   int
	}

	// Remove duplications
	eventMap := make(map[pairType]int, len(events))
	for _, event := range events {
		pair := pairType{
			start: event[0],
			end:   event[1],
		}
		eventMap[pair] = max(eventMap[pair], event[2])
	}
	events = make([][]int, 0, len(eventMap))
	for pair, value := range eventMap {
		events = append(events, []int{
			pair.start, pair.end, value,
		})
	}

	// Sort by value
	slices.SortFunc(events, func(a []int, b []int) int {
		return b[2] - a[2]
	})

	maxValue := events[0][2]

	for i, event_i := range events {
		for _, event_j := range events[i+1:] {
			sum := event_i[2] + event_j[2]

			// Sum of two event is less than single event
			if sum < maxValue {
				break
			}

			// Check overlapping
			if event_i[1] < event_j[0] || event_j[1] < event_i[0] {
				maxValue = sum
				break
			}
		}
	}

	return maxValue
}
