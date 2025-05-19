// Source: https://leetcode.com/problems/find-largest-value-in-each-tree-row
// Title: Find Largest Value in Each Tree Row
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given the `root` of a binary tree, return an array of the largest value in each row of the tree **(0-indexed)**.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2020/08/21/largest_e1.jpg
//
// ```
// Input: root = [1,3,2,5,3,null,9]
// Output: [1,3,9]
// ```
//
// **Example 2:**
//
// ```
// Input: root = [1,2,3]
// Output: [1,3]
// ```
//
// **Constraints:**
//
// - The number of nodes in the tree will be in the range `[0, 10^4]`.
// - `-2^31 <= Node.val <= 2^31 - 1`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import "math"

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

// DFS
func largestValues(root *TreeNode) []int {
	var largest []int

	var _dfs func(*TreeNode, int)

	_dfs = func(node *TreeNode, level int) {
		if node == nil {
			return
		}
		if len(largest) == level {
			largest = append(largest, math.MinInt)
		}

		largest[level] = max(largest[level], node.Val)

		_dfs(node.Left, level+1)
		_dfs(node.Right, level+1)

		return
	}

	_dfs(root, 0)

	return largest
}

// BFS
func largestValues2(root *TreeNode) []int {
	if root == nil {
		return nil
	}

	var currLevel []*TreeNode
	var nextLevel []*TreeNode
	currLevel = append(currLevel, root)

	var res []int
	for len(currLevel) > 0 {
		maxVal := math.MinInt
		for _, node := range currLevel {
			maxVal = max(maxVal, node.Val)
			if node.Left != nil {
				nextLevel = append(nextLevel, node.Left)
			}
			if node.Right != nil {
				nextLevel = append(nextLevel, node.Right)
			}
		}

		res = append(res, maxVal)

		currLevel = nextLevel
		nextLevel = nil
	}

	return res
}
