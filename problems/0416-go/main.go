// Source: https://leetcode.com/problems/partition-equal-subset-sum
// Title: Partition Equal Subset Sum
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer array `nums`, return `true` if you can partition the array into two subsets such that the sum of the elements in both subsets is equal or `false` otherwise.
//
// **Example 1:**
//
// ```
// Input: nums = [1,5,11,5]
// Output: true
// Explanation: The array can be partitioned as [1, 5, 5] and [11].
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [1,2,3,5]
// Output: false
// Explanation: The array cannot be partitioned into equal sum subsets.
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 200`
// - `1 <= nums[i] <= 100`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func canPartition(nums []int) bool {
	sum := 0
	for _, num := range nums {
		sum += num
	}
	if sum%2 != 0 {
		return false
	}
	halfsum := sum / 2

	possibleSums := make([]bool, halfsum+1)
	possibleSums[0] = true

	for _, num := range nums {
		for i := halfsum; i >= num; i-- {
			possibleSums[i] = possibleSums[i] || possibleSums[i-num]
		}
	}

	return possibleSums[halfsum]
}
