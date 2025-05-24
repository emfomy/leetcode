// Source: https://leetcode.com/problems/best-sightseeing-pair
// Title: Best Sightseeing Pair
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `values` where values[i] represents the value of the `i^th` sightseeing spot. Two sightseeing spots `i` and `j` have a **distance** `j - i` between them.
//
// The score of a pair (`i < j`) of sightseeing spots is `values[i] + values[j] + i - j`: the sum of the values of the sightseeing spots, minus the distance between them.
//
// Return the maximum score of a pair of sightseeing spots.
//
// **Example 1:**
//
// ```
// Input: values = [8,1,5,2,6]
// Output: 11
// Explanation: i = 0, j = 2, values[i] + values[j] + i - j = 8 + 5 + 0 - 2 = 11
// ```
//
// **Example 2:**
//
// ```
// Input: values = [1,2]
// Output: 2
// ```
//
// **Constraints:**
//
// - `2 <= values.length <= 5 * 10^4`
// - `1 <= values[i] <= 1000`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// Brute-force, O(n^2)
func maxScoreSightseeingPair(values []int) int {
	n := len(values)

	res := 0
	for i := 0; i < n; i++ {
		for j := i + 1; j < n; j++ {
			res = max(res, values[i]+values[j]+i-j)
		}
	}

	return res
}

// DP, O(n)
// The value of i decrease by 1 for each step we go right
func maxScoreSightseeingPair2(values []int) int {
	iValue := values[0]

	res := 0
	for _, jValue := range values {
		iValue--
		res = max(res, iValue+jValue)
		iValue = max(iValue, jValue)
	}

	return res
}
