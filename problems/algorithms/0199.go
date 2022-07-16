// Source: https://leetcode.com/problems/binary-tree-right-side-view/
// Title: Binary Tree Right Side View
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given the root of a binary tree, imagine yourself standing on the right side of it, return the values of the nodes you can see ordered from top to bottom.
//
// Example 1:
//
//   https://assets.leetcode.com/uploads/2021/02/14/tree.jpg
//
//   Input: root = [1,2,3,null,5,null,4]
//   Output: [1,3,4]
//
// Example 2:
//
//   Input: root = [1,null,3]
//   Output: [1,3]
//
// Example 3:
//
//   Input: root = []
//   Output: []
//
// Constraints:
//
//   The number of nodes in the tree is in the range [0, 100].
//   -100 <= Node.val <= 100
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func rightSideView(root *TreeNode) []int {
	res := make([]int, 0, 100)
	_rightSideView(root, &res, 0)
	return res
}

func _rightSideView(root *TreeNode, res *[]int, depth int) {
	if root == nil {
		return
	}
	if depth >= len(*res) {
		*res = append(*res, root.Val)
	}
	_rightSideView(root.Right, res, depth+1)
	_rightSideView(root.Left, res, depth+1)
}
