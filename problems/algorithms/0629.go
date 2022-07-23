// Source: https://leetcode.com/problems/k-inverse-pairs-array/
// Title: K Inverse Pairs Array
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// For an integer array nums, an inverse pair is a pair of integers [i, j] where 0 <= i < j < nums.length and nums[i] > nums[j].
//
// Given two integers n and k, return the number of different arrays consist of numbers from 1 to n such that there are exactly k inverse pairs. Since the answer can be huge, return it modulo 10^9 + 7.
//
// Example 1:
//
//   Input: n = 3, k = 0
//   Output: 1
//   Explanation: Only the array [1,2,3] which consists of numbers from 1 to 3 has exactly 0 inverse pairs.
//
// Example 2:
//
//   Input: n = 3, k = 1
//   Output: 2
//   Explanation: The array [1,3,2] and [2,1,3] have exactly 1 inverse pair.
//
// Constraints:
//
//   1 <= n <= 1000
//   0 <= k <= 1000
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

const modulo = int(1e9 + 7)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Use 2D DP
// dp[0, k] = 0
// dp[n, 0] = 1
// dp[n+1, k] = dp[n, 0] + dp[n, 1] + ... + dp[n, k]
func kInversePairs(n int, k int) int {
	dp := make([][]int, n+1)
	for i := 0; i <= n; i++ {
		dp[i] = make([]int, k+1)
	}

	for n1 := 1; n1 <= n; n1++ {
		dp[n1][0] = 1
		for k1 := 1; k1 <= k; k1++ {
			for i := 0; i <= _min(k1, n1-1); i++ {
				dp[n1][k1] += dp[n1-1][k1-i]
			}
			dp[n1][k1] %= modulo
		}
	}

	return dp[n][k]
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Use 1D DP
// dp[0, k] = 0
// dp[n, 0] = 1
// dp[n+1, k] = dp[n, 0] + dp[n, 1] + ... + dp[n, k]
func kInversePairs2(n int, k int) int {
	prev := make([]int, k+1)
	next := make([]int, k+1)

	for n1 := 1; n1 <= n; n1++ {
		next[0] = 1
		for k1 := 1; k1 <= k; k1++ {
			next[k1] = 0
			for i := 0; i <= _min(k1, n1-1); i++ {
				next[k1] += prev[k1-i]
			}
			next[k1] %= modulo
		}

		next, prev = prev, next
	}

	return prev[k]
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

func _min(a, b int) int {
	if a < b {
		return a
	}
	return b
}
