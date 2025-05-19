// Source: https://leetcode.com/problems/count-the-number-of-good-subarrays
// Title: Count the Number of Good Subarrays
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer array `nums` and an integer `k`, return the number of **good** subarrays of `nums`.
//
// A subarray `arr` is **good** if there are **at least **`k` pairs of indices `(i, j)` such that `i < j` and `arr[i] == arr[j]`.
//
// A **subarray** is a contiguous **non-empty** sequence of elements within an array.
//
// **Example 1:**
//
// ```
// Input: nums = [1,1,1,1,1], k = 10
// Output: 1
// Explanation: The only good subarray is the array nums itself.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [3,1,4,3,2,2,4], k = 2
// Output: 4
// Explanation: There are 4 different good subarrays:
// - [3,1,4,3,2,2] that has 2 pairs.
// - [3,1,4,3,2,2,4] that has 3 pairs.
// - [1,4,3,2,2,4] that has 2 pairs.
// - [4,3,2,2,4] that has 2 pairs.
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 10^5`
// - `1 <= nums[i], k <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// Two pointer
func countGood(nums []int, k int) int64 {
	n := len(nums)

	counter := make(map[int]int) // num count
	pairCount := 0               // pair count

	res := int64(0)

	right := 1
	counter[nums[0]]++
	for left := range n {
		for ; pairCount < k && right < n; right++ {
			pairCount += counter[nums[right]]
			counter[nums[right]]++
		}
		if pairCount < k {
			break
		}

		res += int64(n - right + 1)

		counter[nums[left]]--
		pairCount -= counter[nums[left]]
	}

	return res
}
