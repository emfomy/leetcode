// Source: https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended
// Title: Maximum Number of Events That Can Be Attended
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an array of `events` where `events[i] = [startDay_i, endDay_i]`. Every event `i` starts at `startDay_i`_ and ends at `endDay_i`.
//
// You can attend an event `i` at any day `d` where `startTime_i <= d <= endTime_i`. You can only attend one event at any time `d`.
//
// Return the maximum number of events you can attend.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2020/02/05/e1.png
//
// ```
// Input: events = [[1,2],[2,3],[3,4]]
// Output: 3
// Explanation: You can attend all the three events.
// One way to attend them all is as shown.
// Attend the first event on day 1.
// Attend the second event on day 2.
// Attend the third event on day 3.
// ```
//
// **Example 2:**
//
// ```
// Input: events= [[1,2],[2,3],[3,4],[1,2]]
// Output: 4
// ```
//
// **Constraints:**
//
// - `1 <= events.length <= 10^5`
// - `events[i].length == 2`
// - `1 <= startDay_i <= endDay_i <= 10^5`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"slices"

	"github.com/emirpasic/gods/v2/trees/binaryheap"
)

// Use Greedy
//
// You should always attend the event that end first.
//
// Each day,
// 1. Add started events into a pool.
// 2. Remove ended events.
// 3. Attend an event if possible.
func maxEvents(events [][]int) int {

	// Sort by (start, end) pair
	slices.SortFunc(events, func(a, b []int) int {
		if a[0] != b[0] {
			return a[0] - b[0]
		}
		return a[1] - b[1]
	})

	heap := binaryheap.New[int]() // available events (end date)

	ans := 0
	now := 1
	for len(events) > 0 || heap.Size() > 0 {
		// Add started event to heap
		for len(events) > 0 && events[0][0] <= now {
			heap.Push(events[0][1])
			events = events[1:]
		}

		// Remove ended events
		for {
			if end, ok := heap.Peek(); ok && end < now {
				heap.Pop()
			} else {
				break
			}
		}

		// Attend an event
		if _, ok := heap.Pop(); ok {
			ans++
		}

		now++
	}

	return ans
}
