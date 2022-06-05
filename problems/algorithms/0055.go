// Source: https://leetcode.com/problems/jump-game/
// Title: Jump Game
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array of non-negative integers, you are initially positioned at the first index of the array.
//
// Each element in the array represents your maximum jump length at that position.
//
// Determine if you are able to reach the last index.
//
// Example 1:
//
//   Input: nums = [2,3,1,1,4]
//   Output: true
//   Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.
//
// Example 2:
//
//   Input: nums = [3,2,1,0,4]
//   Output: false
//   Explanation: You will always arrive at index 3 no matter what. Its maximum jump length is 0, which makes it impossible to reach the last index.
//
// Constraints:
//
//   1 <= nums.length <= 10^4
//   0 <= nums[i] <= 1000
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func canJump(nums []int) bool {
	currMax := 0
	for i, num := range nums {
		if i > currMax { // We can't reach here
			return false
		}
		currMax = _max(currMax, i+num)
	}
	return true
}

func canJump2(nums []int) bool {
	l := len(nums)
	currMax := 0
	for i := 0; i < l && i <= currMax; i++ {
		currMax = _max(currMax, i+nums[i])
		if currMax >= l-1 { // We reached the target
			return true
		}
	}
	return false
}

func _max(a, b int) int {
	if a > b {
		return a
	}
	return b
}
