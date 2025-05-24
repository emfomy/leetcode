// Source: https://leetcode.com/problems/maximum-erasure-value
// Title: Maximum Erasure Value
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an array of positive integers nums and want to erase a subarray containing unique elements. The score you get by erasing the subarray is equal to the sum of its elements.
//
// Return the maximum score you can get by erasing exactly one subarray.
//
// An array b is called to be a subarray of a if it forms a contiguous subsequence of a, that is, if it is equal to a[l],a[l+1],...,a[r] for some (l,r).
//
// Example 1:
//
//   Input: nums = [4,2,4,5,6]
//   Output: 17
//   Explanation: The optimal subarray here is [2,4,5,6].
//
// Example 2:
//
//   Input: nums = [5,2,1,2,5,2,1,2,5]
//   Output: 8
//   Explanation: The optimal subarray here is [5,2,1] or [1,2,5].
//
// Constraints:
//
//   1 <= nums.length <= 10^5
//   1 <= nums[i] <= 10^4
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

type void struct{}

func maximumUniqueSubarray(nums []int) int {
	pool := make(map[int]void)
	i := 0 // start index of substring
	j := 0 // end index of substring
	n := len(nums)

	maxSum := 0
	sum := 0

	for j < n {
		if _, ok := pool[nums[j]]; !ok { // no repeating number
			pool[nums[j]] = void{}
			sum += nums[j]
			j += 1
			maxSum = _max(maxSum, sum)
		} else {
			delete(pool, nums[i])
			sum -= nums[i]
			i += 1
		}
	}
	return maxSum
}

func _max(a, b int) int {
	if a > b {
		return a
	}
	return b
}
