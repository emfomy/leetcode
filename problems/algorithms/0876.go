// Source: https://leetcode.com/problems/middle-of-the-linked-list/
// Title: Middle of the Linked List
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given the head of a singly linked list, return the middle node of the linked list.
//
// If there are two middle nodes, return the second middle node.
//
// Example 1:
//
//   https://assets.leetcode.com/uploads/2021/07/23/lc-midlist1.jpg
//   Input: head = [1,2,3,4,5]
//   Output: [3,4,5]
//   Explanation: The middle node of the list is node 3.
//
// Example 2:
//
//   https://assets.leetcode.com/uploads/2021/07/23/lc-midlist2.jpg
//   Input: head = [1,2,3,4,5,6]
//   Output: [4,5,6]
//   Explanation: Since the list has two middle nodes with values 3 and 4, we return the second one.
//
// Constraints:
//
//   The number of nodes in the list is in the range [1, 100].
//   1 <= Node.val <= 100
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

type ListNode struct {
	Val  int
	Next *ListNode
}

func middleNode(head *ListNode) *ListNode {
	head2 := head.Next

	for head2 != nil {
		head = head.Next
		head2 = head2.Next
		if head2 != nil {
			head2 = head2.Next
		}
	}

	return head
}
