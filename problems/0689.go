// Source: https://leetcode.com/problems/maximum-sum-of-3-non-overlapping-subarrays
// Title: Maximum Sum of 3 Non-Overlapping Subarrays
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer array `nums` and an integer `k`, find three non-overlapping subarrays of length `k` with maximum sum and return them.
//
// Return the result as a list of indices representing the starting position of each interval (**0-indexed** ). If there are multiple answers, return the lexicographically smallest one.
//
// **Example 1:**
//
// ```
// Input: nums = [1,2,1,2,6,7,5,1], k = 2
// Output: [0,3,5]
// Explanation: Subarrays [1, 2], [2, 6], [7, 5] correspond to the starting indices [0, 3, 5].
// We could have also taken [2, 1], but an answer of [1, 3, 5] would be lexicographically larger.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [1,2,1,2,1,2,1,2,1], k = 2
// Output: [0,2,4]
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 2 * 10^4`
// - `1 <= nums[i] <2^16`
// - `1 <= k <= floor(nums.length / 3)`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// Use 2-D DP
//
// DP[0][i] stores max subarray before i
// DP[1][i] stores max double subarraies before i
// DP[2][i] stores max triple subarraies before i
func maxSumOfThreeSubarrays(nums []int, k int) []int {
	n := len(nums) - k + 1
	for i := 0; i < n; i++ {
		for j := 1; j < k; j++ {
			nums[i] += nums[i+j]
		}
	}
	sums := nums[:n] // reuse memory

	dpSum := make([][]int, 3)
	dpIdx := make([][]int, 3)
	for i := 0; i < 3; i++ {
		dpSum[i] = make([]int, n)
		dpIdx[i] = make([]int, n)
	}

	dpSum[0][0] = sums[0]
	dpIdx[0][0] = 0
	for i := 1; i < n; i++ {
		sum := sums[i]
		if sum > dpSum[0][i-1] {
			dpSum[0][i] = sum
			dpIdx[0][i] = i
		} else {
			dpSum[0][i] = dpSum[0][i-1]
			dpIdx[0][i] = dpIdx[0][i-1]
		}
	}

	dpSum[1][k] = sums[k] + dpSum[0][0]
	dpIdx[1][k] = k
	for i := k + 1; i < n; i++ {
		sum := sums[i] + dpSum[0][i-k]
		if sum > dpSum[1][i-1] {
			dpSum[1][i] = sum
			dpIdx[1][i] = i
		} else {
			dpSum[1][i] = dpSum[1][i-1]
			dpIdx[1][i] = dpIdx[1][i-1]
		}
	}

	dpSum[2][2*k] = sums[2*k] + dpSum[1][k]
	dpIdx[2][2*k] = 2 * k
	for i := 2*k + 1; i < n; i++ {
		sum := sums[i] + dpSum[1][i-k]
		if sum > dpSum[2][i-1] {
			dpSum[2][i] = sum
			dpIdx[2][i] = i
		} else {
			dpSum[2][i] = dpSum[2][i-1]
			dpIdx[2][i] = dpIdx[2][i-1]
		}
	}

	res := [3]int{}
	res[2] = dpIdx[2][n-1]
	res[1] = dpIdx[1][dpIdx[2][res[2]]-k]
	res[0] = dpIdx[0][dpIdx[1][res[1]]-k]

	return res[:]
}

// Use 1D DP
//
// DP[0] = max subarray before current idx
// DP[1] = max double subarray before current idx
// DP[2] = max triple subarray before current idx
func maxSumOfThreeSubarrays2(nums []int, k int) []int {
	n := len(nums) - k + 1
	for i := 0; i < n; i++ {
		for j := 1; j < k; j++ {
			nums[i] += nums[i+j]
		}
	}
	sums := nums[:n] // reuse memory

	dp0 := sums[0]
	dp1 := dp0 + sums[k]
	dp2 := dp1 + sums[2*k]

	idx0 := [1]int{0}
	idx1 := [2]int{0, k}
	idx2 := [3]int{0, k, 2 * k}

	m := n - 2*k
	for i := 1; i < m; i++ {
		sum0 := sums[i]
		if sum0 > dp0 {
			dp0 = sum0
			idx0[0] = i
		}

		sum1 := sums[i+k] + dp0
		if sum1 > dp1 {
			dp1 = sum1
			idx1[0] = idx0[0]
			idx1[1] = i + k
		}

		sum2 := sums[i+2*k] + dp1
		if sum2 > dp2 {
			dp2 = sum2
			idx2[0] = idx1[0]
			idx2[1] = idx1[1]
			idx2[2] = i + 2*k
		}
	}

	return idx2[:]
}

func maxSumOfThreeSubarrays3(nums []int, k int) []int {
	n := len(nums) - k + 1
	sums := make([]int, n)
	for i := 0; i < k; i++ {
		sums[0] += nums[i]
	}
	for i := 1; i < n; i++ {
		sums[i] = sums[i-1] - nums[i-1] + nums[i+k-1]
	}

	leftIdxs := make([]int, n) // max array idx before i
	{
		sum := 0
		idx := 0
		for i := 0; i < n; i++ {
			if sums[i] > sum {
				sum = sums[i]
				idx = i
			}
			leftIdxs[i] = idx
		}
	}

	rightIdxs := make([]int, n) // max array idx after i
	rightIdxs[n-1] = n - 1
	{
		sum := sums[n-1]
		idx := n - 1
		for i := n - 2; i >= 0; i-- {
			if sums[i] >= sum {
				sum = sums[i]
				idx = i
			}
			rightIdxs[i] = idx
		}
	}

	res := [3]int{}
	{
		sum := 0
		for i := k; i < n-k; i++ {
			sum0 := sums[leftIdxs[i-k]]
			sum1 := sums[i]
			sum2 := sums[rightIdxs[i+k]]
			if sum0+sum1+sum2 > sum {
				sum = sum0 + sum1 + sum2
				res[0] = leftIdxs[i-k]
				res[1] = i
				res[2] = rightIdxs[i+k]
			}
		}
	}

	return res[:]
}
