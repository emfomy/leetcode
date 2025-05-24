// Source: https://leetcode.com/problems/maximum-value-of-an-ordered-triplet-ii
// Title: Maximum Value of an Ordered Triplet II
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a **0-indexed** integer array `nums`.
//
// Return **the maximum value over all triplets of indices** `(i, j, k)` such that `i < j < k`. If all such triplets have a negative value, return `0`.
//
// The **value of a triplet of indices** `(i, j, k)` is equal to `(nums[i] - nums[j]) * nums[k]`.
//
// **Example 1:**
//
// ```
// Input: nums = [12,6,1,2,7]
// Output: 77
// Explanation: The value of the triplet (0, 2, 4) is (nums[0] - nums[2]) * nums[4] = 77.
// It can be shown that there are no ordered triplets of indices with a value greater than 77.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [1,10,3,4,19]
// Output: 133
// Explanation: The value of the triplet (1, 2, 4) is (nums[1] - nums[2]) * nums[4] = 133.
// It can be shown that there are no ordered triplets of indices with a value greater than 133.
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [1,2,3]
// Output: 0
// Explanation: The only ordered triplet of indices (0, 1, 2) has a negative value of (nums[0] - nums[1]) * nums[2] = -3. Hence, the answer would be 0.
// ```
//
// **Constraints:**
//
// - `3 <= nums.length <= 10^5`
// - `1 <= nums[i] <= 10^6`
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// O(n^3)
func maximumTripletValue(nums []int) int64 {
	n := len(nums)

	res := int64(0)
	for i := 0; i < n-2; i++ {
		for j := i + 1; j < n-1; j++ {
			for k := j + 1; k < n; k++ {
				res = max(res, int64(nums[i]-nums[j])*int64(nums[k]))
			}
		}
	}

	return res
}

// O(n^2)
func maximumTripletValue2(nums []int) int64 {
	n := len(nums)

	res := int64(0)
	imax := nums[0]
	for j := 1; j < n-1; j++ {
		for k := j + 1; k < n; k++ {
			res = max(res, int64(imax-nums[j])*int64(nums[k]))
		}
		imax = max(imax, nums[j])
	}

	return res
}

// O(n) time, O(n) space
func maximumTripletValue3(nums []int) int64 {
	n := len(nums)

	lMax := make([]int, n)
	lMax[0] = nums[0]
	for i := 1; i < n; i++ {
		lMax[i] = max(lMax[i-1], nums[i])
	}

	rMax := make([]int, n)
	rMax[n-1] = nums[n-1]
	for i := n - 2; i >= 0; i-- {
		rMax[i] = max(rMax[i+1], nums[i])
	}

	res := int64(0)
	for j := 1; j < n-1; j++ {
		res = max(res, int64(lMax[j-1]-nums[j])*int64(rMax[j+1]))
	}

	return res
}

// O(n)
func maximumTripletValue4(nums []int) int64 {
	var res, imax, dmax int64 = 0, 0, 0

	for _, num := range nums { // loop through k
		res = max(res, dmax*int64(num))
		dmax = max(dmax, imax-int64(num))
		imax = max(imax, int64(num))
	}

	return res
}
