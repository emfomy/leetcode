// Source: https://leetcode.com/problems/delete-n-nodes-after-m-nodes-of-a-linked-list
// Title: Delete N Nodes After M Nodes of a Linked List
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given the `head` of a linked list and two integers `m` and `n`.
//
// Traverse the linked list and remove some nodes in the following way:
//
// - Start with the head as the current node.
// - Keep the first `m` nodes starting with the current node.
// - Remove the next `n` nodes
// - Keep repeating steps 2 and 3 until you reach the end of the list.
//
// Return the head of the modified list after removing the mentioned nodes.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2020/06/06/sample_1_1848.png
//
// ```
// Input: head = [1,2,3,4,5,6,7,8,9,10,11,12,13], m = 2, n = 3
// Output: [1,2,6,7,11,12]
// Explanation: Keep the first (m = 2) nodes starting from the head of the linked List  (1 ->2) show in black nodes.
// Delete the next (n = 3) nodes (3 -> 4 -> 5) show in read nodes.
// Continue with the same procedure until reaching the tail of the Linked List.
// Head of the linked list after removing nodes is returned.
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2020/06/06/sample_2_1848.png
//
// ```
// Input: head = [1,2,3,4,5,6,7,8,9,10,11], m = 1, n = 3
// Output: [1,5,9]
// Explanation: Head of linked list after removing nodes is returned.
// ```
//
// **Constraints:**
//
// - The number of nodes in the list is in the range `[1, 10^4]`.
// - `1 <= Node.val <= 10^6`
// - `1 <= m, n <= 1000`
//
// **Follow up:** Could you solve this problem by modifying the list in-place?
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

type ListNode struct {
	Val  int
	Next *ListNode
}

func deleteNodes(head *ListNode, m int, n int) *ListNode {
	curr := head

	jump := func(node *ListNode, k int) *ListNode {
		for range k {
			if node == nil {
				break
			}
			node = node.Next
		}
		return node
	}

	for {
		// Keep m
		curr = jump(curr, m-1)
		if curr == nil {
			break
		}

		// Skip n
		next := jump(curr, n+1)
		curr.Next = next
		curr = next
		if curr == nil {
			break
		}
	}

	return head
}
