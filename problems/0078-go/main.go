// Source: https://leetcode.com/problems/subsets
// Title: Subsets
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer array nums of unique elements, return all possible subsets (the power set).
//
// The solution set must not contain duplicate subsets. Return the solution in any order.
//
// Example 1:
//
//   Input: nums = [1,2,3]
//   Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
//
// Example 2:
//
//   Input: nums = [0]
//   Output: [[],[0]]
//
// Constraints:
//
//   1 <= nums.length <= 10
//   -10 <= nums[i] <= 10
//   All the numbers of nums are unique.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func subsets(nums []int) [][]int {
	m := 1 << len(nums)
	res := make([][]int, 0, m)
	for mask := 0; mask < m; mask++ {
		res = append(res, _subset(nums, mask))
	}
	return res
}

func _subset(nums []int, mask int) []int {
	res := make([]int, 0, len(nums))
	for i, num := range nums {
		if mask&(1<<i) != 0 {
			res = append(res, num)
		}
	}
	return res
}
