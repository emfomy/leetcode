// Source: https://leetcode.com/problems/maximum-erasure-value
// Title: Maximum Erasure Value
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an array of positive integers `nums` and want to erase a subarray containing**unique elements**. The **score** you get by erasing the subarray is equal to the **sum** of its elements.
//
// Return the **maximum score** you can get by erasing **exactly one** subarray.
//
// An array `b` is called to be a subarray of `a` if it forms a contiguous subsequence of `a`, that is, if it is equal to `a[l],a[l+1],...,a[r]` for some `(l,r)`.
//
// **Example 1:**
//
// ```
// Input: nums = [4,2,4,5,6]
// Output: 17
// Explanation: The optimal subarray here is [2,4,5,6].
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [5,2,1,2,5,2,1,2,5]
// Output: 8
// Explanation: The optimal subarray here is [5,2,1] or [1,2,5].
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 10^5`
// - `1 <= nums[i] <= 10^4`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// Two Pointer + Set
func maximumUniqueSubarray(nums []int) int {
	numSet := make(map[int]bool)

	n := len(nums)
	i, j := 0, 0
	sum := 0
	ans := 0
	for j < n {
		num := nums[j]
		if !numSet[num] {
			numSet[num] = true
			sum += num
			ans = max(ans, sum)
			j++
		} else {
			sum -= nums[i]
			numSet[nums[i]] = false
			i++
		}
	}

	return ans
}

// Two Pointer + Set(Array)
func maximumUniqueSubarray2(nums []int) int {
	numSet := [10001]bool{}

	n := len(nums)
	i, j := 0, 0
	sum := 0
	ans := 0
	for j < n {
		num := nums[j]
		if !numSet[num] {
			numSet[num] = true
			sum += num
			ans = max(ans, sum)
			j++
		} else {
			sum -= nums[i]
			numSet[nums[i]] = false
			i++
		}
	}

	return ans
}
