// Source: https://leetcode.com/problems/add-two-numbers/
// Title: Add Two Numbers
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.
//
// You may assume the two numbers do not contain any leading zero, except the number 0 itself.
//
// Example:
//
//   Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
//   Output: 7 -> 0 -> 8
//   Explanation: 342 + 465 = 807.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// Definition for singly-linked list.
type ListNode struct {
	Val  int
	Next *ListNode
}

func addTwoNumbers(l1 *ListNode, l2 *ListNode) *ListNode {
	root := &ListNode{Val: l1.Val + l2.Val}

	l3 := root
	l1 = l1.Next
	l2 = l2.Next

	carry := l3.Val / 10
	l3.Val %= 10

	for l1 != nil || l2 != nil {
		l3.Next = &ListNode{Val: carry}
		l3 = l3.Next
		if l1 != nil {
			l3.Val += l1.Val
			l1 = l1.Next
		}
		if l2 != nil {
			l3.Val += l2.Val
			l2 = l2.Next
		}
		carry = l3.Val / 10
		l3.Val %= 10
	}

	if carry != 0 {
		l3.Next = &ListNode{Val: carry}
	}

	return root
}
