// Source: https://leetcode.com/problems/maximum-difference-between-node-and-ancestor/
// Title: Determine if String Halves Are Alike
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given the root of a binary tree, find the maximum value v for which there exist different nodes a and b where v = |a.val - b.val| and a is an ancestor of b.
//
// A node a is an ancestor of b if either: any child of a is equal to b or any child of a is an ancestor of b.
//
// Example 1:
//
//   https://assets.leetcode.com/uploads/2020/11/09/tmp-tree.jpg
//
//   Input: root = [8,3,10,1,6,null,14,null,null,4,7,13]
//   Output: 7
//   Explanation:
//     We have various ancestor-node differences, some of which are given below :
//     |8 - 3| = 5
//     |3 - 7| = 4
//     |8 - 1| = 7
//     |10 - 13| = 3
//     Among all possible differences, the maximum value of 7 is obtained by |8 - 1| = 7.
//
// Example 2:
//
//   https://assets.leetcode.com/uploads/2020/11/09/tmp-tree-1.jpg
//
//   Input: root = [1,null,2,null,0,3]
//   Output: 3
//
// Constraints:
//
//   The number of nodes in the tree is in the range [2, 5000].
//   0 <= Node.val <= 10^5
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func maxAncestorDiff(root *TreeNode) int {
	return _maxAncestorDiff(root, root.Val, root.Val)
}

func _maxAncestorDiff(root *TreeNode, min, max int) int {
	if root == nil {
		return 0
	}

	min = _min(min, root.Val)
	max = _max(max, root.Val)
	res := _max(root.Val-min, max-root.Val)

	// Left
	res = _max(res, _maxAncestorDiff(root.Left, min, max))

	// Right
	res = _max(res, _maxAncestorDiff(root.Right, min, max))

	return res
}

func _max(a, b int) int {
	if a > b {
		return a
	}
	return b
}

func _min(a, b int) int {
	if a < b {
		return a
	}
	return b
}
