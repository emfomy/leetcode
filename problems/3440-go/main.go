// Source: https://leetcode.com/problems/reschedule-meetings-for-maximum-free-time-ii
// Title: Reschedule Meetings for Maximum Free Time II
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer `eventTime` denoting the duration of an event. You are also given two integer arrays `startTime` and `endTime`, each of length `n`.
//
// These represent the start and end times of `n` **non-overlapping** meetings that occur during the event between time `t = 0` and time `t = eventTime`, where the `i^th` meeting occurs during the time `[startTime[i], endTime[i]].`
//
// You can reschedule **at most **one meeting by moving its start time while maintaining the **same duration**, such that the meetings remain non-overlapping, to **maximize** the **longest** continuous period of free time during the event.
//
// Return the **maximum** amount of free time possible after rearranging the meetings.
//
// **Note** that the meetings can **not** be rescheduled to a time outside the event and they should remain non-overlapping.
//
// **Note:** In this version, it is **valid** for the relative ordering of the meetings to change after rescheduling one meeting.
//
// **Example 1:**
//
// ```
// Input: eventTime = 5, startTime = [1,3], endTime = [2,5]
// Output: 2
// Explanation:
// https://assets.leetcode.com/uploads/2024/12/22/example0_rescheduled.png
// Reschedule the meeting at `[1, 2]` to `[2, 3]`, leaving no meetings during the time `[0, 2]`.
// ```
//
// **Example 2:**
//
// ```
// Input: eventTime = 10, startTime = [0,7,9], endTime = [1,8,10]
// Output: 7
// Explanation:
// https://assets.leetcode.com/uploads/2024/12/22/rescheduled_example0.png
// Reschedule the meeting at `[0, 1]` to `[8, 9]`, leaving no meetings during the time `[0, 7]`.
// ```
//
// **Example 3:**
//
// ```
// Input: eventTime = 10, startTime = [0,3,7,9], endTime = [1,4,8,10]
// Output: 6
// Explanation:
// https://assets.leetcode.com/uploads/2025/01/28/image3.png
// Reschedule the meeting at `[3, 4]` to `[8, 9]`, leaving no meetings during the time `[1, 7]`.
// ```
//
// **Example 4:**
//
// ```
// Input: eventTime = 5, startTime = [0,1,2,3,4], endTime = [1,2,3,4,5]
// Output: 0
// Explanation:
// There is no time during the event not occupied by meetings.
// ```
//
// **Constraints:**
//
// - `1 <= eventTime <= 10^9`
// - `n == startTime.length == endTime.length`
// - `2 <= n <= 10^5`
// - `0 <= startTime[i] < endTime[i] <= eventTime`
// - `endTime[i] <= startTime[i + 1]` where `i` lies in the range `[0, n - 2]`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import "fmt"

// Greedy
//
// First compute the gaps between each meetings.
// For each meeting, if there is a gap (no adjacent to this meeting) larger than this meeting,
// it is better to move this meeting to that gap.
// Otherwise, just snap this meeting to the previous meeting.
func maxFreeTime(eventTime int, startTime []int, endTime []int) int {
	n := len(startTime)

	start := func(i int) int {
		if i == n {
			return eventTime
		}
		return startTime[i]
	}
	end := func(i int) int {
		if i == -1 {
			return 0
		}
		return endTime[i]
	}

	maxGap := make([]int, n)
	{ // left max
		maxVal := 0
		for i := 1; i < n; i++ {
			maxVal = max(maxVal, start(i-1)-end(i-2))
			maxGap[i] = max(maxGap[i], maxVal)
		}
	}
	{ // right max
		maxVal := 0
		for i := n - 2; i >= 0; i-- {
			maxVal = max(maxVal, start(i+2)-end(i+1))
			maxGap[i] = max(maxGap[i], maxVal)
		}
	}

	ans := 0
	for i := range n {
		meeting := endTime[i] - startTime[i]
		period := start(i+1) - end(i-1)
		if maxGap[i] < meeting {
			period -= meeting
		}
		ans = max(ans, period)
	}

	return ans
}

func main() {
	fmt.Println(maxFreeTime(
		5, []int{1, 3}, []int{2, 5},
	))
}
