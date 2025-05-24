// Source: https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal
// Title: Construct Binary Tree from Preorder and Inorder Traversal
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given two integer arrays preorder and inorder where preorder is the preorder traversal of a binary tree and inorder is the inorder traversal of the same tree, construct and return the binary tree.
//
// Example 1:
//
//   Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
//   Output: [3,9,20,null,null,15,7]
//
// Example 2:
//
//   Input: preorder = [-1], inorder = [-1]
//   Output: [-1]
//
// Constraints:
//
//   1 <= preorder.length <= 3000
//   inorder.length == preorder.length
//   -3000 <= preorder[i], inorder[i] <= 3000
//   preorder and inorder consist of unique values.
//   Each value of inorder also appears in preorder.
//   preorder is guaranteed to be the preorder traversal of the tree.
//   inorder is guaranteed to be the inorder traversal of the tree.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

type list struct {
	arr []int
	idx int
}

func newList(arr []int) *list {
	return &list{
		arr: arr,
	}
}

func (l *list) peak() int {
	return l.arr[l.idx]
}

func (l *list) pop() int {
	res := l.peak()
	l.idx++
	return res
}

func (l *list) isEmpty() bool {
	return l.idx == len(l.arr)
}

// Time: O(n); Space: O(n)
func buildTree(preorder []int, inorder []int) *TreeNode {
	pre := newList(preorder)
	in := newList(inorder)
	return _buildTree(pre, in, -10000)
}

func _buildTree(pre, in *list, parentVal int) (root *TreeNode) {
	if pre.isEmpty() {
		return nil
	}

	if parentVal == in.peak() {
		in.pop()
		return
	}

	root = &TreeNode{
		Val: pre.pop(),
	}

	root.Left = _buildTree(pre, in, root.Val)
	root.Right = _buildTree(pre, in, parentVal)

	return
}
