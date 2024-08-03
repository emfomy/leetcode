# Source: https://leetcode.com/problems/remove-nth-node-from-end-of-list
# Title: Remove Nth Node From End of List
# Difficulty: Medium
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given a linked list, remove the n-th node from the end of list and return its head.
#
# Example:
#
#   Given linked list: 1->2->3->4->5, and n = 2.
#
#   After removing the second node from the end, the linked list becomes 1->2->3->5.
#
# Note:
#
#   Given n will always be valid.
#
# Follow up:
#
#   Could you do this in one pass?
#
################################################################################################################################

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution:
    def removeNthFromEnd(self, head: ListNode, n: int) -> ListNode:
        dummy = ListNode(0)
        dummy.next = head

        first = dummy
        second = dummy
        for _ in range(n):
            first = first.next

        while first:
            first = first.next
            second = second.next

        second.next = second.next.next

        return dummy.next
