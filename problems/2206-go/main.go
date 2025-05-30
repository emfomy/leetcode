// Source: https://leetcode.com/problems/divide-array-into-equal-pairs
// Title: Divide Array Into Equal Pairs
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `nums` consisting of `2 * n` integers.
//
// You need to divide `nums` into `n` pairs such that:
//
// - Each element belongs to **exactly one** pair.
// - The elements present in a pair are **equal**.
//
// Return `true` if nums can be divided into `n` pairs, otherwise return `false`.
//
// **Example 1:**
//
// ```
// Input: nums = [3,2,3,2,2,2]
// Output: true
// Explanation:
// There are 6 elements in nums, so they should be divided into 6 / 2 = 3 pairs.
// If nums is divided into the pairs (2, 2), (3, 3), and (2, 2), it will satisfy all the conditions.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [1,2,3,4]
// Output: false
// Explanation:
// There is no way to divide nums into 4 / 2 = 2 pairs such that the pairs satisfy every condition.
// ```
//
// **Constraints:**
//
// - `nums.length == 2 * n`
// - `1 <= n <= 500`
// - `1 <= nums[i] <= 500`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func divideArray(nums []int) bool {
	m := len(nums)
	numCount := make(map[int]int, m)

	for _, num := range nums {
		numCount[num]++
	}

	for _, count := range numCount {
		if count%2 != 0 {
			return false
		}
	}
	return true
}

func divideArray2(nums []int) bool {
	m := len(nums)
	visited := make(map[int]bool, m)

	for _, num := range nums {
		if !visited[num] {
			visited[num] = true
		} else {
			delete(visited, num)
		}
	}

	return len(visited) == 0
}
