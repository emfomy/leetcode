// Source: https://leetcode.com/problems/k-empty-slots
// Title: K Empty Slots
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You have `n` bulbs in a row numbered from `1` to `n`. Initially, all the bulbs are turned off. We turn on **exactly one** bulb every day until all bulbs are on after `n` days.
//
// You are given an array `bulbs`of length `n`where `bulbs[i] = x` means that on the `(i+1)^th` day, we will turn on the bulb at position `x`where`i`is**0-indexed**and`x`is**1-indexed.**
//
// Given an integer `k`, return the **minimum day number** such that there exists two **turned on** bulbs that have **exactly**`k` bulbs between them that are **all turned off**. If there isn't such day, return `-1`.
//
// **Example 1:**
//
// ```
// Input: bulbs = [1,3,2], k = 1
// Output: 2
// Explanation:
// On the first day: bulbs[0] = 1, first bulb is turned on: [1,0,0]
// On the second day: bulbs[1] = 3, third bulb is turned on: [1,0,1]
// On the third day: bulbs[2] = 2, second bulb is turned on: [1,1,1]
// We return 2 because on the second day, there were two on bulbs with one off bulb between them.```
//
// **Example 2:**
//
// ```
// Input: bulbs = [1,2,3], k = 1
// Output: -1
// ```
//
// **Constraints:**
//
// - `n == bulbs.length`
// - `1 <= n <= 2 * 10^4`
// - `1 <= bulbs[i] <= n`
// - `bulbs`is a permutation of numbers from`1`to`n`.
// - `0 <= k <= 2 * 10^4`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"github.com/emirpasic/gods/v2/trees/redblacktree"
)

// Brute-force
func kEmptySlots(bulbs []int, k int) int {
	n := len(bulbs)

	on := make([]bool, n+1)

	checkLeft := func(curr int) bool {
		left := curr - k - 1
		if left < 1 {
			return false
		}
		if !on[left] {
			return false
		}
		for i := left + 1; i < curr; i++ {
			if on[i] {
				return false
			}
		}
		return true
	}
	checkRight := func(curr int) bool {
		right := curr + k + 1
		if right > n {
			return false
		}
		if !on[right] {
			return false
		}
		for i := curr + 1; i < right; i++ {
			if on[i] {
				return false
			}
		}
		return true
	}

	for day, bulb := range bulbs {
		on[bulb] = true
		if checkLeft(bulb) || checkRight(bulb) {
			return day + 1
		}
	}

	return -1
}

// Use tree
func kEmptySlots2(bulbs []int, k int) int {
	type void struct{}
	tree := redblacktree.New[int, void]()
	for day, bulb := range bulbs {
		tree.Put(bulb, void{})
		if left, ok := tree.Floor(bulb - 1); ok && (bulb-left.Key-1 == k) {
			return day + 1
		}
		if right, ok := tree.Ceiling(bulb + 1); ok && (right.Key-bulb-1 == k) {
			return day + 1
		}
	}

	return -1
}

// Track the day that bulb turns on
// Let days[b] = d be the time that `b`-th bulb turns on.
func kEmptySlots3(bulbs []int, k int) int {
	n := len(bulbs)
	days := make([]int, n) // bulb -> day
	for day, bulb := range bulbs {
		days[bulb-1] = day + 1
	}

	// Check if everything between days[bulb] and days[bulb+k+1] are larger
	check := func(bulb int, day int) bool {
		for j := bulb + 1; j <= bulb+k; j++ {
			if days[j] < day {
				return false
			}
		}
		return true
	}
	ans := n + 1
	for bulb := range n - k - 1 {
		day := max(days[bulb], days[bulb+k+1])
		if check(bulb, day) {
			ans = min(ans, day)
		}
	}

	if ans == n+1 {
		return -1
	}
	return ans
}
