// Source: https://leetcode.com/problems/minimum-operations-to-make-a-uni-value-grid
// Title: Minimum Operations to Make a Uni-Value Grid
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a 2D integer `grid` of size `m x n` and an integer `x`. In one operation, you can **add** `x` to or **subtract** `x` from any element in the `grid`.
//
// A **uni-value grid** is a grid where all the elements of it are equal.
//
// Return the **minimum** number of operations to make the grid **uni-value**. If it is not possible, return `-1`.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/09/21/gridtxt.png
//
// ```
// Input: grid = [[2,4],[6,8]], x = 2
// Output: 4
// Explanation: We can make every element equal to 4 by doing the following:
// - Add x to 2 once.
// - Subtract x from 6 once.
// - Subtract x from 8 twice.
// A total of 4 operations were used.
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2021/09/21/gridtxt-1.png
//
// ```
// Input: grid = [[1,5],[2,3]], x = 1
// Output: 5
// Explanation: We can make every element equal to 3.
// ```
//
// **Example 3:**
// https://assets.leetcode.com/uploads/2021/09/21/gridtxt-2.png
//
// ```
// Input: grid = [[1,2],[3,4]], x = 2
// Output: -1
// Explanation: It is impossible to make every element equal.
// ```
//
// **Constraints:**
//
// - `m == grid.length`
// - `n == grid[i].length`
// - `1 <= m, n <= 10^5`
// - `1 <= m * n <= 10^5`
// - `1 <= x, grid[i][j] <= 10^4`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"fmt"
	"slices"
)

// Minimize |a_1-k| + ... + |a_n-k|
// Say a_(t-1) <= k < a_t
// = (k-a_1) + ... + (k-a_(t-1)) + (a_t-k) + ... + (a_n-k)
// = sum(a_i) - 2*(a_1+...+a_(t-1)) - (n-2t)*k
func minOperations(grid [][]int, x int) int {
	m, n := len(grid), len(grid[0])
	mn := m * n

	nums := make([]int, mn)
	r := grid[0][0] % x
	sum := 0
	for i := range mn {
		num := grid[i/n][i%n]
		if num%x != r {
			return -1
		}
		nums[i] = num
		sum += num
	}

	slices.Sort(nums)

	minVal := sum
	presum, t := 0, 0
	for k := nums[0]; k <= nums[mn-1]; k += x {
		for t < mn && k >= nums[t] {
			presum += nums[t]
			t++
		}
		val := sum - 2*presum - (mn-2*t)*k
		if val < minVal {
			minVal = val
		} else {
			break
		}
	}

	return minVal / x
}
func main() {
	fmt.Println(minOperations(
		[][]int{
			{1, 2, 3},
			{4, 5, 6},
		},
		1,
	))
}
