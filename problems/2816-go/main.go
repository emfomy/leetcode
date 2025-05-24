// Source: https://leetcode.com/problems/double-a-number-represented-as-a-linked-list
// Title: Double a Number Represented as a Linked List
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given the head of a non-empty linked list representing a non-negative integer without leading zeroes.
// Return the head of the linked list after doubling it.
//
// Example 1:
//
//   https://assets.leetcode.com/uploads/2023/05/28/example.png
//
//   Input: head = [1,8,9]
//   Output: [3,7,8]
//   Explanation: The figure above corresponds to the given linked list which represents the number 189. Hence, the returned linked list represents the number 189 * 2 = 378.
//
// Example 2:
//
//   https://assets.leetcode.com/uploads/2023/05/28/example2.png
//
//   Input: head = [9,9,9]
//   Output: [1,9,9,8]
//   Explanation: The figure above corresponds to the given linked list which represents the number 999. Hence, the returned linked list reprersents the number 999 * 2 = 1998.
//
// Constraints:
//
//   The number of nodes in the list is in the range [1, 10^4]
//   0 <= Node.val <= 9
//   The input is generated such that the list represents a number that does not have leading zeros, except the number 0 itself.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

type ListNode struct {
	Val  int
	Next *ListNode
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Use reverse
func doubleIt(head *ListNode) *ListNode {
	head = _reverse(head)

	curr := head
	carry := 0
	for {
		curr.Val = curr.Val*2 + carry
		carry = curr.Val / 10
		curr.Val %= 10
		if curr.Next == nil {
			break
		}
		curr = curr.Next
	}
	if carry > 0 {
		curr.Next = &ListNode{
			Val: carry,
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Double pointer
func doubleIt2(head *ListNode) *ListNode {
	// Prepend 0
	head = &ListNode{
		Val:  0,
		Next: head,
	}

	// Double
	var prev, curr = head, head.Next
	for curr != nil {
		curr.Val *= 2
		prev.Val += curr.Val / 10
		curr.Val %= 10
		prev, curr = curr, curr.Next
	}

	// Remove leading 0
	if head.Val == 0 {
		head = head.Next
	}

	return head
}
