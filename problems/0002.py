# Source: https://leetcode.com/problems/add-two-numbers
# Title: Add Two Numbers
# Difficulty: Medium
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
#
# You may assume that each input would have exactly one solution, and you may not use the same element twice.
#
# You can return the answer in any order.
#
# Example 1:
#
#   Input: nums = [2,7,11,15], target = 9
#   Output: [0,1]
#   Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
#
# Example 2:
#
#   Input: nums = [3,2,4], target = 6
#   Output: [1,2]
#
# Example 3:
#
#   Input: nums = [3,3], target = 6
#   Output: [0,1]
#
# Constraints:
#
#   2 <= nums.length <= 10^4
#   -10^9 <= nums[i] <= 10^9
#   -10^9 <= target <= 10^9
#   Only one valid answer exists.
#
# Follow-up: Can you come up with an algorithm that is less than O(n^2) time complexity?
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
