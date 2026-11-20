# Source: https://leetcode.com/problems/populating-next-right-pointers-in-each-node-ii
# Title: Populating Next Right Pointers in Each Node II
# Difficulty: Medium
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given a binary tree
#
# ```
# struct Node {
#   int val;
#   Node *left;
#   Node *right;
#   Node *next;
# }
# ```
#
# Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to `NULL`.
#
# Initially, all next pointers are set to `NULL`.
#
# **Example 1:**
# https://assets.leetcode.com/uploads/2019/02/15/117_sample.png
#
# ```
# Input: root = [1,2,3,4,5,null,7]
# Output: [1,#,2,3,#,4,5,7,#]
# Explanation: Given the above binary tree (Figure A), your function should populate each next pointer to point to its next right node, just like in Figure B. The serialized output is in level order as connected by the next pointers, with '#' signifying the end of each level.
# ```
#
# **Example 2:**
#
# ```
# Input: root = []
# Output: []
# ```
#
# **Constraints:**
#
# - The number of nodes in the tree is in the range `[0, 6000]`.
# - `-100 <= Node.val <= 100`
#
# **Follow-up:**
#
# - You may only use constant extra space.
# - The recursive approach is fine. You may assume implicit stack space does not count as extra space for this problem.
#
################################################################################################################################


class Node:
    def __init__(self, val: int = 0, left=None, right=None, next=None):
        self.val = val
        self.left = left
        self.right = right
        self.next = next


# BFS
# O(n) & O(n)
class Solution:
    def connect(self, root: "Node") -> "Node":
        if not root:
            return None

        prevLevel: list[Node] = [root]
        while prevLevel:
            nextLevel: list[Node] = []
            prevNode = None
            for node in prevLevel:
                if not prevNode:
                    prevNode.next = node
                prevNode = node

                if not node.left:
                    nextLevel.append(node.left)
                if not node.right:
                    nextLevel.append(node.right)
            prevLevel = nextLevel

        return root


# BFS
# O(n) & O(1)
class Solution:
    def connect(self, root: "Node") -> "Node":
        if not root:
            return None

        head = root  # left most node
        while head:
            prev = None
            curr = head
            head = None
            while curr:
                prev, head = self._connect(curr.left, prev, head)
                prev, head = self._connect(curr.right, prev, head)
                curr = curr.next

        return root

    def _connect(self, node: "Node", prev: "Node", head: "Node"):
        if not node:
            return prev, head

        if prev:
            prev.next = node
        else:
            head = node
        return node, head
