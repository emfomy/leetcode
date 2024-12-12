// Source: https://leetcode.com/problems/take-gifts-from-the-richest-pile
// Title: Take Gifts From the Richest Pile
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `gifts` denoting the number of gifts in various piles. Every second, you do the following:
//
// - Choose the pile with the maximum number of gifts.
// - If there is more than one pile with the maximum number of gifts, choose any.
// - Leave behind the floor of the square root of the number of gifts in the pile. Take the rest of the gifts.
//
// Return the number of gifts remaining after `k` seconds.
//
// **Example 1:**
//
// ```
// Input: gifts = [25,64,9,4,100], k = 4
// Output: 29
// Explanation:
// The gifts are taken in the following way:
// - In the first second, the last pile is chosen and 10 gifts are left behind.
// - Then the second pile is chosen and 8 gifts are left behind.
// - After that the first pile is chosen and 5 gifts are left behind.
// - Finally, the last pile is chosen again and 3 gifts are left behind.
// The final remaining gifts are [5,8,9,4,3], so the total number of gifts remaining is 29.
// ```
//
// **Example 2:**
//
// ```
// Input: gifts = [1,1,1,1], k = 4
// Output: 4
// Explanation:
// In this case, regardless which pile you choose, you have to leave behind 1 gift in each pile.
// That is, you can't take any pile with you.
// So, the total gifts remaining are 4.
// ```
//
// **Constraints:**
//
// - `1 <= gifts.length <= 10^3`
// - `1 <= gifts[i] <= 10^9`
// - `1 <= k <= 10^3`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"container/heap"
	"math"
)

type intHeap []int

func (h intHeap) Len() int           { return len(h) }
func (h intHeap) Less(i, j int) bool { return h[i] > h[j] } // max-heap
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

func pickGifts(gifts []int, k int) int64 {
	h := newIntHeap(gifts)

	for i := 0; i < k; i++ {
		gift := heap.Pop(h).(int)
		left := int(math.Sqrt(float64(gift)))
		heap.Push(h, left)
	}

	res := int64(0)
	for _, gift := range gifts {
		res += int64(gift)
	}
	return res
}
