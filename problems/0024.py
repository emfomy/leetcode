# Source: https://leetcode.com/problems/swap-nodes-in-pairs
# Title: Swap Nodes in Pairs
# Difficulty: Medium
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given a linked list, swap every two adjacent nodes and return its head.
#
# You may not modify the values in the list's nodes, only nodes itself may be changed.
#
# Example:
#
#   Given 1->2->3->4, you should return the list as 2->1->4->3.
#
################################################################################################################################

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next

class Solution:
    def swapPairs(self, head: ListNode) -> ListNode:
        dummy = ListNode(0)
        dummy.next = head

        prev = dummy
        node1 = prev.next
        while node1:
            node2 = node1.next
            if not node2:
                break
            prev.next = node2
            node1.next = node2.next
            node2.next = node1

            prev = node1
            node1 = prev.next

        return dummy.next
