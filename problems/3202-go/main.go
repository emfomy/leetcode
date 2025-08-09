// Source: https://leetcode.com/problems/https://leetcode.com/problems/find-the-maximum-length-of-valid-subsequence-ii
// Title: Find the Maximum Length of Valid Subsequence II
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `nums` and a **positive** integer `k`.
//
// A **subsequence** `sub` of `nums` with length `x` is called **valid** if it satisfies:
//
// - `(sub[0] + sub[1]) % k == (sub[1] + sub[2]) % k == ... == (sub[x - 2] + sub[x - 1]) % k.`
//
// A **subsequence** is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
//
// Return the length of the **longest** **valid** subsequence of `nums`.
//
// **Example 1:**
//
// ```
// Input: nums = [1,2,3,4,5], k = 2
// Output: 5
// Explanation:
// The longest valid subsequence is `[1, 2, 3, 4, 5]`.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [1,4,2,3,1,4], k = 3
// Output: 4
// Explanation:
// The longest valid subsequence is `[1, 4, 1, 4]`.
// ```
//
// **Constraints:**
//
// - `2 <= nums.length <= 10^3`
// - `1 <= nums[i] <= 10^7`
// - `1 <= k <= 10^3`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// TLE
func maximumLength(nums []int, k int) int {
	ans := 0
	for i := range k {
		for j := range k {
			pattern := []int{i, j}
			count := 0
			for _, num := range nums {
				if num%k == pattern[count%2] {
					count++
				}
			}
			ans = max(ans, count)
		}
	}

	return ans
}

// Backtracking, TLE
func maximumLength2(nums []int, k int) int {
	n := len(nums)

	var backtrack func(i int, r int) int // last index, reminder, size
	backtrack = func(i, r int) int {
		size := 1
		for j := range i {
			if (nums[i]+nums[j])%k == r {
				size = max(size, backtrack(j, r)+1)
			}
		}
		return size
	}

	ans := 0
	for j := range n {
		for i := range j {
			r := (nums[i] + nums[j]) % k
			ans = max(ans, backtrack(i, r))
		}
	}

	return ans + 1
}

// DP
//
// Loop though all possible target t such that (sub[0] + sub[1]) % k = t.
// Loop though the array.
// Let dp[i] = r be the maximum length of subsequence
// where the ending number is congruent to r modulo k.
func maximumLength3(nums []int, k int) int {
	ans := 0
	for t := range k {
		dp := make([]int, k)
		for _, num := range nums {
			r := num % k
			s := (t + k - r) % k // (r + s) % k == t
			dp[r] = max(dp[r], dp[s]+1)
			ans = max(ans, dp[r])
		}
	}

	return ans
}

// DP
//
// Let dp[i, j] be the maximum length of subsequence
// where the last pair is residue to (i, j) mod k.
//
// We loop thought the numbers. Say current number is congruent to i.
// We loop though all possible ending pairs (j, i) (i.e., loop through all j),
// and update dp[j, i] = max(dp[j, i], dp[i, j]+1).
//
// Note that the recursion can be simplify as dp[j, i] = dp[i, j]+1.
//
// To prove this, we improve the notation.
// Let DP[x, i, j] = dp[i, j] when current number index is x.
// Say index y dp[i, j] to its current value,
// and index z dp[j, i] to its current value.
// Note that x == z == i (mod k) and y == j (mod k).
//
// If y < z < x, we have DP[z, i, j] = DP[y, j, i] + 1 since z updates the value.
// Therefore, DP[x, i, j] = max(dp[j, i], dp[i, j]+1)
// .                      = max(DP[z, j, i], DP[y, i, j]+1)
// .                      = max(DP[y, i, j]+1, DP[y, i, j]+1)
// .                      = DP[y, i, j]+1, equation holds.
//
// If z < y < x, we have DP[y, j, i] = DP[z, i, j] + 1 since y updates the value.
// Therefore, DP[x, i, j] = max(dp[j, i], dp[i, j]+1)
// .                      = max(DP[z, j, i], DP[y, i, j]+1)
// .                      = max(DP[y, i, j]-1, DP[y, i, j]+1)
// .                      = DP[y, i, j]+1, equation holds.
func maximumLength4(nums []int, k int) int {
	dp := make([][]int, k)
	for i := range k {
		dp[i] = make([]int, k)
	}

	ans := 0
	for _, num := range nums {
		i := num % k
		for j := range k {
			dp[i][j] = dp[j][i] + 1 // NOTE: we ignore max() here
			ans = max(ans, dp[i][j])
		}
	}

	return ans
}
