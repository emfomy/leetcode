// Source: https://leetcode.com/problems/minimum-difference-in-sums-after-removal-of-elements
// Title: Minimum Difference in Sums After Removal of Elements
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a **0-indexed** integer array `nums` consisting of `3 * n` elements.
//
// You are allowed to remove any **subsequence** of elements of size **exactly** `n` from `nums`. The remaining `2 * n` elements will be divided into two **equal** parts:
//
// - The first `n` elements belonging to the first part and their sum is `sum_first`.
// - The next `n` elements belonging to the second part and their sum is `sum_second`.
//
// The **difference in sums** of the two parts is denoted as `sum_first - sum_second`.
//
// - For example, if `sum_first = 3` and `sum_second = 2`, their difference is `1`.
// - Similarly, if `sum_first = 2` and `sum_second = 3`, their difference is `-1`.
//
// Return the **minimum difference** possible between the sums of the two parts after the removal of `n` elements.
//
// **Example 1:**
//
// ```
// Input: nums = [3,1,2]
// Output: -1
// Explanation: Here, nums has 3 elements, so n = 1.
// Thus we have to remove 1 element from nums and divide the array into two equal parts.
// - If we remove nums[0] = 3, the array will be [1,2]. The difference in sums of the two parts will be 1 - 2 = -1.
// - If we remove nums[1] = 1, the array will be [3,2]. The difference in sums of the two parts will be 3 - 2 = 1.
// - If we remove nums[2] = 2, the array will be [3,1]. The difference in sums of the two parts will be 3 - 1 = 2.
// The minimum difference between sums of the two parts is min(-1,1,2) = -1.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [7,9,5,8,1,3]
// Output: 1
// Explanation: Here n = 2. So we must remove 2 elements and divide the remaining array into two parts containing two elements each.
// If we remove nums[2] = 5 and nums[3] = 8, the resultant array will be [7,9,1,3]. The difference in sums will be (7+9) - (1+3) = 12.
// To obtain the minimum difference, we should remove nums[1] = 9 and nums[4] = 1. The resultant array becomes [7,5,8,3]. The difference in sums of the two parts is (7+5) - (8+3) = 1.
// It can be shown that it is not possible to obtain a difference smaller than 1.
// ```
//
// **Constraints:**
//
// - `nums.length == 3 * n`
// - `1 <= n <= 10^5`
// - `1 <= nums[i] <= 10^5`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"github.com/emirpasic/gods/v2/trees/binaryheap"
)

// Use DP, OOM
//
// We want to minimize sum1 and maximize sum2.
// Let dp1(l, i) be the minimal sum of any subsequence of [0, i) with length l elements.
// Let dp2(l, j) be the minimal sum of any subsequence of [j, m) with length l elements.
//
// For recursion, we either include current number or exclude current number.
// dp1(l, i) = min(dp1(l-1, i-1) + nums[i-1], dp1(l, i-1))
// dp2(l, j) = max(dp2(l-1, j+1) + nums[i],   dp2(l, j+1))
func minimumDifference(nums []int) int64 {
	m := len(nums)
	n := m / 3

	dp1 := make([][]int64, n+1)
	dp2 := make([][]int64, n+1)
	for i := range n + 1 {
		dp1[i] = make([]int64, m+1)
		dp2[i] = make([]int64, m+1)
	}

	for l := 1; l <= n; l++ {
		dp1[l][l] = dp1[l-1][l-1] + int64(nums[l-1])
		for i := l + 1; i <= m; i++ {
			dp1[l][i] = min(
				dp1[l-1][i-1]+int64(nums[i-1]),
				dp1[l][i-1],
			)
		}

		dp2[l][m-l] = dp2[l-1][m-l+1] + int64(nums[m-l])
		for j := m - l - 1; j >= 0; j-- {
			dp2[l][j] = max(
				dp2[l-1][j+1]+int64(nums[j]),
				dp2[l][j+1],
			)
		}
	}

	ans := dp1[n][n] - dp2[n][n]
	for i := n + 1; i <= m-n; i++ {
		ans = min(ans, dp1[n][i]-dp2[n][i])
	}

	return ans
}

// Use DP
func minimumDifference2(nums []int) int64 {
	m := len(nums)
	n := m / 3

	curr1 := make([]int64, m+1)
	curr2 := make([]int64, m+1)

	for l := 1; l <= n; l++ {
		next1 := make([]int64, m+1)
		next2 := make([]int64, m+1)

		next1[l] = curr1[l-1] + int64(nums[l-1])
		for i := l + 1; i <= m; i++ {
			next1[i] = min(
				curr1[i-1]+int64(nums[i-1]),
				next1[i-1],
			)
		}

		next2[m-l] = curr2[m-l+1] + int64(nums[m-l])
		for j := m - l - 1; j >= 0; j-- {
			next2[j] = max(
				curr2[j+1]+int64(nums[j]),
				next2[j+1],
			)
		}

		curr1 = next1
		curr2 = next2
	}

	ans := curr1[n] - curr2[n]
	for i := n + 1; i <= m-n; i++ {
		ans = min(ans, curr1[i]-curr2[i])
	}

	return ans
}

// Use Heap
//
// Say we split the array at index i.
// sum1 must be the sum of the minimal n numbers in [0, i).
// sum2 must be the sum of the maximal n numbers in [i, m).
// We can use heaps to store these numbers.
func minimumDifference3(nums []int) int64 {
	m := len(nums)
	n := m / 3

	part1 := make([]int, n+1) // stores i in [n, 2n]
	part2 := make([]int, n+1) // stores i in [n, 2n]

	heap1 := binaryheap.NewWith(func(a, b int) int { return b - a }) // max heap
	heap2 := binaryheap.New[int]()                                   // min-heap

	sum1 := 0
	for _, num := range nums[:n] {
		sum1 += num
		heap1.Push(num)
	}

	part1[0] = sum1
	for i := n + 1; i <= 2*n; i++ {
		heap1.Push(nums[i-1])
		num, _ := heap1.Pop()
		sum1 += nums[i-1] - num
		part1[i-n] = sum1
	}

	sum2 := 0
	for _, num := range nums[m-n:] {
		sum2 += num
		heap2.Push(num)
	}

	part2[n] = sum2
	for i := 2*n - 1; i >= n; i-- {
		heap2.Push(nums[i])
		num, _ := heap2.Pop()
		sum2 += nums[i] - num
		part2[i-n] = sum2
	}

	ans := part1[0] - part2[0]
	for i := 1; i <= n; i++ {
		ans = min(ans, part1[i]-part2[i])
	}

	return int64(ans)
}
