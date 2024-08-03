// Source: https://leetcode.com/problems/binary-trees-with-factors
// Title: Binary Trees With Factors
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array of unique integers, arr, where each integer arr[i] is strictly greater than 1.
//
// We make a binary tree using these integers, and each number may be used for any number of times. Each non-leaf node's value should be equal to the product of the values of its children.
//
// Return the number of binary trees we can make. The answer may be too large so return the answer modulo 10^9 + 7.
//
// Example 1:
//
//   Input: arr = [2,4]
//   Output: 3
//   Explanation: We can make these trees: [2], [4], [4, 2, 2]
//
// Example 2:
//
//   Input: arr = [2,4,5,10]
//   Output: 7
//   Explanation: We can make these trees: [2], [4], [5], [10], [4, 2, 2], [10, 2, 5], [10, 5, 2].
//
// Constraints:
//
//   1 <= arr.length <= 1000
//   2 <= arr[i] <= 10^9
//   All the values of arr are unique.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"sort"
)

const modulo = int(1e9 + 7)

func numFactoredBinaryTrees(arr []int) int {
	sort.Ints(arr)

	dp := make(map[int]int) // Map root value to number of trees

	for _, val := range arr {
		dp[val] = 1
		for _, child := range arr {
			if child >= val {
				break
			}
			if val%child != 0 {
				continue
			}
			dp[val] += dp[child] * dp[val/child]
		}
		dp[val] %= modulo
	}

	res := 0
	for _, val := range arr {
		res += dp[val]
	}

	return res % modulo
}
