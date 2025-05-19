// Source: https://leetcode.com/problems/count-largest-group
// Title: Count Largest Group
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer `n`.
//
// Each number from `1` to `n` is grouped according to the sum of its digits.
//
// Return the number of groups that have the largest size.
//
// **Example 1:**
//
// ```
// Input: n = 13
// Output: 4
// Explanation: There are 9 groups in total, they are grouped according sum of its digits of numbers from 1 to 13:
// [1,10], [2,11], [3,12], [4,13], [5], [6], [7], [8], [9].
// There are 4 groups with largest size.
// ```
//
// **Example 2:**
//
// ```
// Input: n = 2
// Output: 2
// Explanation: There are 2 groups [1], [2] of size 1.
// ```
//
// **Constraints:**
//
// - `1 <= n <= 10^4`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func countLargestGroup(n int) int {
	groupSize := make(map[int]int) // group to size

	for num := range n {
		num++
		sum := 0
		for num > 0 {
			sum += num % 10
			num /= 10
		}
		groupSize[sum]++
	}

	sizeCount := make(map[int]int) // size to count
	maxSize := 0
	for _, size := range groupSize {
		sizeCount[size]++
		maxSize = max(maxSize, size)
	}

	return sizeCount[maxSize]
}
