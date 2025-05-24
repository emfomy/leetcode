// Source: https://leetcode.com/problems/target-sum
// Title: Target Sum
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `nums` and an integer `target`.
//
// You want to build an **expression** out of nums by adding one of the symbols `'+'` and `'-'` before each integer in nums and then concatenate all the integers.
//
// - For example, if `nums = [2, 1]`, you can add a `'+'` before `2` and a `'-'` before `1` and concatenate them to build the expression `"+2-1"`.
//
// Return the number of different **expressions** that you can build, which evaluates to `target`.
//
// **Example 1:**
//
// ```
// Input: nums = [1,1,1,1,1], target = 3
// Output: 5
// Explanation: There are 5 ways to assign symbols to make the sum of nums be target 3.
// -1 + 1 + 1 + 1 + 1 = 3
// +1 - 1 + 1 + 1 + 1 = 3
// +1 + 1 - 1 + 1 + 1 = 3
// +1 + 1 + 1 - 1 + 1 = 3
// +1 + 1 + 1 + 1 - 1 = 3
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [1], target = 1
// Output: 1
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 20`
// - `0 <= nums[i] <= 1000`
// - `0 <= sum(nums[i]) <= 1000`
// - `-1000 <= target <= 1000`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func findTargetSumWays(nums []int, target int) int {
	currSums := map[int]int{0: 1}

	for _, num := range nums {
		nextSums := make(map[int]int)

		for sum, count := range currSums {
			nextSums[sum+num] += count
			nextSums[sum-num] += count
		}

		currSums = nextSums
	}

	return currSums[target]
}

func findTargetSumWays2(nums []int, target int) int {
	n := len(nums)

	sums := make([][2001]int, n+1)
	sums[0][1000] = 1

	for i, num := range nums {
		for sum, count := range sums[i] {
			if sum+num <= 2000 {
				sums[i+1][sum+num] += count
			}
			if sum-num >= 0 {
				sums[i+1][sum-num] += count
			}
		}
	}

	return sums[n][1000+target]
}
