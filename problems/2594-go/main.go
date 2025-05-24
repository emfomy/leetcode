// Source: https://leetcode.com/problems/minimum-time-to-repair-cars
// Title: Minimum Time to Repair Cars
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `ranks` representing the **ranks** of some mechanics. ranks_i is the rank of the i^th mechanic. A mechanic with a rank `r` can repair n cars in `r * n^2` minutes.
//
// You are also given an integer `cars` representing the total number of cars waiting in the garage to be repaired.
//
// Return the **minimum** time taken to repair all the cars.
//
// **Note:** All the mechanics can repair the cars simultaneously.
//
// **Example 1:**
//
// ```
// Input: ranks = [4,2,3,1], cars = 10
// Output: 16
// Explanation:
// - The first mechanic will repair two cars. The time required is 4 * 2 * 2 = 16 minutes.
// - The second mechanic will repair two cars. The time required is 2 * 2 * 2 = 8 minutes.
// - The third mechanic will repair two cars. The time required is 3 * 2 * 2 = 12 minutes.
// - The fourth mechanic will repair four cars. The time required is 1 * 4 * 4 = 16 minutes.
// It can be proved that the cars cannot be repaired in less than 16 minutes.
// ```
//
// **Example 2:**
//
// ```
// Input: ranks = [5,1,8], cars = 6
// Output: 16
// Explanation:
// - The first mechanic will repair one car. The time required is 5 * 1 * 1 = 5 minutes.
// - The second mechanic will repair four cars. The time required is 1 * 4 * 4 = 16 minutes.
// - The third mechanic will repair one car. The time required is 8 * 1 * 1 = 8 minutes.
// It can be proved that the cars cannot be repaired in less than 16 minutes.
// ```
//
// **Constraints:**
//
// - `1 <= ranks.length <= 10^5`
// - `1 <= ranks[i] <= 100`
// - `1 <= cars <= 10^6`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"container/heap"
	"math"
	"slices"
)

// Use Binary Search
func repairCars(ranks []int, cars int) int64 {
	check := func(time int64) int { // returns the numbers of cars can be repaired
		count := 0
		for _, rank := range ranks {
			count += int(math.Sqrt(float64(time / int64(rank))))
		}
		return count
	}

	// check(lo-1) < cars <= check(lo=hi)
	lo, hi := int64(0), int64(slices.Min(ranks))*int64(cars)*int64(cars)
	for lo < hi {
		mid := (lo + hi) / 2
		if check(mid) < cars {
			lo = mid + 1
		} else {
			hi = mid
		}
	}

	return lo
}

// Use Binary Search
func repairCars2(ranks []int, cars int) int64 {
	check := func(time int64) bool { // returns the numbers of cars can be repaired
		count := 0
		for _, rank := range ranks {
			count += int(math.Sqrt(float64(time / int64(rank))))
			if count >= cars {
				return true
			}
		}
		return false
	}

	// check(lo-1) < target <= check(lo=hi)
	lo, hi := int64(0), int64(slices.Min(ranks))*int64(cars)*int64(cars)
	for lo < hi {
		mid := (lo + hi) / 2
		if check(mid) {
			hi = mid
		} else {
			lo = mid + 1
		}
	}

	return lo
}

// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

type mechanic struct {
	rank  int64 // rank of mechanic
	count int64 // number of mechanic
	cars  int64 // cars being repaired
	time  int64 // time elapsed
}

func (m *mechanic) inc() {
	m.cars++
	m.time = m.rank * m.cars * m.cars
}

type mechanicHeap []mechanic

func (h mechanicHeap) Len() int { return len(h) }
func (h mechanicHeap) Less(i, j int) bool { // min-heap
	if h[i].time != h[j].time {
		return h[i].time < h[j].time
	}
	return h[i].rank < h[j].rank
}
func (h mechanicHeap) Swap(i, j int) { h[i], h[j] = h[j], h[i] }

func newMechanicHeap(ranks []int) *mechanicHeap {
	rankCount := make(map[int]int, len(ranks))
	for _, rank := range ranks {
		rankCount[rank]++
	}

	h := make(mechanicHeap, 0, len(rankCount))
	for rank, count := range rankCount {
		mech := mechanic{
			rank:  int64(rank),
			count: int64(count),
			cars:  1,
			time:  int64(rank),
		}
		h = append(h, mech)
	}
	heap.Init(&h)
	return &h
}

func (h *mechanicHeap) Push(x interface{}) {
	*h = append(*h, x.(mechanic))
}

func (h *mechanicHeap) Pop() interface{} {
	n := len(*h)
	x := (*h)[n-1]
	*h = (*h)[:n-1]
	return x
}

// Use Heap
func repairCars3(ranks []int, cars int) int64 {
	h := newMechanicHeap(ranks)
	var res int64
	for cars > 0 {
		mech := heap.Pop(h).(mechanic)
		res = mech.time
		cars -= int(mech.count)
		mech.inc()
		heap.Push(h, mech)
	}

	return res
}
