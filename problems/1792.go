// Source: https://leetcode.com/problems/maximum-average-pass-ratio
// Title: Maximum Average Pass Ratio
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There is a school that has classes of students and each class will be having a final exam. You are given a 2D integer array `classes`, where `classes[i] = [pass_i, total_i]`. You know beforehand that in the `i^th` class, there are `total_i` total students, but only `pass_i` number of students will pass the exam.
//
// You are also given an integer `extraStudents`. There are another `extraStudents` brilliant students that are **guaranteed** to pass the exam of any class they are assigned to. You want to assign each of the `extraStudents` students to a class in a way that **maximizes** the **average** pass ratio across **all** the classes.
//
// The **pass ratio** of a class is equal to the number of students of the class that will pass the exam divided by the total number of students of the class. The **average pass ratio** is the sum of pass ratios of all the classes divided by the number of the classes.
//
// Return the **maximum** possible average pass ratio after assigning the `extraStudents` students. Answers within `10^-5` of the actual answer will be accepted.
//
// **Example 1:**
//
// ```
// Input: classes = [[1,2],[3,5],[2,2]], `extraStudents` = 2
// Output: 0.78333
// Explanation: You can assign the two extra students to the first class. The average pass ratio will be equal to (3/4 + 3/5 + 2/2) / 3 = 0.78333.
// ```
//
// **Example 2:**
//
// ```
// Input: classes = [[2,4],[3,9],[4,5],[2,10]], `extraStudents` = 4
// Output: 0.53485
// ```
//
// **Constraints:**
//
// - `1 <= classes.length <= 10^5`
// - `classes[i].length == 2`
// - `1 <= pass_i <= total_i <= 10^5`
// - `1 <= extraStudents <= 10^5`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"container/heap"
)

type classType struct {
	pass  float64
	total float64
	diff  float64 // = (pass+1)/(total+1) - pass/total
}

func newClassType(class []int) classType {
	pass := float64(class[0])
	total := float64(class[1])
	return classType{
		pass:  pass,
		total: total,
		diff:  (pass+1)/(total+1) - pass/total,
	}
}

func (c *classType) Add(x int) {
	c.pass += float64(x)
	c.total += float64(x)
	c.diff = (c.pass+1)/(c.total+1) - c.pass/c.total
}

type classHeap []classType

func (h classHeap) Len() int           { return len(h) }
func (h classHeap) Less(i, j int) bool { return h[i].diff > h[j].diff } // max-heap
func (h classHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }

func newClassHeap(classes [][]int) *classHeap {
	h := make(classHeap, 0, len(classes))
	for _, class := range classes {
		h = append(h, newClassType(class))
	}
	heap.Init(&h)
	return &h
}

func (h *classHeap) Push(x interface{}) {
	*h = append(*h, x.(classType))
}

func (h *classHeap) Pop() interface{} {
	n := len(*h)
	x := (*h)[n-1]
	*h = (*h)[:n-1]
	return x
}

func (h *classHeap) Peak() *classType {
	if h.Len() == 0 {
		return nil
	}
	return &(*h)[0]
}

func maxAverageRatio(classes [][]int, extraStudents int) float64 {
	h := newClassHeap(classes)

	for i := 0; i < extraStudents; i++ {
		class := heap.Pop(h).(classType)
		class.Add(1)
		heap.Push(h, class)
	}

	res := float64(0)
	for _, class := range *h {
		res += class.pass / class.total
	}
	return res / float64(len(classes))
}
