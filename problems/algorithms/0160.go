// Source: https://leetcode.com/problems/intersection-of-two-linked-lists/
// Title: Intersection of Two Linked Lists
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given the heads of two singly linked-lists headA and headB, return the node at which the two lists intersect. If the two linked lists have no intersection at all, return null.
//
// For example, the following two linked lists begin to intersect at node c1:
//   https://assets.leetcode.com/uploads/2021/03/05/160_statement.png
//
// The test cases are generated such that there are no cycles anywhere in the entire linked structure.
//
// Note that the linked lists must retain their original structure after the function returns.
//
// Custom Judge:
//
// The inputs to the judge are given as follows (your program is not given these inputs):
//
//   intersectVal - The value of the node where the intersection occurs. This is 0 if there is no intersected node.
//   listA - The first linked list.
//   listB - The second linked list.
//   skipA - The number of nodes to skip ahead in listA (starting from the head) to get to the intersected node.
//   skipB - The number of nodes to skip ahead in listB (starting from the head) to get to the intersected node.
//
// The judge will then create the linked structure based on these inputs and pass the two heads, headA and headB to your program. If you correctly return the intersected node, then your solution will be accepted.
//
// Example 1:
//
//   Input: intersectVal = 8, listA = [4,1,8,4,5], listB = [5,6,1,8,4,5], skipA = 2, skipB = 3
//   Output: Intersected at '8'
//   Explanation:
//     The intersected node's value is 8 (note that this must not be 0 if the two lists intersect).
//     From the head of A, it reads as [4,1,8,4,5]. From the head of B, it reads as [5,6,1,8,4,5]. There are 2 nodes before the intersected node in A; There are 3 nodes before the intersected node in B.
//
// Example 2:
//
//   Input: intersectVal = 2, listA = [1,9,1,2,4], listB = [3,2,4], skipA = 3, skipB = 1
//   Output: Intersected at '2'
//   Explanation:
//     The intersected node's value is 2 (note that this must not be 0 if the two lists intersect).
//     From the head of A, it reads as [1,9,1,2,4]. From the head of B, it reads as [3,2,4]. There are 3 nodes before the intersected node in A; There are 1 node before the intersected node in B.
//
// Example 3:
//
//   Input: intersectVal = 0, listA = [2,6,4], listB = [1,5], skipA = 3, skipB = 2
//   Output: No intersection
//   Explanation:
//     From the head of A, it reads as [2,6,4]. From the head of B, it reads as [1,5]. Since the two lists do not intersect, intersectVal must be 0, while skipA and skipB can be arbitrary values.
//     The two lists do not intersect, so return null.
//
// Constraints:
//
//   The number of nodes of listA is in the m.
//   The number of nodes of listB is in the n.
//   1 <= m, n <= 3 * 10^4
//   1 <= Node.val <= 10^5
//   0 <= skipA < m
//   0 <= skipB < n
//   intersectVal is 0 if listA and listB do not intersect.
//   intersectVal == listA[skipA] == listB[skipB] if listA and listB intersect.
//
// Follow up: Could you write a solution that runs in O(m + n) time and use only O(1) memory?
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import "unsafe"

type ListNode struct {
	Val  int
	Next *ListNode
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Use two runner A & B starting from each head.
// For each runner, go to another head if it reaches the end.
// Stop the algorithm when both runner reach the same node.
// Runner A will run lenA + skipB = skipA + lenC + skipB steps to reach the intersection twice
// Runner B will run lenB + skipA = skipB + lenC + skipA steps to reach the intersection twice
// Note that both runner takes the same steps.
//
// If there is intersection:
//   If skipA == skipB, then the runners will stop at the the first traversal (reaches the intersection)
//   If skipA != skipB, then the runners will stop at the the second traversal (reaches the intersection)
// If there is NO intersection
//   If lenA == lenB, then the runners will stop at the the first traversal (reaches nil)
//   If lenA != lenB, then the runners will stop at the the second traversal (reaches nil)
//
func getIntersectionNode(headA, headB *ListNode) *ListNode {
	runnerA := headA
	runnerB := headB

	for runnerA != runnerB {
		if runnerA == nil { // goto head B if reaches the end
			runnerA = headB
		} else {
			runnerA = runnerA.Next
		}

		if runnerB == nil { // goto head A if reaches the end
			runnerB = headA
		} else {
			runnerB = runnerB.Next
		}
	}

	return runnerA
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Use two runner P & Q starting from the heads A & B.
//       (P) a1 -> a2 -> X -> c1 -> c2
// (Q) b1 -> b2 -> b3 ->
// First, run P and revert the links as you go:
//           a1 <- a2 <- X <- c1 <- c2 (P)
// (Q) b1 -> b2 -> b3 ->
// Next, reverse by Q:
//       (Q) a1 -> a2 -> X <- c1 <- c2 (P)
//     b1 <- b2 <- b3 <-
// Finally, reverse by P again:
//       (Q) a1 -> a2 -> X -> c1 -> c2
// (P) b1 -> b2 -> b3 ->
// Note that P & Q are swapped
//
// In the process, all nodes has been visited exactly twice, while X has been visited three times.
// We may use XOR trick the get the node X.
//
// If there is no X (no intersection), then P will go back to A.
// Therefore we need to reverse Q again to recover the structure.
func getIntersectionNode2(headA, headB *ListNode) *ListNode {
	if headA == headB { // Eage case
		return headA
	}

	runnerP := headA
	runnerQ := headB

	acc := uintptr(unsafe.Pointer(nil))

	runnerP = _reverseLinkList(runnerP, &acc)
	runnerQ = _reverseLinkList(runnerQ, &acc)
	runnerP = _reverseLinkList(runnerP, &acc)
	if runnerP == headA {
		runnerQ = _reverseLinkList(runnerQ, &acc)
		return nil
	}

	return (*ListNode)(unsafe.Pointer(acc))
}

func _reverseLinkList(head *ListNode, acc *uintptr) *ListNode {
	var (
		prevNode *ListNode = nil
		currNode *ListNode = head
	)

	for currNode != nil {
		*acc ^= uintptr(unsafe.Pointer(currNode))
		prevNode, currNode, currNode.Next = currNode, currNode.Next, prevNode
	}

	return prevNode
}
