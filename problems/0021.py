# Source: https://leetcode.com/problems/merge-two-sorted-lists
# Title: Merge Two Sorted Lists
# Difficulty: Easy
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Merge two sorted linked lists and return it as a new list. The new list should be made by splicing together the nodes of the first two lists.
#
# Example:
#
#   Input: 1->2->4, 1->3->4
#   Output: 1->1->2->3->4->4
#
################################################################################################################################

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution:
    def mergeTwoLists(self, l1: ListNode, l2: ListNode) -> ListNode:
        dummy = ListNode(0)
        cur = dummy

        while True:
            if l1 and l2:
                if l1.val < l2.val:
                    cur.next = l1
                    cur = l1
                    l1 = l1.next
                else:
                    cur.next = l2
                    cur = l2
                    l2 = l2.next
                continue

            if not l1:
                cur.next = l2

            if not l2:
                cur.next = l1

            return dummy.next
