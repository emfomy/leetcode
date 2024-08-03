// Source: https://leetcode.com/problems/house-robber
// Title: House Robber
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security systems connected and it will automatically contact the police if two adjacent houses were broken into on the same night.
//
// Given an integer array nums representing the amount of money of each house, return the maximum amount of money you can rob tonight without alerting the police.
//
// Example 1:
//
//   Input: nums = [1,2,3,1]
//   Output: 4
//   Explanation:
//     Rob house 1 (money = 1) and then rob house 3 (money = 3).
//     Total amount you can rob = 1 + 3 = 4.
//
// Example 2:
//
//   Input: nums = [2,7,9,3,1]
//   Output: 12
//   Explanation:
//     Rob house 1 (money = 2), rob house 3 (money = 9) and rob house 5 (money = 1).
//     Total amount you can rob = 2 + 9 + 1 = 12.
//
// Constraints:
//
//   1 <= nums.length <= 100
//   0 <= nums[i] <= 400
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// Let M(i) be the amoount of money in house i
// Let R(i) be the max money if you rob house i
// Let N(i) be the max money if you don't rob house i
// R(i) = M(i) + N(i-1)
// N(i) = max(R(i-1), N(i-1))
func rob(nums []int) int {
	r := 0
	n := 0

	for _, m := range nums {
		r, n = m+n, _max(r, n)
	}
	return _max(r, n)
}

func _max(a, b int) int {
	if a > b {
		return a
	}
	return b
}
