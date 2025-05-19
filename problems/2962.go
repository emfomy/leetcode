// Source: https://leetcode.com/problems/count-subarrays-where-max-element-appears-at-least-k-times
// Title: Count Subarrays Where Max Element Appears at Least K Times
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `nums` and a **positive** integer `k`.
//
// Return the number of subarrays where the **maximum** element of `nums` appears **at least** `k` times in that subarray.
//
// A **subarray** is a contiguous sequence of elements within an array.
//
// **Example 1:**
//
// ```
// Input: nums = [1,3,2,3,3], k = 2
// Output: 6
// Explanation: The subarrays that contain the element 3 at least 2 times are: [1,3,2,3], [1,3,2,3,3], [3,2,3], [3,2,3,3], [2,3,3] and [3,3].
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [1,4,2,1], k = 3
// Output: 0
// Explanation: No subarray contains the element 4 at least 3 times.
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 10^5`
// - `1 <= nums[i] <= 10^6`
// - `1 <= k <= 10^5`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// Queue
func countSubarrays(nums []int, k int) int64 {
	maxNum := 0
	for _, num := range nums {
		maxNum = max(maxNum, num)
	}

	queue := make([]int, 0)
	ans := 0
	for i, num := range nums {
		if num == maxNum {
			queue = append(queue, i)
		}

		if len(queue) > k {
			queue = queue[1:]
		}
		if len(queue) == k {
			ans += queue[0] + 1
		}
	}

	return int64(ans)
}

// Two pointer
func countSubarrays2(nums []int, k int) int64 {
	maxNum := 0
	for _, num := range nums {
		maxNum = max(maxNum, num)
	}

	ans, count, left := 0, 0, 0
	for _, num := range nums {
		if num == maxNum {
			count++
		}

		for count >= k {
			if nums[left] == maxNum {
				count--
			}
			left++
		}

		ans += left
	}

	return int64(ans)
}
