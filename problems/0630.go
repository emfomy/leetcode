// Source: https://leetcode.com/problems/course-schedule-iii
// Title: Course Schedule III
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There are n different online courses numbered from 1 to n. You are given an array courses where courses[i] = [duration_i, lastDay_i] indicate that the ith course should be taken continuously for duration_i days and must be finished before or on lastDay_i.
//
// You will start on the 1st day and you cannot take two or more courses simultaneously.
//
// Return the maximum number of courses that you can take.
//
// Example 1:
//
//   Input: courses = [[100,200],[200,1300],[1000,1250],[2000,3200]]
//   Output: 3
//   Explanation:
//     There are totally 4 courses, but you can take 3 courses at most:
//     First, take the 1st course, it costs 100 days so you will finish it on the 100th day, and ready to take the next course on the 101st day.
//     Second, take the 3rd course, it costs 1000 days so you will finish it on the 1100th day, and ready to take the next course on the 1101st day.
//     Third, take the 2nd course, it costs 200 days so you will finish it on the 1300th day.
//     The 4th course cannot be taken now, since you will finish it on the 3300th day, which exceeds the closed date.
//
// Example 2:
//
//   Input: courses = [[1,2]]
//   Output: 1
//
// Example 3:
//
//   Input: courses = [[3,2],[4,3]]
//   Output: 0
//
// Constraints:
//
//   1 <= courses.length <= 10^4
//   1 <= duration_i, lastDay_i <= 10^4
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"container/heap"
	"sort"
)

type intHeap []int

func (h intHeap) Len() int           { return len(h) }
func (h intHeap) Less(i, j int) bool { return h[i] > h[j] } // we want max-heap
func (h intHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }

func newIntHeap(arr []int) *intHeap {
	h := intHeap(arr)
	heap.Init(&h)
	return &h
}

func (h *intHeap) Push(x interface{}) {
	*h = append(*h, x.(int))
}

func (h *intHeap) Pop() interface{} {
	n := len(*h)
	x := (*h)[n-1]
	*h = (*h)[:n-1]
	return x
}

func (h *intHeap) Peak() int {
	if h.Len() == 0 {
		return -1
	}
	return (*h)[0]
}

func scheduleCourse(courses [][]int) int {
	// Sort by last day and duration
	sort.Slice(courses, func(i, j int) bool {
		return courses[i][1] < courses[j][1]
	})

	currDay := 0

	takenCourses := newIntHeap(make([]int, 0, len(courses)))

	for _, course := range courses {
		duration := course[0]
		lastDay := course[1]

		// We can take this course
		if currDay+duration <= lastDay {
			currDay += duration
			heap.Push(takenCourses, duration)
			continue
		}

		// We don't have enough time. Try to replace a previous course with longest duration.
		prev := takenCourses.Peak()
		if prev > duration {
			heap.Pop(takenCourses)
			currDay += duration - prev
			heap.Push(takenCourses, duration)
			continue
		}
	}

	return takenCourses.Len()
}
