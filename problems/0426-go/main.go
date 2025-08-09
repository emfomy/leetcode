// Source: https://leetcode.com/problems/convert-binary-search-tree-to-sorted-doubly-linked-list
// Title: Convert Binary Search Tree to Sorted Doubly Linked List
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Convert a **Binary Search Tree** to a sorted **Circular Doubly-Linked List** in place.
//
// You can think of the left and right pointers as synonymous to the predecessor and successor pointers in a doubly-linked list. For a circular doubly linked list, the predecessor of the first element is the last element, and the successor of the last element is the first element.
//
// We want to do the transformation **in place**. After the transformation, the left pointer of the tree node should point to its predecessor, and the right pointer should point to its successor. You should return the pointer to the smallest element of the linked list.
//
// **Example 1:**
//
// https://assets.leetcode.com/uploads/2018/10/12/bstdlloriginalbst.png
//
// ```
// Input: root = [4,2,5,1,3]
//
// https://assets.leetcode.com/uploads/2018/10/12/bstdllreturndll.png
// Output: [1,2,3,4,5]
//
// Explanation: The figure below shows the transformed BST. The solid line indicates the successor relationship, while the dashed line means the predecessor relationship.
// https://assets.leetcode.com/uploads/2018/10/12/bstdllreturnbst.png
// ```
//
// **Example 2:**
//
// ```
// Input: root = [2,1,3]
// Output: [1,2,3]
// ```
//
// **Constraints:**
//
// - The number of nodes in the tree is in the range `[0, 2000]`.
// - `-1000 <= Node.val <= 1000`
// - All the values of the tree are **unique**.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

type Node struct {
	Val   int
	Left  *Node
	Right *Node
}

// Use DFS
func treeToDoublyList(root *Node) *Node {
	if root == nil {
		return nil
	}

	// DFS
	var dfs func(node *Node) (*Node, *Node) // return left/right most node
	dfs = func(node *Node) (*Node, *Node) {
		left, right := node, node
		if node.Left != nil {
			leftLeft, leftRight := dfs(node.Left)
			leftRight.Right = node
			node.Left = leftRight
			left = leftLeft
		}
		if node.Right != nil {
			rightLeft, rightRight := dfs(node.Right)
			rightLeft.Left = node
			node.Right = rightLeft
			right = rightRight
		}

		return left, right
	}

	left, right := dfs(root)
	left.Left = right
	right.Right = left

	return left
}

// Use DFS + Extra Space
func treeToDoublyList2(root *Node) *Node {
	if root == nil {
		return nil
	}

	var nodes []*Node

	// DFS
	var dfs func(node *Node)
	dfs = func(node *Node) {
		if node == nil {
			return
		}

		dfs(node.Left)
		nodes = append(nodes, node)
		dfs(node.Right)
	}
	dfs(root)

	// Build linked list
	n := len(nodes)
	for i := range n {
		nodes[i].Right = nodes[(i+1)%n]
		nodes[(i+1)%n].Left = nodes[i]
	}

	return nodes[0]
}
