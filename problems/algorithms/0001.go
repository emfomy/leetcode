// Source: https://leetcode.com/problems/two-sum/
// Title: Two Sum
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array of integers, return indices of the two numbers such that they add up to a specific target.
//
// You may assume that each input would have exactly one solution, and you may not use the same element twice.
//
// Example:
//
//   Given nums = [2, 7, 11, 15], target = 9,
//
//   Because nums[0] + nums[1] = 2 + 7 = 9,
//   return [0, 1].
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func twoSum(nums []int, target int) []int {
	m := make(map[int]int, len(nums)) // maps target-num to index of num
	for i, num := range nums {
		if j, ok := m[num]; ok { // Check if target-num exists
			return []int{j, i}
		}
		m[target-num] = i
	}
	return nil
}
