// Source: https://leetcode.com/problems/unique-binary-search-trees-ii/
// Title: Unique Binary Search Trees II
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer n, return all the structurally unique BST's (binary search trees), which has exactly n nodes of unique values from 1 to n. Return the answer in any order.
//
// Example 1:
//
//   https://assets.leetcode.com/uploads/2021/01/18/uniquebstn3.jpg
//
//   Input: n = 3
//   Output: [[1,null,2,null,3],[1,null,3,2],[2,1,3],[3,1,null,null,2],[3,2,null,1]]
//
// Example 2:
//
//   Input: n = 1
//   Output: [[1]]
//
// Constraints:
//
//   1 <= n <= 8
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func generateTrees(n int) []*TreeNode {
	return _generateTrees(n, 1)
}

func _generateTrees(n int, val int) []*TreeNode {
	if n == 0 {
		return []*TreeNode{nil}
	}

	res := make([]*TreeNode, 0)
	for i := 0; i < n; i++ {
		for _, left := range _generateTrees(i, val) {
			for _, right := range _generateTrees(n-i-1, val+i+1) {
				res = append(res, &TreeNode{
					Val:   val + i,
					Left:  left,
					Right: right,
				})
			}
		}
	}
	return res
}
