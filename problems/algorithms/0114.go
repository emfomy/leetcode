// Source: https://leetcode.com/problems/flatten-binary-tree-to-linked-list/
//  Title: Flatten Binary Tree to Linked List
//  Difficulty: Medium
//  Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Given the root of a binary tree, flatten the tree into a "linked list":
//
//    The "linked list" should use the same TreeNode class where the right child pointer points to the next node in the list and the left child pointer is always null.
//    The "linked list" should be in the same order as a pre-order traversal of the binary tree.
//
//  Example 1:
//
//    https://assets.leetcode.com/uploads/2021/01/14/flaten.jpg
//
//    Input: root = [1,2,5,3,4,null,6]
//    Output: [1,null,2,null,3,null,4,null,5,null,6]
//
//  Example 2:
//
//    Input: root = []
//    Output: []
//
//  Example 3:
//
//    Input: root = [0]
//    Output: [0]
//
//  Constraints:
//
//    The number of nodes in the tree is in the range [0, 2000].
//    -100 <= Node.val <= 100
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func flatten(root *TreeNode) {
	_flatten(root)
}

// Returns the tail
func _flatten(root *TreeNode) *TreeNode {
	if root == nil {
		return nil
	}

	res := root

	left := root.Left
	right := root.Right
	root.Left = nil

	leftTail := _flatten(left)
	if leftTail != nil {
		root.Right = left
		leftTail.Right = root.Right
		res = leftTail
	}

	rightTail := _flatten(right)
	if rightTail != nil {
		res = rightTail
	}

	return res
}
