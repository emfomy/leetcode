// Source: https://leetcode.com/problems/number-of-sub-arrays-with-odd-sum
// Title: Number of Sub-arrays With Odd Sum
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array of integers `arr`, return the number of subarrays with an **odd** sum.
//
// Since the answer can be very large, return it modulo `10^9 + 7`.
//
// **Example 1:**
//
// ```
// Input: arr = [1,3,5]
// Output: 4
// Explanation: All subarrays are [[1],[1,3],[1,3,5],[3],[3,5],[5]]
// All sub-arrays sum are [1,4,9,3,8,5].
// Odd sums are [1,9,3,5] so the answer is 4.
// ```
//
// **Example 2:**
//
// ```
// Input: arr = [2,4,6]
// Output: 0
// Explanation: All subarrays are [[2],[2,4],[2,4,6],[4],[4,6],[6]]
// All sub-arrays sum are [2,6,12,4,10,6].
// All sub-arrays have even sum and the answer is 0.
// ```
//
// **Example 3:**
//
// ```
// Input: arr = [1,2,3,4,5,6,7]
// Output: 16
// ```
//
// **Constraints:**
//
// - `1 <= arr.length <= 10^5`
// - `1 <= arr[i] <= 100`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

const modulo = int(1e9 + 7)

// DP
func numOfSubarrays(arr []int) int {
	oddDp := 0  // number of odd subarray starts at i
	evenDp := 0 // number of even subarray starts at i

	res := 0
	for _, num := range arr {
		if num%2 == 0 { // even
			evenDp++
		} else { // odd
			oddDp, evenDp = evenDp, oddDp
			oddDp++
		}
		res += oddDp
	}

	return res % modulo
}

// Count prefix sum
// Any subarray is the difference of two subarray start from zero (i.e. prefix sum)
func numOfSubarrays2(arr []int) int {
	sum := 0
	odd := 0
	even := 1 // empty array is even

	for _, num := range arr {
		sum += num
		if sum%2 == 0 { // even
			even++
		} else { // odd
			odd++
		}
	}

	return (even * odd) % modulo
}
