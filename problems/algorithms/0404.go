// Source: https://leetcode.com/problems/sum-of-left-leaves/
// Title: Sum of Left Leaves
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given the root of a binary tree, return the sum of all left leaves.
//
// A leaf is a node with no children. A left leaf is a leaf that is the left child of another node.
//
// Example 1:
//
//   https://assets.leetcode.com/uploads/2021/04/08/leftsum-tree.jpg
//   Input: root = [3,9,20,null,null,15,7]
//   Output: 24
//   Explanation: There are two left leaves in the binary tree, with values 9 and 15 respectively.
//
// Example 2:
//
//   Input: root = [1]
//   Output: 0
//
// Constraints:
//
//   The number of nodes in the tree is in the range [1, 1000].
//   -1000 <= Node.val <= 1000
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func sumOfLeftLeaves(root *TreeNode) int {
	return _sumOfLeftLeaves(root, false)
}

func _sumOfLeftLeaves(root *TreeNode, isLeft bool) int {
	if root.Left == nil && root.Right == nil {
		if isLeft {
			return root.Val
		}
		return 0
	}

	res := 0
	if root.Left != nil {
		res += _sumOfLeftLeaves(root.Left, true)
	}
	if root.Right != nil {
		res += _sumOfLeftLeaves(root.Right, false)
	}
	return res
}
