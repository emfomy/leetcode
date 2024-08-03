// Source: https://leetcode.com/problems/reverse-linked-list
// Title: Reverse Linked List
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given the head of a singly linked list, reverse the list, and return the reversed list.
//
// Example 1:
//
//   https://assets.leetcode.com/uploads/2021/02/19/rev1ex1.jpg
//
//   Input: head = [1,2,3,4,5]
//   Output: [5,4,3,2,1]
//
// Example 2:
//
//   https://assets.leetcode.com/uploads/2021/02/19/rev1ex2.jpg
//
//   Input: head = [1,2]
//   Output: [2,1]
//
// Example 3:
//
//   Input: head = []
//   Output: []
//
// Constraints:
//
//   The number of nodes in the list is the range [0, 5000].
//   -5000 <= Node.val <= 5000
//
// Follow up: A linked list can be reversed either iteratively or recursively. Could you implement both?
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

type ListNode struct {
	Val  int
	Next *ListNode
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Use recursion
func reverseList(head *ListNode) *ListNode {
	return _reverseList(head, nil)
}

func _reverseList(head *ListNode, prev *ListNode) *ListNode {
	if head == nil {
		return prev
	}

	newHead := _reverseList(head.Next, head)
	head.Next = prev
	return newHead
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Use iteration
func reverseList2(head *ListNode) *ListNode {
	prev := (*ListNode)(nil)
	curr := head

	for curr != nil {
		next := curr.Next
		curr.Next = prev
		prev, curr = curr, next
	}

	return prev
}
