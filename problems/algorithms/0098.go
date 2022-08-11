// Source: https://leetcode.com/problems/validate-binary-search-tree/
// Title: Validate Binary Search Tree
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given the root of a binary tree, determine if it is a valid binary search tree (BST).
//
// A valid BST is defined as follows:
//
//   The left subtree of a node contains only nodes with keys less than the node's key.
//   The right subtree of a node contains only nodes with keys greater than the node's key.
//   Both the left and right subtrees must also be binary search trees.
//
// Example 1:
//
//   https://assets.leetcode.com/uploads/2020/12/01/tree1.jpg
//
//   Input: root = [2,1,3]
//   Output: true
//
//   Example 2:
//
//   https://assets.leetcode.com/uploads/2020/12/01/tree2.jpg
//
//   Input: root = [5,1,4,null,null,3,6]
//   Output: false
//   Explanation: The root node's value is 5 but its right child's value is 4.
//
// Constraints:
//
//   The number of nodes in the tree is in the range [1, 10^4].
//   -23^1 <= Node.val <= 23^1 - 1
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func isValidBST(root *TreeNode) bool {
	_, _, valid := _isValidBST(root)
	return valid
}

func _isValidBST(root *TreeNode) (min int, max int, valid bool) {
	min, max, valid = root.Val, root.Val, true

	if root.Left != nil {
		leftMin, leftMax, leftValid := _isValidBST(root.Left)
		min = leftMin
		if !leftValid || leftMax >= root.Val {
			valid = false
			return
		}
	}

	if root.Right != nil {
		rightMin, rightMax, rightValid := _isValidBST(root.Right)
		max = rightMax
		if !rightValid || rightMin <= root.Val {
			valid = false
			return
		}
	}

	return
}
