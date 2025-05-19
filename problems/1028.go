// Source: https://leetcode.com/problems/recover-a-tree-from-preorder-traversal
// Title: Recover a Tree From Preorder Traversal
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// We run a pre order depth-first search (DFS) on the `root` of a binary tree.
//
// At each node in this traversal, we output `D` dashes (where `D` is the depth of this node), then we output the value of this node. If the depth of a node is `D`, the depth of its immediate child is `D + 1`. The depth of the `root` node is `0`.
//
// If a node has only one child, that child is guaranteed to be **the left child**.
//
// Given the output `traversal` of this traversal, recover the tree and return its `root`.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2024/09/10/recover_tree_ex1.png
//
// ```
// Input: traversal = "1-2--3--4-5--6--7"
// Output: [1,2,5,3,4,6,7]
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2024/09/10/recover_tree_ex2.png
//
// ```
// Input: traversal = "1-2--3---4-5--6---7"
// Output: [1,2,5,3,null,6,null,4,null,7]
// ```
//
// **Example 3:**
// https://assets.leetcode.com/uploads/2024/09/10/recover_tree_ex3.png
//
// ```
// Input: traversal = "1-401--349---90--88"
// Output: [1,401,null,349,88,90]
// ```
//
// **Constraints:**
//
// - The number of nodes in the original tree is in the range `[1, 1000]`.
// - `1 <= Node.val <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"fmt"
	"strconv"
)

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func recoverFromPreorder(traversal string) *TreeNode {
	values, depths := _parseTraversal(traversal)
	n := len(values)

	stack := make([]*TreeNode, len(depths))
	stack[0] = &TreeNode{Val: values[0]}
	stackDepth := 0

	for i := 1; i < n; i++ {
		value, depth := values[i], depths[i]

		node := &TreeNode{Val: value}
		for stackDepth >= depth {
			stackDepth--
		}
		fmt.Println(value, depth, stackDepth)
		if stack[stackDepth].Left == nil {
			stack[stackDepth].Left = node
		} else {
			stack[stackDepth].Right = node
		}
		stackDepth++
		stack[stackDepth] = node
	}

	return stack[0]
}

// Return the values and the depths of each node
func _parseTraversal(traversal string) ([]int, []int) {
	n := len(traversal)

	values := make([]int, 0, n)
	depths := make([]int, 0, n)
	depths = append(depths, 0)

	var digits []byte
	var dashs []byte
	for i := range n {
		ch := traversal[i]
		if ch != '-' {
			if len(dashs) > 0 {
				depths = append(depths, len(dashs))
				dashs = nil
			}
			digits = append(digits, ch)
		} else {
			if len(digits) > 0 {
				value, _ := strconv.Atoi(string(digits))
				values = append(values, value)
				digits = nil
			}
			dashs = append(dashs, ch)
		}
	}
	value, _ := strconv.Atoi(string(digits))
	values = append(values, value)

	return values, depths
}
