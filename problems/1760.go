// Source: https://leetcode.com/problems/minimum-limit-of-balls-in-a-bag
// Title: Minimum Limit of Balls in a Bag
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `nums` where the `i^th` bag contains `nums[i]` balls. You are also given an integer `maxOperations`.
//
// You can perform the following operation at most `maxOperations` times:
//
// - Take any bag of balls and divide it into two new bags with a **positive ** number of balls.
//
// - For example, a bag of `5` balls can become two new bags of `1` and `4` balls, or two new bags of `2` and `3` balls.
//
// Your penalty is the **maximum**  number of balls in a bag. You want to **minimize**  your penalty after the operations.
//
// Return the minimum possible penalty after performing the operations.
//
// **Example 1:**
//
// ```
// Input: nums = [9], maxOperations = 2
// Output: 3
// Explanation:
// - Divide the bag with 9 balls into two bags of sizes 6 and 3. [**9** ] -> [6,3].
// - Divide the bag with 6 balls into two bags of sizes 3 and 3. [**6** ,3] -> [3,3,3].
// The bag with the most number of balls has 3 balls, so your penalty is 3 and you should return 3.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [2,4,8,2], maxOperations = 4
// Output: 2
// Explanation:
// - Divide the bag with 8 balls into two bags of sizes 4 and 4. [2,4,**8** ,2] -> [2,4,4,4,2].
// - Divide the bag with 4 balls into two bags of sizes 2 and 2. [2,**4** ,4,4,2] -> [2,2,2,4,4,2].
// - Divide the bag with 4 balls into two bags of sizes 2 and 2. [2,2,2,**4** ,4,2] -> [2,2,2,2,2,4,2].
// - Divide the bag with 4 balls into two bags of sizes 2 and 2. [2,2,2,2,2,**4** ,2] -> [2,2,2,2,2,2,2,2].
// The bag with the most number of balls has 2 balls, so your penalty is 2, and you should return 2.
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 10^5`
// - `1 <= maxOperations, nums[i] <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"container/heap"
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

// Say we know the solution is "size"
// Then the total number of bags will be
// Ceil[N1/size] + Ceil[N2/size] + ... + Ceil[Nn/size] = n + op
// Now we can use binary search to find the solution
func minimumSize(nums []int, maxOperations int) int {
	// Find max bag
	maxBag := 0
	for _, num := range nums {
		maxBag = max(maxBag, num)
	}

	// Binary search
	check := func(size int) bool {
		ops := 0
		for _, num := range nums {
			ops += (num - 1) / size
		}
		return ops > maxOperations
	}

	return bisectFunc(check, 1, maxBag)
}

// Use heap (TLE)

type bagType struct {
	total int // Original size
	size  int // current size of each subbag (the max one)
	split int // number of subbags
}

type bagHeap []bagType

func (h bagHeap) Len() int           { return len(h) }
func (h bagHeap) Less(i, j int) bool { return h[i].size > h[j].size } // max-heap
func (h bagHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }

func (h *bagHeap) Push(x any) {
	*h = append(*h, x.(bagType))
}

func (h *bagHeap) Pop() any {
	old := *h
	n := len(old)
	x := old[n-1]
	*h = old[0 : n-1]
	return x
}

func minimumSize2(nums []int, maxOperations int) int {
	n := len(nums)
	bags := make(bagHeap, 0, n)
	for _, num := range nums {
		bags = append(bags, bagType{
			total: num,
			size:  num,
			split: 1,
		})
	}

	heap.Init(&bags)

	for i := 0; i < maxOperations; i++ {
		bag := heap.Pop(&bags).(bagType)
		bag.split++
		bag.size = (bag.total + bag.split - 1) / bag.split
		heap.Push(&bags, bag)
	}

	return heap.Pop(&bags).(bagType).size
}
