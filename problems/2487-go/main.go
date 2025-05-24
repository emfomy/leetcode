// Source: https://leetcode.com/problems/remove-nodes-from-linked-list
// Title: Remove Nodes From Linked List
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given the head of a linked list.
// Remove every node which has a node with a greater value anywhere to the right side of it.
// Return the head of the modified linked list.
//
// Example 1:
//
//   Input: head = [5,2,13,3,8]
//   Output: [13,8]
//   Explanation: The nodes that should be removed are 5, 2 and 3.
//     - Node 13 is to the right of node 5.
//     - Node 13 is to the right of node 2.
//     - Node 8 is to the right of node 3.
//
// Example 2:
//
//   Input: head = [1,1,1,1]
//   Output: [1,1,1,1]
//   Explanation: Every node has value 1, so no nodes are removed.
//
// Constraints:
//
//   The number of the nodes in the given list is in the range [1, 10^5].
//   1 <= Node.val <= 10^5
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

type ListNode struct {
	Val  int
	Next *ListNode
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Use reverse
func removeNodes(head *ListNode) *ListNode {
	head = _reverse(head)

	maxVal := head.Val
	var prev, curr = head, head.Next
	for curr != nil {
		if curr.Val >= maxVal {
			maxVal = curr.Val
			prev, curr = curr, curr.Next
		} else {
			prev.Next = curr.Next
			curr = curr.Next
		}
	}

	head = _reverse(head)
	return head
}

func _reverse(head *ListNode) *ListNode {
	prev := (*ListNode)(nil)
	curr := head

	for curr != nil {
		next := curr.Next
		curr.Next = prev
		prev, curr = curr, next
	}

	return prev
}
