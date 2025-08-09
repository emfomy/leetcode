// Source: https://leetcode.com/problems/longest-harmonious-subsequence
// Title: Longest Harmonious Subsequence
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// We define a harmonious array as an array where the difference between its maximum value and its minimum value is **exactly** `1`.
//
// Given an integer array `nums`, return the length of its longest harmonious **subsequence** among all its possible subsequences.
//
// A **subsequence** is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
//
// **Example 1:**
//
// ```
// Input: nums = [1,3,2,2,5,2,3,7]
// Output: 5
// Explanation:
// The longest harmonious subsequence is `[3,2,2,2,3]`.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [1,2,3,4]
// Output: 2
// Explanation:
// The longest harmonious subsequences are `[1,2]`, `[2,3]`, and `[3,4]`, all of which have a length of 2.
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [1,1,1,1]
// Output: 0
// Explanation:
// No harmonic subsequence exists.
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 2 * 10^4`
// - `-10^9 <= nums[i] <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// Use hash map
func findLHS(nums []int) int {
	n := len(nums)

	// Count frequency
	freqs := make(map[int]int, n)
	for _, num := range nums {
		freqs[num]++
	}

	ans := 0
	for num, freq := range freqs {
		if freqs[num+1] > 0 {
			ans = max(ans, freq+freqs[num+1])
		}
	}

	return ans
}
