// Source: https://leetcode.com/problems/meeting-rooms-iii
// Title: Meeting Rooms III
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer `n`. There are `n` rooms numbered from `0` to `n - 1`.
//
// You are given a 2D integer array `meetings` where `meetings[i] = [start_i, end_i]` means that a meeting will be held during the **half-closed** time interval `[start_i, end_i)`. All the values of `start_i` are **unique**.
//
// Meetings are allocated to rooms in the following manner:
//
// - Each meeting will take place in the unused room with the **lowest** number.
// - If there are no available rooms, the meeting will be delayed until a room becomes free. The delayed meeting should have the **same** duration as the original meeting.
// - When a room becomes unused, meetings that have an earlier original **start** time should be given the room.
//
// Return the **number** of the room that held the most meetings. If there are multiple rooms, return the room with the **lowest** number.
//
// A **half-closed interval** `[a, b)` is the interval between `a` and `b` **including** `a` and **not including** `b`.
//
// **Example 1:**
//
// ```
// Input: n = 2, meetings = [[0,10],[1,5],[2,7],[3,4]]
// Output: 0
// Explanation:
// - At time 0, both rooms are not being used. The first meeting starts in room 0.
// - At time 1, only room 1 is not being used. The second meeting starts in room 1.
// - At time 2, both rooms are being used. The third meeting is delayed.
// - At time 3, both rooms are being used. The fourth meeting is delayed.
// - At time 5, the meeting in room 1 finishes. The third meeting starts in room 1 for the time period [5,10).
// - At time 10, the meetings in both rooms finish. The fourth meeting starts in room 0 for the time period [10,11).
// Both rooms 0 and 1 held 2 meetings, so we return 0.
// ```
//
// **Example 2:**
//
// ```
// Input: n = 3, meetings = [[1,20],[2,10],[3,5],[4,9],[6,8]]
// Output: 1
// Explanation:
// - At time 1, all three rooms are not being used. The first meeting starts in room 0.
// - At time 2, rooms 1 and 2 are not being used. The second meeting starts in room 1.
// - At time 3, only room 2 is not being used. The third meeting starts in room 2.
// - At time 4, all three rooms are being used. The fourth meeting is delayed.
// - At time 5, the meeting in room 2 finishes. The fourth meeting starts in room 2 for the time period [5,10).
// - At time 6, all three rooms are being used. The fifth meeting is delayed.
// - At time 10, the meetings in rooms 1 and 2 finish. The fifth meeting starts in room 1 for the time period [10,12).
// Room 0 held 1 meeting while rooms 1 and 2 each held 2 meetings, so we return 1.
// ```
//
// **Constraints:**
//
// - `1 <= n <= 100`
// - `1 <= meetings.length <= 10^5`
// - `meetings[i].length == 2`
// - `0 <= start_i < end_i <= 5 * 10^5`
// - All the values of `start_i` are **unique**.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"slices"

	"github.com/emirpasic/gods/v2/trees/binaryheap"
)

// Simulation
func mostBooked(n int, meetings [][]int) int {
	// Sort meetings
	slices.SortFunc(meetings, func(a, b []int) int {
		return a[0] - b[0]
	})

	freeRooms := binaryheap.New[int]()                      // [room id]
	busyRooms := binaryheap.NewWith(func(x, y [2]int) int { // [room id, available time]
		if x[1] != y[1] {
			return x[1] - y[1]
		}
		return x[0] - y[0]
	})
	for i := range n {
		freeRooms.Push(i)
	}

	// Room
	counter := make([]int, n) // number of meetings in each room

	// Simulation
	for _, meeting := range meetings {
		// Clear busy room
		for busyRooms.Size() > 0 {
			room, _ := busyRooms.Peek()
			if room[1] <= meeting[0] {
				busyRooms.Pop()
				freeRooms.Push(room[0])
			} else {
				break
			}
		}

		// Check free room
		roomId, ok := freeRooms.Pop()
		if !ok {
			// delay meeting
			room, _ := busyRooms.Pop()
			roomId = room[0]
			meeting[1] += room[1] - meeting[0]
		}

		counter[roomId]++
		room := [2]int{roomId, meeting[1]}
		busyRooms.Push(room)
	}

	// Answer
	ans := 0
	maxCount := 0
	for i, count := range counter {
		if maxCount < count {
			ans = i
			maxCount = count
		}
	}

	return ans
}

// Simulation
//
// Since n is small, we don't need to use heap.
func mostBooked2(n int, meetings [][]int) int {
	// Sort meetings
	slices.SortFunc(meetings, func(a, b []int) int {
		return a[0] - b[0]
	})

	rooms := make([]int, n)   // available time for each room
	counter := make([]int, n) // number of meetings in each room

	// Simulation
	for _, meeting := range meetings {
		// Find free rooms
		roomId := slices.IndexFunc(rooms, func(time int) bool {
			return time <= meeting[0]
		})

		// Delay meeting
		if roomId == -1 {
			minRoom := slices.Min(rooms)
			roomId = slices.Index(rooms, minRoom)
			meeting[1] += minRoom - meeting[0] // delay
		}

		counter[roomId]++
		rooms[roomId] = meeting[1]
	}

	// Answer
	return slices.Index(counter, slices.Max(counter))
}
