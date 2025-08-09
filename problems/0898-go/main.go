// Source: https://leetcode.com/problems/bitwise-ors-of-subarrays
// Title: Bitwise ORs of Subarrays
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer array `arr`, return the number of distinct bitwise ORs of all the non-empty subarrays of `arr`.
//
// The bitwise OR of a subarray is the bitwise OR of each integer in the subarray. The bitwise OR of a subarray of one integer is that integer.
//
// A **subarray** is a contiguous non-empty sequence of elements within an array.
//
// **Example 1:**
//
// ```
// Input: arr = [0]
// Output: 1
// Explanation: There is only one possible result: 0.
// ```
//
// **Example 2:**
//
// ```
// Input: arr = [1,1,2]
// Output: 3
// Explanation: The possible subarrays are [1], [1], [2], [1, 1], [1, 2], [1, 1, 2].
// These yield the results 1, 1, 2, 1, 3, 3.
// There are 3 unique values, so the answer is 3.
// ```
//
// **Example 3:**
//
// ```
// Input: arr = [1,2,4]
// Output: 6
// Explanation: The possible results are 1, 2, 3, 4, 6, and 7.
// ```
//
// **Constraints:**
//
// - `1 <= arr.length <= 5 * 10^4`
// - `0 <= arr[i] <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func subarrayBitwiseORs(arr []int) int {
	type void struct{}
	ans := make(map[int]void)
	var currMap map[int]void

	for _, num := range arr {
		nextMap := make(map[int]void)
		nextMap[num] = void{}
		ans[num] = void{}

		for curr := range currMap {
			nextMap[curr|num] = void{}
			ans[curr|num] = void{}
		}

		currMap = nextMap
	}

	return len(ans)
}
