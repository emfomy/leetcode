// Source: https://leetcode.com/problems/contains-duplicate
// Title: Contains Duplicate
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer array nums, return true if any value appears at least twice in the array, and return false if every element is distinct.
//
// Example 1:
//
//   Input: nums = [1,2,3,1]
//   Output: true
//
// Example 2:
//
//   Input: nums = [1,2,3,4]
//   Output: false
//
// Example 3:
//
//   Input: nums = [1,1,1,3,3,4,3,2,4,2]
//   Output: true
//
// Constraints:
//
//   1 <= nums.length <= 10^5
//   -10^9 <= nums[i] <= 10^9
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"sort"
)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Use set; O(n) time, O(n) space
func containsDuplicate(nums []int) bool {
	n := len(nums)
	pool := make(map[int]bool, n) // set of numbers

	for _, num := range nums {
		if pool[num] {
			return true
		}
		pool[num] = true

	}

	return false
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Use sort; O(nlogn) time, O(1) space
func containsDuplicate2(nums []int) bool {
	n := len(nums)
	sort.Ints(nums)
	for i := 1; i < n; i++ {
		if nums[i-1] == nums[i] {
			return true
		}
	}
	return false
}
