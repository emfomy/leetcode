// Source: https://leetcode.com/problems/maximum-depth-of-binary-tree
// Title: Maximum Depth of Binary Tree
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given the root of a binary tree, return its maximum depth.
//
// A binary tree's maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.
//
// Example 1:
//
//   https://assets.leetcode.com/uploads/2020/11/26/tmp-tree.jpg
//
//   Input: root = [3,9,20,null,null,15,7]
//   Output: 3
//
// Example 2:
//
//   Input: root = [1,null,2]
//   Output: 2
//
// Constraints:
//
//   The number of nodes in the tree is in the range [0, 10^4].
//   -100 <= Node.val <= 100
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func maxDepth(root *TreeNode) int {
	if root == nil {
		return 0
	}
	return 1 + _max(maxDepth(root.Left), maxDepth(root.Right))
}

func _max(a, b int) int {
	if a > b {
		return a
	}
	return b
}
