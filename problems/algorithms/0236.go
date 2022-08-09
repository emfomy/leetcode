// Source: https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/
// Title: Lowest Common Ancestor of a Binary Tree
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.
//
// According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes p and q as the lowest node in T that has both p and q as descendants (where we allow a node to be a descendant of itself).”
//
// Example 1:
//
//   https://assets.leetcode.com/uploads/2018/12/14/binarytree.png
//
//   Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
//   Output: 3
//   Explanation: The LCA of nodes 5 and 1 is 3.
//
// Example 2:
//
//   https://assets.leetcode.com/uploads/2018/12/14/binarytree.png
//
//   Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
//   Output: 5
//   Explanation: The LCA of nodes 5 and 4 is 5, since a node can be a descendant of itself according to the LCA definition.
//
// Example 3:
//
//   Input: root = [1,2], p = 1, q = 2
//   Output: 1
//
// Constraints:
//
//   The number of nodes in the tree is in the range [2, 10^5].
//   -10^9 <= Node.val <= 10^9
//   All Node.val are unique.
//   p != q
//   p and q will exist in the tree.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func lowestCommonAncestor(root, p, q *TreeNode) *TreeNode {
	res, _ := _findChild(root, p, q)
	return res
}

func _findChild(root, p, q *TreeNode) (*TreeNode, int) {
	if root == nil {
		return nil, 0
	}

	found := 0

	if root == p || root == q {
		found++
	}

	lRes, lFound := _findChild(root.Left, p, q)
	if lRes != nil {
		return lRes, lFound
	}
	found += lFound

	rRes, rFound := _findChild(root.Right, p, q)
	if rRes != nil {
		return rRes, rFound
	}
	found += rFound

	if found == 2 {
		return root, found
	}

	return nil, found
}
