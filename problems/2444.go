// Source: https://leetcode.com/problems/count-subarrays-with-fixed-bounds
// Title: Count Subarrays With Fixed Bounds
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `nums` and two integers `minK` and `maxK`.
//
// A **fixed-bound subarray** of `nums` is a subarray that satisfies the following conditions:
//
// - The **minimum** value in the subarray is equal to `minK`.
// - The **maximum** value in the subarray is equal to `maxK`.
//
// Return the **number** of fixed-bound subarrays.
//
// A **subarray** is a **contiguous** part of an array.
//
// **Example 1:**
//
// ```
// Input: nums = [1,3,5,2,7,5], minK = 1, maxK = 5
// Output: 2
// Explanation: The fixed-bound subarrays are [1,3,5] and [1,3,5,2].
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [1,1,1,1], minK = 1, maxK = 1
// Output: 10
// Explanation: Every subarray of nums is a fixed-bound subarray. There are 10 possible subarrays.
// ```
//
// **Constraints:**
//
// - `2 <= nums.length <= 10^5`
// - `1 <= nums[i], minK, maxK <= 10^6`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func countSubarrays(nums []int, minK int, maxK int) int64 {
	n := len(nums)

	nextMin := make([]int, n)
	nextMax := make([]int, n)
	nextOuter := make([]int, n)
	{
		minIdx, maxIdx, outerIdx := n, n, n
		for i := n - 1; i >= 0; i-- {
			num := nums[i]
			if num < minK || num > maxK {
				outerIdx = i
			}
			if num == minK {
				minIdx = i
			}
			if num == maxK {
				maxIdx = i
			}
			nextMin[i] = minIdx
			nextMax[i] = maxIdx
			nextOuter[i] = outerIdx
		}
	}

	ans := int64(0)
	left := 0
	for left < n {
		minIdx, maxIdx, outerIdx := nextMin[left], nextMax[left], nextOuter[left]
		if minIdx > maxIdx {
			minIdx, maxIdx = maxIdx, minIdx
		}
		if maxIdx < outerIdx {
			ans += int64((minIdx - left + 1) * (outerIdx - maxIdx))
		}
		left = min(minIdx, maxIdx, outerIdx) + 1
	}

	return ans
}

func countSubarrays2(nums []int, minK int, maxK int) int64 {
	n := len(nums)

	minQueue := make([]int, n)
	maxQueue := make([]int, n)
	minSize, maxSize := 0, 0

	ans := int64(0)
	left := 0
	for i, num := range nums {
		if num < minK || num > maxK {
			minSize, maxSize = 0, 0
			left = i + 1
			continue
		}

		// Pop queue
		for minSize > 0 && nums[minQueue[minSize-1]] >= num {
			minSize--
		}
		minQueue[minSize] = i
		minSize++

		for maxSize > 0 && nums[maxQueue[maxSize-1]] <= num {
			maxSize--
		}
		maxQueue[maxSize] = i
		maxSize++

		// Count
		if nums[minQueue[0]] == minK && nums[maxQueue[0]] == maxK {
			start := min(minQueue[0], maxQueue[0])
			ans += int64(start - left + 1)
		}

	}

	return ans
}

func countSubarrays3(nums []int, minK int, maxK int) int64 {
	ans := int64(0)
	left, minIdx, maxIdx := -1, -1, -1
	for i, num := range nums {
		if num < minK || num > maxK {
			left = i
		}
		if num == minK {
			minIdx = i
		}
		if num == maxK {
			maxIdx = i
		}
		ans += max(0, int64(min(minIdx, maxIdx)-left))
	}

	return ans
}
