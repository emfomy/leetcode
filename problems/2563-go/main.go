// Source: https://leetcode.com/problems/count-the-number-of-fair-pairs
// Title: Count the Number of Fair Pairs
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a **0-indexed** integer array `nums` of size `n` and two integers `lower` and `upper`, return the number of fair pairs.
//
// A pair `(i, j)` is **fair** if:
//
// - `0 <= i < j < n`, and
// - `lower <= nums[i] + nums[j] <= upper`
//
// **Example 1:**
//
// ```
// Input: nums = [0,1,7,4,4,5], lower = 3, upper = 6
// Output: 6
// Explanation: There are 6 fair pairs: (0,3), (0,4), (0,5), (1,3), (1,4), and (1,5).
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [1,7,9,2,5], lower = 11, upper = 11
// Output: 1
// Explanation: There is a single fair pair: (2,3).
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 10^5`
// - `nums.length == n`
// - `-10^9<= nums[i] <= 10^9`
// - `-10^9<= lower <= upper <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"slices"
)

func countFairPairs(nums []int, lower int, upper int) int64 {
	n := len(nums)
	slices.Sort(nums)

	res := int64(0)
	minRight, maxRight := 0, 0
	for left := n - 1; left >= 0; left-- {
		minRight = min(minRight, left)
		maxRight = min(maxRight, left)

		for minRight < left && nums[left]+nums[minRight] < lower {
			minRight++
		}
		for maxRight < left && nums[left]+nums[maxRight] <= upper {
			maxRight++
		}

		res += int64(maxRight - minRight)
	}

	return res
}

func countFairPairs2(nums []int, lower int, upper int) int64 {
	n := len(nums)
	slices.Sort(nums)

	countPairs := func(value int) int64 { // count pairs smaller thant `value`
		res := int64(0)
		left, right := 0, n-1
		for left < right {
			if nums[left]+nums[right] < value {
				res += int64(right - left)
				left++
			} else {
				right--
			}
		}
		return res
	}

	return countPairs(upper+1) - countPairs(lower)
}
