// Source: https://leetcode.com/problems/count-number-of-bad-pairs
// Title: Count Number of Bad Pairs
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a **0-indexed** integer array `nums`. A pair of indices `(i, j)` is a **bad pair** if `i < j` and `j - i != nums[j] - nums[i]`.
//
// Return the total number of **bad pairs** in `nums`.
//
// **Example 1:**
//
// ```
// Input: nums = [4,1,3,3]
// Output: 5
// Explanation: The pair (0, 1) is a bad pair since 1 - 0 != 1 - 4.
// The pair (0, 2) is a bad pair since 2 - 0 != 3 - 4, 2 != -1.
// The pair (0, 3) is a bad pair since 3 - 0 != 3 - 4, 3 != -1.
// The pair (1, 2) is a bad pair since 2 - 1 != 3 - 1, 1 != 2.
// The pair (2, 3) is a bad pair since 3 - 2 != 3 - 3, 1 != 0.
// There are a total of 5 bad pairs, so we return 5.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [1,2,3,4,5]
// Output: 0
// Explanation: There are no bad pairs.
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 10^5`
// - `1 <= nums[i] <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// We find good pair instead.
// IF (i, j) is good, then (nums[i]-i) = (nums[j]-j).
// If (i, j) is good and (j, k) is good, then (i, k) is good.
// That is, (nums[i]-i) = (nums[j]-j) = (nums[k]-k).
// Therefore we can group numbers into equivalence classes.
func countBadPairs(nums []int) int64 {
	n := len(nums)

	classCount := make(map[int]int64, n)

	for i, num := range nums {
		classCount[num-i]++
	}

	badCount := int64(n) * int64(n-1) / 2
	for _, size := range classCount {
		badCount -= size * (size - 1) / 2
	}

	return badCount
}
