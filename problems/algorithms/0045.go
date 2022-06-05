// Source: https://leetcode.com/problems/jump-game-ii/
// Title: Jump Game II
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array of non-negative integers nums, you are initially positioned at the first index of the array.
//
// Each element in the array represents your maximum jump length at that position.
//
// Your goal is to reach the last index in the minimum number of jumps.
//
// You can assume that you can always reach the last index.
//
// Example 1:
//
//   Input: nums = [2,3,1,1,4]
//   Output: 2
//   Explanation: The minimum number of jumps to reach the last index is 2. Jump 1 step from index 0 to 1, then 3 steps to the last index.
//
// Example 2:
//
//   Input: nums = [2,3,0,1,4]
//   Output: 2
//
// Constraints:
//
//   1 <= nums.length <= 10^4
//   0 <= nums[i] <= 1000
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func jump1(nums []int) int {
	target := len(nums) - 1
	if target == 0 {
		return 0
	}

	step := 0
	currMax := 0 // max reachable index
	prevMax := 0 // max reachable index in (step-1) steps
	for i, num := range nums {
		currMax = _max(currMax, i+num)
		if i == prevMax {
			step++
			prevMax = currMax
			if currMax >= target {
				break
			}
		}
	}

	return step
}

func _max(a, b int) int {
	if a > b {
		return a
	}
	return b
}
