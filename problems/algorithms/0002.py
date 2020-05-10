# Source: https://leetcode.com/problems/add-two-numbers/
# Title: Add Two Numbers
# Difficulty: Medium
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.
#
# You may assume the two numbers do not contain any leading zero, except the number 0 itself.
#
# Example:
#
#   Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
#   Output: 7 -> 0 -> 8
#   Explanation: 342 + 465 = 807.
#
################################################################################################################################

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution:
    def addTwoNumbers(self, l1: ListNode, l2: ListNode, carry: int = 0) -> ListNode:
        if not l1 and not l2:
            return ListNode(carry) if carry else None
        if l1:
            carry += l1.val
            l1 = l1.next
        if l2:
            carry += l2.val
            l2 = l2.next
        l3 = ListNode(carry%10)
        l3.next = self.addTwoNumbers(l1, l2, carry//10);
        return l3

################################################################################################################################

class Solution2:
    def addTwoNumbers(self, l1: ListNode, l2: ListNode) -> ListNode:
        root = ListNode(l1.val + l2.val)
        l3 = root
        l1 = l1.next
        l2 = l2.next
        carry = l3.val // 10
        l3.val %= 10
        while l1 or l2:
            l3.next = ListNode(carry)
            l3 = l3.next
            if l1:
                l3.val += l1.val
                l1 = l1.next
            if l2:
                l3.val += l2.val
                l2 = l2.next
            carry = l3.val // 10
            l3.val %= 10
        if carry:
            l3.next = ListNode(carry)
        return root
