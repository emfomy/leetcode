// Source: https://leetcode.com/problems/minimize-the-maximum-difference-of-pairs
// Title: Minimize the Maximum Difference of Pairs
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a **0-indexed** integer array `nums` and an integer `p`. Find `p` pairs of indices of `nums` such that the **maximum** difference amongst all the pairs is **minimized**. Also, ensure no index appears more than once amongst the `p` pairs.
//
// Note that for a pair of elements at the index `i` and `j`, the difference of this pair is `|nums[i] - nums[j]|`, where `|x|` represents the **absolute** **value** of `x`.
//
// Return the **minimum** **maximum** difference among all `p` pairs. We define the maximum of an empty set to be zero.
//
// **Example 1:**
//
// ```
// Input: nums = [10,1,2,7,1,3], p = 2
// Output: 1
// Explanation: The first pair is formed from the indices 1 and 4, and the second pair is formed from the indices 2 and 5.
// The maximum difference is max(|nums[1] - nums[4]|, |nums[2] - nums[5]|) = max(0, 1) = 1. Therefore, we return 1.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [4,2,1,2], p = 1
// Output: 0
// Explanation: Let the indices 1 and 3 form a pair. The difference of that pair is |2 - 2| = 0, which is the minimum we can attain.
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 10^5`
// - `0 <= nums[i] <= 10^9`
// - `0 <= p <= (nums.length)/2`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"slices"
)

// Use DP, TLE
//
// First sort the array.
// Define dp(x, i) be the solution of nums[:i] with x pairs
// dp(x, i) = min(
// . dp(x, i-1)                                 // exclude last number
// . max(dp(x-1, i-2), |nums[i-1] - nums[i-2]|) // include last number (i.e. last pair)
// )
// Note that dp(0, i)    = 0   (no pair)
// Note that dp(x, i<2x) = INF (not enough numbers)
func minimizeMax(nums []int, p int) int {
	const INF = 1e10

	n := len(nums)
	slices.Sort(nums)

	prev := make([]int, n+1) // dp[x-1]
	curr := make([]int, n+1) // dp[x]

	// Initialize dp(0, x>0)
	for x := 1; x <= p; x++ {
		curr, prev = prev, curr
		for i := range 2 * x {
			curr[i] = INF
		}
		for i := 2 * x; i <= n; i++ {
			curr[i] = min(
				curr[i-1],
				max(prev[i-2], nums[i-1]-nums[i-2]),
			)
		}
	}

	return curr[n]
}

// Use DP
//
// Same as above.
// Note that the answer is dp(p, n), which requires dp(p-1, n-2).
// We don't need dp(p-1, i>n-2).
//
// We can simplify the problem by only compute dp(x, 2(x-1)) ~ dp(x, n-2(p-x))
func minimizeMax2(nums []int, p int) int {
	const INF = 1e10

	n := len(nums)
	slices.Sort(nums)

	prev := make([]int, n+1) // dp[x-1]
	curr := make([]int, n+1) // dp[x]

	// Initialize dp(0, x>0)
	for x := 1; x <= p; x++ {
		curr, prev = prev, curr
		curr[2*x-2] = INF
		curr[2*x-1] = INF
		for i := 2 * x; i <= n-2*(p-x); i++ {
			curr[i] = min(
				curr[i-1],
				max(prev[i-2], nums[i-1]-nums[i-2]),
			)
		}
	}

	return curr[n]
}

// Use Binary Search
func minimizeMax3(nums []int, p int) int {
	if p == 0 {
		return 0
	}

	n := len(nums)
	slices.Sort(nums)
	check := func(x int) bool { // check if there are p pairs shorter than x
		count := 0
		for i := 0; i < n-1; i++ {
			if nums[i+1]-nums[i] <= x {
				count++
				if count == p {
					return true
				}
				i++ // skip next number
			}
		}
		return false
	}

	// fn(lo-1) = false, fn(lo=hi) = true
	lo, hi := 0, nums[n-1]-nums[0]
	for lo < hi { // find in range [lo, hi)
		mid := lo + (hi-lo)/2
		if check(mid) {
			hi = mid // go to range [lo, mid)
		} else {
			lo = mid + 1 // go to range [mid+1, hi)
		}
	}
	return lo
}
