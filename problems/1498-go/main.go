// Source: https://leetcode.com/problems/number-of-subsequences-that-satisfy-the-given-sum-condition
// Title: Number of Subsequences That Satisfy the Given Sum Condition
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an array of integers `nums` and an integer `target`.
//
// Return the number of **non-empty** subsequences of `nums` such that the sum of the minimum and maximum element on it is less or equal to `target`. Since the answer may be too large, return it **modulo** `10^9 + 7`.
//
// **Example 1:**
//
// ```
// Input: nums = [3,5,6,7], target = 9
// Output: 4
// Explanation: There are 4 subsequences that satisfy the condition.
// [3] -> Min value + max value <= target (3 + 3 <= 9)
// [3,5] -> (3 + 5 <= 9)
// [3,5,6] -> (3 + 6 <= 9)
// [3,6] -> (3 + 6 <= 9)
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [3,3,6,8], target = 10
// Output: 6
// Explanation: There are 6 subsequences that satisfy the condition. (nums can have repeated numbers).
// [3] , [3] , [3,3], [3,6] , [3,6] , [3,3,6]
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [2,3,3,4,6,7], target = 12
// Output: 61
// Explanation: There are 63 non-empty subsequences, two of them do not satisfy the condition ([6,7], [7]).
// Number of valid subsequences (63 - 2 = 61).
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 10^5`
// - `1 <= nums[i] <= 10^6`
// - `1 <= target <= 10^6`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"slices"
)

const modulo = int(1e9 + 7)

// Precompute all possible power of 2
const P = int(1e5)

var POW2 = [P + 1]int{}

func init() {
	POW2[0] = 1
	for p := range P {
		POW2[p+1] = (POW2[p] << 1) % modulo
	}
}

// First we count the frequency, and compute the pre-sum of the frequencies.
// Use two pointer to find min-max pairs that satisfy the condition.
//
// Say we have (i, j) with nums[i]+nums[j] <= target.
// We fix nums[i] to be always been chosen, and freely choose from (i, j].
// There are 2^(j-i) possible such subsequences.
func numSubseq(nums []int, target int) int {
	n := len(nums)
	slices.Sort(nums)

	ans := 0
	left, right := 0, n-1
	for left <= right {
		if nums[left]+nums[right] <= target {
			ans += POW2[right-left]
			ans %= modulo
			left++
		} else {
			right--
		}
	}

	return ans
}
