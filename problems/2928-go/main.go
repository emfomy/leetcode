// Source: https://leetcode.com/problems/distribute-candies-among-children-i
// Title: Distribute Candies Among Children I
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given two positive integers `n` and `limit`.
//
// Return the **total number** of ways to distribute `n` candies among `3` children such that no child gets more than `limit` candies.
//
// **Example 1:**
//
// ```
// Input: n = 5, limit = 2
// Output: 3
// Explanation: There are 3 ways to distribute 5 candies such that no child gets more than 2 candies: (1, 2, 2), (2, 1, 2) and (2, 2, 1).
// ```
//
// **Example 2:**
//
// ```
// Input: n = 3, limit = 3
// Output: 10
// Explanation: There are 10 ways to distribute 3 candies such that no child gets more than 3 candies: (0, 0, 3), (0, 1, 2), (0, 2, 1), (0, 3, 0), (1, 0, 2), (1, 1, 1), (1, 2, 0), (2, 0, 1), (2, 1, 0) and (3, 0, 0).
// ```
//
// **Constraints:**
//
// - `1 <= n <= 50`
// - `1 <= limit <= 50`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// Count
func distributeCandies(n int, limit int) int {
	if n > 3*limit {
		return 0
	}

	ans := 0
	min1 := max(0, n-limit*2)
	max1 := min(limit, n)
	for num1 := min1; num1 <= max1; num1++ {
		min2 := max(0, n-num1-limit)
		max2 := min(limit, n-num1)
		ans += max2 - min2 + 1
	}

	return ans
}

// Math, Inclusion-Exclusion Principle
//
// Total distribution without limit:
// C1 = C(n+2, 2)
//
// At least one receives more than limit:
// Given (limit+1) candles to one child. Remains n-(limit+1) candles.
// 3 possible way to choose the child.
// C2 = 3 * C(n-(limit+1)+2, 2)
//
// At least two receives more than limit:
// Given 2(limit+1) candles to two children. Remains n-2(limit+1) candles.
// 3 possible way to choose two children.
// C3 = 3 * C(n-2(limit+1)+2, 2)
//
// All receives more than limit:
// Given 3(limit+1) candles to all children. Remains n-3(limit+1) candles.
// C4 = C(n-3(limit+1)+2, 2)
//
// Ans = C1 - C2 + C3 - C4
func distributeCandies2(n int, limit int) int {
	comb := func(x int) int {
		if x < 0 {
			return 0
		}
		return x * (x - 1) / 2
	}

	n2 := n + 2
	limit1 := limit + 1
	return comb(n2) - 3*comb(n2-limit1) + 3*comb(n2-limit1*2) - comb(n2-limit1*3)
}
