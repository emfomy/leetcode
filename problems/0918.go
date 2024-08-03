// Source: https://leetcode.com/problems/maximum-sum-circular-subarray
// Title: Maximum Sum Circular Subarray
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a circular integer array nums of length n, return the maximum possible sum of a non-empty subarray of nums.
//
// A circular array means the end of the array connects to the beginning of the array. Formally, the next element of nums[i] is nums[(i + 1) % n] and the previous element of nums[i] is nums[(i - 1 + n) % n].
//
// A subarray may only include each element of the fixed buffer nums at most once. Formally, for a subarray nums[i], nums[i + 1], ..., nums[j], there does not exist i <= k1, k2 <= j with k1 % n == k2 % n.
//
// Example 1:
//
//   Input: nums = [1,-2,3,-2]
//   Output: 3
//   Explanation: Subarray [3] has maximum sum 3.
//
// Example 2:
//
//   Input: nums = [5,-3,5]
//   Output: 10
//   Explanation: Subarray [5,5] has maximum sum 5 + 5 = 10.
//
// Example 3:
//
//   Input: nums = [-3,-2,-3]
//   Output: -2
//   Explanation: Subarray [-2] has maximum sum -2.
//
// Constraints:
//
//   n == nums.length
//   1 <= n <= 3 * 10^4
//   -3 * 10^4 <= nums[i] <= 3 * 10^4
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// The sum of a subarray pass the ends is equal to the total sum minus the sum of the complement array.
func maxSubarraySumCircular(nums []int) int {
	// Get sum of total array
	sum := nums[0]
	maxVal := nums[0]
	for _, num := range nums[1:] {
		sum += num
		maxVal = _max(maxVal, num)
	}

	if maxVal < 0 { // all negative
		return maxVal
	}

	maxSum := _maxSubArray(nums) // Get max subarray
	minSum := _minSubArray(nums) // Get min subarray

	return _max(maxSum, sum-minSum)
}

// See P53
func _maxSubArray(nums []int) int {
	maxGlobal := nums[0]
	maxEndHere := nums[0]

	for _, num := range nums[1:] {
		maxEndHere = _max(maxEndHere+num, num)
		maxGlobal = _max(maxGlobal, maxEndHere)
	}

	return maxGlobal
}

// Get min subarray
func _minSubArray(nums []int) int {
	minGlobal := nums[0]
	minEndHere := nums[0]

	for _, num := range nums[1:] {
		minEndHere = _min(minEndHere+num, num)
		minGlobal = _min(minGlobal, minEndHere)
	}

	return minGlobal
}

func _max(a, b int) int {
	if a > b {
		return a
	}
	return b
}

func _min(a, b int) int {
	if a < b {
		return a
	}
	return b
}
