// Source: https://leetcode.com/problems/construct-binary-tree-from-preorder-and-postorder-traversal
// Title: Construct Binary Tree from Preorder and Postorder Traversal
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given two integer arrays, `preorder` and `postorder` where `preorder` is the preorder traversal of a binary tree of **distinct** values and `postorder` is the postorder traversal of the same tree, reconstruct and return the binary tree.
//
// If there exist multiple answers, you can **return any** of them.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/07/24/lc-prepost.jpg
//
// ```
// Input: preorder = [1,2,4,5,3,6,7], postorder = [4,5,2,6,7,3,1]
// Output: [1,2,3,4,5,6,7]
// ```
//
// **Example 2:**
//
// ```
// Input: preorder = [1], postorder = [1]
// Output: [1]
// ```
//
// **Constraints:**
//
// - `1 <= preorder.length <= 30`
// - `1 <= preorder[i] <= preorder.length`
// - All the values of `preorder` are **unique**.
// - `postorder.length == preorder.length`
// - `1 <= postorder[i] <= postorder.length`
// - All the values of `postorder` are **unique**.
// - It is guaranteed that `preorder` and `postorder` are the preorder traversal and postorder traversal of the same binary tree.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"fmt"
	"strings"
)

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

// Use stack
func constructFromPrePost(preorder []int, postorder []int) *TreeNode {
	n := len(preorder)

	stack := make([]*TreeNode, n)
	stack[0] = &TreeNode{Val: preorder[0]}
	stackIdx := 0
	fmt.Println("+", preorder[0], 0)

	preIdx, postIdx := 1, 0
	for preIdx < n {
		for postIdx < n && postorder[postIdx] == stack[stackIdx].Val {
			postIdx++
			stackIdx--
		}

		node := &TreeNode{Val: preorder[preIdx]}
		if stack[stackIdx].Left == nil {
			stack[stackIdx].Left = node
		} else {
			stack[stackIdx].Right = node
		}
		preIdx++
		stackIdx++
		stack[stackIdx] = node
	}

	return stack[0]
}

// Use divide and concour
func constructFromPrePost2(preorder []int, postorder []int) *TreeNode {
	n := len(preorder)

	if n == 0 {
		return nil
	}

	root := &TreeNode{Val: preorder[0]}

	if n == 1 {
		return root
	}

	leftVal := preorder[1]
	leftCount := 0
	for ; leftCount < n; leftCount++ {
		if postorder[leftCount] == leftVal {
			break
		}
	}
	leftCount++

	root.Left = constructFromPrePost2(preorder[1:(1+leftCount)], postorder[:leftCount])
	root.Right = constructFromPrePost2(preorder[(1+leftCount):], postorder[leftCount:n-1])
	return root
}

func main() {
	tree := constructFromPrePost2(
		[]int{1, 2, 4, 5, 3, 6, 7},
		[]int{4, 5, 2, 6, 7, 3, 1},
	)
	printTree(tree, 0)
}

func printTree(node *TreeNode, depth int) {
	fmt.Printf("%s%d\n", strings.Repeat("\t", depth), node.Val)
	if node.Left != nil {
		printTree(node.Left, depth+1)
	}
	if node.Right != nil {
		printTree(node.Right, depth+1)
	}
}
