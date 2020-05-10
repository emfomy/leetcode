# Source: https://leetcode.com/problems/merge-k-sorted-lists/
# Title: Merge k Sorted Lists
# Difficulty: Hard
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.
#
# Example:
#
#   Input:
#   [
#     1->4->5,
#     1->3->4,
#     2->6
#   ]
#   Output: 1->1->2->3->4->4->5->6
#
################################################################################################################################

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next

class Solution:
    def mergeKLists(self, lists: List[ListNode]) -> ListNode:
        dummy = ListNode(0)
        cur = dummy

        lists = list(filter(None, lists))

        while True:
            if not lists:
                return dummy.next

            i, head = min(enumerate(lists), key=self.keyfunc)
            cur.next = head
            cur = head
            if head.next:
                lists[i] = head.next
            else:
                del lists[i]

    @staticmethod
    def keyfunc(args):
        return args[1].val
