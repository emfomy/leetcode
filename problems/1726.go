// Source: https://leetcode.com/problems/tuple-with-same-product
// Title: Tuple with Same Product
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array `nums` of **distinct** positive integers, return the number of tuples `(a, b, c, d)` such that `a * b = c * d` where `a`, `b`, `c`, and `d` are elements of `nums`, and `a != b != c != d`.
//
// **Example 1:**
//
// ```
// Input: nums = [2,3,4,6]
// Output: 8
// Explanation: There are 8 valid tuples:
// (2,6,3,4) , (2,6,4,3) , (6,2,3,4) , (6,2,4,3)
// (3,4,2,6) , (4,3,2,6) , (3,4,6,2) , (4,3,6,2)
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [1,2,4,5,10]
// Output: 16
// Explanation: There are 16 valid tuples:
// (1,10,2,5) , (1,10,5,2) , (10,1,2,5) , (10,1,5,2)
// (2,5,1,10) , (2,5,10,1) , (5,2,1,10) , (5,2,10,1)
// (2,10,4,5) , (2,10,5,4) , (10,2,4,5) , (10,2,5,4)
// (4,5,2,10) , (4,5,10,2) , (5,4,2,10) , (5,4,10,2)
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 1000`
// - `1 <= nums[i] <= 10^4`
// - All elements in `nums` are **distinct**.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// First we find all possible pair production
// For each production,
func tupleSameProduct(nums []int) int {
	prodCount := make(map[int]int) // count of production of two numbers

	for i, a := range nums {
		for _, b := range nums[:i] {
			prodCount[a*b]++
		}
	}

	res := 0
	for _, count := range prodCount {
		res += 4 * count * (count - 1) // 8 * C^k_2, k=count
	}

	return res
}
