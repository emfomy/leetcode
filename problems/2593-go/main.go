// Source: https://leetcode.com/problems/find-score-of-an-array-after-marking-all-elements
// Title: Find Score of an Array After Marking All Elements
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an array `nums` consisting of positive integers.
//
// Starting with `score = 0`, apply the following algorithm:
//
// - Choose the smallest integer of the array that is not marked. If there is a tie, choose the one with the smallest index.
// - Add the value of the chosen integer to `score`.
// - Mark **the chosen element and its two adjacent elements if they exist**.
// - Repeat until all the array elements are marked.
//
// Return the score you get after applying the above algorithm.
//
// **Example 1:**
//
// ```
// Input: nums = [2,1,3,4,5,2]
// Output: 7
// Explanation: We mark the elements as follows:
// - 1 is the smallest unmarked element, so we mark it and its two adjacent elements: [2,1,3,4,5,2].
// - 2 is the smallest unmarked element, so we mark it and its left adjacent element: [2,1,3,4,5,2].
// - 4 is the only remaining unmarked element, so we mark it: [2,1,3,4,5,2].
// Our score is 1 + 2 + 4 = 7.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [2,3,5,1,3,2]
// Output: 5
// Explanation: We mark the elements as follows:
// - 1 is the smallest unmarked element, so we mark it and its two adjacent elements: [2,3,5,1,3,2].
// - 2 is the smallest unmarked element, since there are two of them, we choose the left-most one, so we mark the one at index 0 and its right adjacent element: [2,3,5,1,3,2].
// - 2 is the only remaining unmarked element, so we mark it: [2,3,5,1,3,2].
// Our score is 1 + 2 + 2 = 5.
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 10^5`
// - `1 <= nums[i] <= 10^6`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"slices"
)

type pairType struct {
	num int
	idx int
}

func findScore(nums []int) int64 {
	n := len(nums)

	// Array pairs
	pairs := make([]pairType, n)
	for idx, num := range nums {
		pairs[idx].num = num
		pairs[idx].idx = idx
	}
	slices.SortFunc(pairs, func(a, b pairType) int {
		if a.num != b.num {
			return a.num - b.num
		}
		return a.idx - b.idx
	})

	// Array of marks
	marks := make([]bool, n)

	score := int64(0)
	for _, pair := range pairs {
		// Skip marked
		if marks[pair.idx] {
			continue
		}

		score += int64(pair.num)
		// marks[pair.idx] = true
		if pair.idx > 0 {
			marks[pair.idx-1] = true
		}
		if pair.idx < n-1 {
			marks[pair.idx+1] = true
		}
	}

	return score
}
