// Source: https://leetcode.com/problems/convert-binary-number-in-a-linked-list-to-integer/
// Title: Convert Binary Number in a Linked List to Integer
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given head which is a reference node to a singly-linked list. The value of each node in the linked list is either 0 or 1. The linked list holds the binary representation of a number.
//
// Return the decimal value of the number in the linked list.
//
// Example 1:
//
//   https://assets.leetcode.com/uploads/2019/12/05/graph-1.png
//
//   Input: head = [1,0,1]
//   Output: 5
//   Explanation: (101) in base 2 = (5) in base 10
//
// Example 2:
//
//   Input: head = [0]
//   Output: 0
//
// Constraints:
//
//   The Linked List is not empty.
//   Number of nodes will not exceed 30.
//   Each node's value is either 0 or 1.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

type ListNode struct {
	Val  int
	Next *ListNode
}

func getDecimalValue(head *ListNode) int {
	res := 0
	for head != nil {
		res <<= 1
		res += head.Val
		head = head.Next
	}

	return res
}
