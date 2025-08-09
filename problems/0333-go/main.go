// Source: https://leetcode.com/problems/largest-bst-subtree
// Title: Largest BST Subtree
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given the root of a binary tree, find the largest **subtree**, which is also a Binary Search Tree (BST), where the largest means subtree has the largest number of nodes.
//
// A **subtree** of treeName is a tree consisting of a node in treeName and all of its descendants.
//
// A **Binary Search Tree (BST)** is a tree in which all the nodes follow the below-mentioned properties:
//
// - The left subtree values are less than the value of their parent (root) node's value.
// - The right subtree values are greater than the value of their parent (root) node's value.
//
// **Note:** A subtree must include all of its descendants.
//
// **Example 1:**
//
// https://assets.leetcode.com/uploads/2020/10/17/tmp.jpg
//
// ```
// Input: root = [10,5,15,1,8,null,7]
// Output: 3
// Explanation: The Largest BST Subtree in this case is the highlighted one. The return value is the subtree's size, which is 3.```
//
// **Example 2:**
//
// ```
// Input: root = [4,2,7,2,3,5,null,2,null,null,null,null,null,1]
// Output: 2
// ```
//
// **Constraints:**
//
// - The number of nodes in the tree is in the range `[0, 10^4]`.
// - `-10^4 <= Node.val <= 10^4`
//
// **Follow up:** Can you figure out ways to solve it with `O(n)` time complexity?
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func largestBSTSubtree(root *TreeNode) int {
	if root == nil {
		return 0
	}

	ans := 0

	var dfs func(node *TreeNode) (ok bool, size int, left int, right int) // node must not be nil
	dfs = func(node *TreeNode) (bool, int, int, int) {
		ok, size, left, right := true, 1, node.Val, node.Val
		if node.Left != nil {
			leftOk, leftSize, leftLeft, leftRight := dfs(node.Left)
			size += leftSize
			left = leftLeft
			if !leftOk || leftRight >= node.Val {
				ok = false
			}
		}
		if node.Right != nil {
			rightOk, rightSize, rightLeft, rightRight := dfs(node.Right)
			size += rightSize
			right = rightRight
			if !rightOk || rightLeft <= node.Val {
				ok = false
			}
		}
		if ok {
			ans = max(ans, size)
		}
		return ok, size, left, right
	}
	dfs(root)

	return ans
}
