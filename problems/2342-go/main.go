// Source: https://leetcode.com/problems/max-sum-of-a-pair-with-equal-sum-of-digits
// Title: Max Sum of a Pair With Equal Sum of Digits
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a **0-indexed** array `nums` consisting of **positive** integers. You can choose two indices `i` and `j`, such that `i != j`, and the sum of digits of the number `nums[i]` is equal to that of `nums[j]`.
//
// Return the **maximum** value of `nums[i] + nums[j]` that you can obtain over all possible indices `i` and `j` that satisfy the conditions.
//
// **Example 1:**
//
// ```
// Input: nums = [18,43,36,13,7]
// Output: 54
// Explanation: The pairs (i, j) that satisfy the conditions are:
// - (0, 2), both numbers have a sum of digits equal to 9, and their sum is 18 + 36 = 54.
// - (1, 4), both numbers have a sum of digits equal to 7, and their sum is 43 + 7 = 50.
// So the maximum sum that we can obtain is 54.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [10,12,19,14]
// Output: -1
// Explanation: There are no two numbers that satisfy the conditions, so we return -1.
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 10^5`
// - `1 <= nums[i] <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// Note that the max hash is hash(999999999)=81
func maximumSum(nums []int) int {
	maxHash := make([]int, 82) // max value for each hash

	hash := func(num int) int {
		h := 0
		for num > 0 {
			h += num % 10
			num /= 10
		}
		return h
	}

	res := -1
	for _, num := range nums {
		h := hash(num)
		mNum := maxHash[h]
		if mNum == 0 {
			maxHash[h] = num
			continue
		}
		maxHash[h] = max(mNum, num)
		res = max(res, num+mNum)
	}

	return res
}
