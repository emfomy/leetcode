// Source: https://leetcode.com/problems/unique-binary-search-trees/
// Title: Unique Binary Search Trees
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer n, return the number of structurally unique BST's (binary search trees) which has exactly n nodes of unique values from 1 to n.
//
// Example 1:
//
//   https://assets.leetcode.com/uploads/2021/01/18/uniquebstn3.jpg
//   Input: n = 3
//   Output: 5
//
// Example 2:
//
//   Input: n = 1
//   Output: 1
//
// Constraints:
//
//   1 <= n <= 19
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Pick any number R as root, assume that there are L/R number smaller/greater than R.
// The number of BST = #BST(L) * #BST(R)
func numTrees(n int) int {
	arr := make([]int, n+1)
	arr[0] = 1

	for i := 1; i <= n; i++ {
		for j := 0; j < i; j++ {
			arr[i] += arr[j] * arr[i-1-j]
		}
	}

	return arr[n]
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Catalan number
var a000170 = []int{
	1, 1, 2, 5, 14,
	42, 132, 429, 1430, 4862,
	16796, 58786, 208012, 742900, 2674440,
	9694845, 35357670, 129644790, 477638700, 1767263190,
}

func numTrees2(n int) int {
	return a000170[n]
}
