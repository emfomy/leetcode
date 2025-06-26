// Source: https://leetcode.com/problems/equal-tree-partition
// Title: Equal Tree Partition
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given the `root` of a binary tree, return `true` if you can partition the tree into two trees with equal sums of values after removing exactly one edge on the original tree.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/05/03/split1-tree.jpg
//
// ```
// Input: root = [5,10,10,null,null,2,3]
// Output: true
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2021/05/03/split2-tree.jpg
//
// ```
// Input: root = [1,2,10,null,null,2,20]
// Output: false
// Explanation: You cannot split the tree into two trees with equal sums after removing exactly one edge on the tree.
// ```
//
// **Constraints:**
//
// - The number of nodes in the tree is in the range `[1, 10^4]`.
// - `-10^5 <= Node.val <= 10^5`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

// We first find the sum of every subtree.
//
// Say `T` is the tree.
// Say `e` is an edge above a subtree `S`.
// We can compute the other tree as sum(T-S) = sum(T) - sum(S).
func checkEqualTree(root *TreeNode) bool {
	// Find sum of the whole tree
	var sumTree func(node *TreeNode) int
	sumTree = func(node *TreeNode) int {
		if node == nil {
			return 0
		}
		return node.Val + sumTree(node.Left) + sumTree(node.Right)
	}
	totalSum := sumTree(root)

	// Check subtree split
	ans := false
	var checkTree func(node *TreeNode) int
	checkTree = func(node *TreeNode) int {
		if ans { // early stop
			return 0
		}
		if node == nil {
			return 0
		}
		sum := node.Val + checkTree(node.Left) + checkTree(node.Right)
		if node != root && sum*2 == totalSum { // root node doesn't have parent edge
			ans = true
		}
		return sum
	}
	checkTree(root)

	return ans
}

// Use stack
func checkEqualTree2(root *TreeNode) bool {
	var sums []int // all subtree sum

	// Find sum of the whole tree
	var sumTree func(node *TreeNode) int
	sumTree = func(node *TreeNode) int {
		if node == nil {
			return 0
		}
		sum := node.Val + sumTree(node.Left) + sumTree(node.Right)
		if node != root { // root node doesn't have parent edge
			sums = append(sums, sum)
		}
		return sum
	}

	totalSum := sumTree(root)

	for _, sum := range sums {
		if sum*2 == totalSum {
			return true
		}
	}
	return false
}
