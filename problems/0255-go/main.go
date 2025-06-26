// Source: https://leetcode.com/problems/verify-preorder-sequence-in-binary-search-tree
// Title: Verify Preorder Sequence in Binary Search Tree
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array of **unique** integers `preorder`, return `true` if it is the correct preorder traversal sequence of a binary search tree.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/03/12/preorder-tree.jpg
//
// ```
// Input: preorder = [5,2,1,3,6]
// Output: true
// ```
//
// **Example 2:**
//
// ```
// Input: preorder = [5,2,6,1,3]
// Output: false
// ```
//
// **Constraints:**
//
// - `1 <= preorder.length <= 10^4`
// - `1 <= preorder[i] <= 10^4`
// - All the elements of `preorder` are **unique**.
//
// **Follow up:** Could you do it using only constant space complexity?
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// Use stack
//
// Lemma: (trivial to prove)
// Given a binary tree `T`. Pick any any node `V`.
// If we replace the subtree rooted at `V` by the subtree rooted at either child node of `V`,
// the tree is still a binary tree.
//
// Using above lemma, we can maintain a stack of left children.
// Whenever a node is larger then the head of the stack (i.e. is larger than its parent),
// we pop the head from the stack (i.e. replace the parent by this node).
// Also, whenever we pop a node from the stack, any new node should be larger then this node (since new node must be at right of the popped node).
func verifyPreorder(preorder []int) bool {
	n := len(preorder)

	stack := make([]int, 0, n+1)
	stack = append(stack, 1e5) // add an extra node as root (avoid empty check of the stack)
	minVal := 0

	for _, node := range preorder {
		if node < minVal { // too small
			return false
		}

		for node > stack[len(stack)-1] { // pop parent
			minVal = stack[len(stack)-1]
			stack = stack[:len(stack)-1]
		}

		// push
		stack = append(stack, node)
	}

	return true
}
