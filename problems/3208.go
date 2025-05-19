// Source: https://leetcode.com/problems/alternating-groups-ii
// Title: Alternating Groups II
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There is a circle of red and blue tiles. You are given an array of integers `colors` and an integer `k`. The color of tile `i` is represented by `colors[i]`:
//
// - `colors[i] == 0` means that tile `i` is **red** .
// - `colors[i] == 1` means that tile `i` is **blue** .
//
// An **alternating** group is every `k` contiguous tiles in the circle with **alternating** colors (each tile in the group except the first and last one has a different color from its **left** and **right** tiles).
//
// Return the number of **alternating** groups.
//
// **Note** that since `colors` represents a **circle** , the **first** and the **last** tiles are considered to be next to each other.
//
// **Example 1:**
//
// ```
// Input: colors = [0,1,0,1,0], k = 3
//
// Output: 3
//
// Explanation:
// https://assets.leetcode.com/uploads/2024/06/19/screenshot-2024-05-28-183519.png
//
// Alternating groups:
// https://assets.leetcode.com/uploads/2024/05/28/screenshot-2024-05-28-182448.png
// https://assets.leetcode.com/uploads/2024/05/28/screenshot-2024-05-28-182844.png
// https://assets.leetcode.com/uploads/2024/05/28/screenshot-2024-05-28-183057.png
// ```
//
// **Example 2:**
//
// ```
// Input: colors = [0,1,0,0,1,0,1], k = 6
//
// Output: 2
//
// Explanation:
// https://assets.leetcode.com/uploads/2024/06/19/screenshot-2024-05-28-183907.png
//
// Alternating groups:
// https://assets.leetcode.com/uploads/2024/06/19/screenshot-2024-05-28-184128.png
// https://assets.leetcode.com/uploads/2024/06/19/screenshot-2024-05-28-184240.png
// ```
//
// **Example 3:**
//
// ```
// Input: colors = [1,1,0,1], k = 4
//
// Output: 0
//
// Explanation:
//
// https://assets.leetcode.com/uploads/2024/06/19/screenshot-2024-05-28-184516.png
// ```
//
// **Constraints:**
//
// - `3 <= colors.length <= 10^5`
// - `0 <= colors[i] <= 1`
// - `3 <= k <= colors.length`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func numberOfAlternatingGroups(colors []int, k int) int {
	n := len(colors)
	res := 0

	// Find first non-alternating point
	start := -1
	if colors[0] == colors[n-1] {
		start = 0
	} else {
		for i := 1; i < n; i++ {
			if colors[i] == colors[i-1] {
				start = i
				break
			}
		}
	}

	if start == -1 { // the circle is alternating
		return n
	}

	// Find alternating segments
	size := 1
	for i := start + 1; i < n+start; i++ {
		if colors[i%n] != colors[(i-1)%n] {
			size++
		} else {
			if size >= k {
				res += size - k + 1
			}
			size = 1
		}
	}
	if size >= k {
		res += size - k + 1
	}

	return res
}

func numberOfAlternatingGroups2(colors []int, k int) int {
	n := len(colors)
	res := 0

	l, r := 0, 0
	for l < n {
		r++

		if colors[r%n] == colors[(r-1)%n] {
			l = r
			continue
		}

		if r-l+1 == k {
			res++
			l++
		}
	}

	return res
}
