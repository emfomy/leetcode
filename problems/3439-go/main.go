// Source: https://leetcode.com/problems/reschedule-meetings-for-maximum-free-time-i
// Title: Reschedule Meetings for Maximum Free Time I
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer `eventTime` denoting the duration of an event, where the event occurs from time `t = 0` to time `t = eventTime`.
//
// You are also given two integer arrays `startTime` and `endTime`, each of length `n`. These represent the start and end time of `n` **non-overlapping** meetings, where the `i^th` meeting occurs during the time `[startTime[i], endTime[i]]`.
//
// You can reschedule **at most** `k` meetings by moving their start time while maintaining the **same duration**, to **maximize** the **longest** continuous period of free time during the event.
//
// The **relative** order of all the meetings should stay the same and they should remain non-overlapping.
//
// Return the **maximum** amount of free time possible after rearranging the meetings.
//
// **Note** that the meetings can **not** be rescheduled to a time outside the event.
//
// **Example 1:**
//
// ```
// Input: eventTime = 5, k = 1, startTime = [1,3], endTime = [2,5]
// Output: 2
// Explanation:
// https://assets.leetcode.com/uploads/2024/12/21/example0_rescheduled.png
// Reschedule the meeting at `[1, 2]` to `[2, 3]`, leaving no meetings during the time `[0, 2]`.
// ```
//
// **Example 2:**
//
// ```
// Input: eventTime = 10, k = 1, startTime = [0,2,9], endTime = [1,4,10]
// Output: 6
// Explanation:
// https://assets.leetcode.com/uploads/2024/12/21/example1_rescheduled.png
// Reschedule the meeting at `[2, 4]` to `[1, 3]`, leaving no meetings during the time `[3, 9]`.
// ```
//
// **Example 3:**
//
// ```
// Input: eventTime = 5, k = 2, startTime = [0,1,2,3,4], endTime = [1,2,3,4,5]
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
// - `1 <= k <= n`
// - `0 <= startTime[i] < endTime[i] <= eventTime`
// - `endTime[i] <= startTime[i + 1]` where `i` lies in the range `[0, n - 2]`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// Greedy + Sliding Window
// O(n) & O(n)
//
// It is always better to reschedule contiguous meetings.
// Say we reschedule meetings [a, b],
// No matter how we move them, the continuous period is always
// (the distance between meeting[a-1] to meeting[b+1]) - (total duration of meeting [a,b]).
// That is, total gap between meetings [a-1, b+1].
//
// We can precompute the gaps, define gap[i] = startTime[i]-endTime[i-1].
// (Note that we define endTime[-1] = 0 and startTime[n] = eventTime).
//
// Now we only need to compute the maximum of contiguous k+1 gaps.
func maxFreeTime(eventTime int, k int, startTime []int, endTime []int) int {
	n := len(startTime)
	gaps := make([]int, n+1)

	gaps[0] = startTime[0]
	gaps[n] = eventTime - endTime[n-1]
	for i := 1; i < n; i++ {
		gaps[i] = startTime[i] - endTime[i-1]
	}

	period := 0
	for i := range k + 1 {
		period += gaps[i]
	}

	ans := period
	for i := range n - k {
		period += gaps[i+k+1] - gaps[i]
		ans = max(ans, period)
	}

	return ans
}

// Greedy + Sliding Window
// O(n) & O(1)
func maxFreeTime2(eventTime int, k int, startTime []int, endTime []int) int {
	n := len(startTime)

	gap := func(i int) int {
		if i == 0 {
			return startTime[0]
		}
		if i == n {
			return eventTime - endTime[n-1]
		}
		return startTime[i] - endTime[i-1]
	}

	period := 0
	for i := range k + 1 {
		period += gap(i)
	}

	ans := period
	for i := range n - k {
		period += gap(i+k+1) - gap(i)
		ans = max(ans, period)
	}

	return ans
}
