// Source: https://leetcode.com/problems/longest-consecutive-sequence
// Title: Longest Consecutive Sequence
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an unsorted array of integers `nums`, return the length of the longest consecutive elements sequence.
//
// You must write an algorithm that runs in `O(n)` time.
//
// **Example 1:**
//
// ```
// Input: nums = [100,4,200,1,3,2]
// Output: 4
// Explanation: The longest consecutive elements sequence is `[1, 2, 3, 4]`. Therefore its length is 4.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [0,3,7,2,5,8,4,6,0,1]
// Output: 9
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [1,0,1,2]
// Output: 3
// ```
//
// **Constraints:**
//
// - `0 <= nums.length <= 10^5`
// - `-10^9 <= nums[i] <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// Use hash map
func longestConsecutive(nums []int) int {
	numSet := make(map[int]bool, len(nums))

	for _, num := range nums {
		numSet[num] = true
	}

	ans := 0
	for num := range numSet {
		if !numSet[num-1] {
			val := num + 1
			for ; numSet[val]; val++ {
			}
			ans = max(ans, val-num)
		}
	}

	return ans
}
