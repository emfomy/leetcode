# Source: https://leetcode.com/problems/flatten-binary-tree-to-linked-list/
# Title: Flatten Binary Tree to Linked List
# Difficulty: Medium
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given a binary tree, flatten it to a linked list in-place.
#
# For example, given the following tree:
#
#     1
#    / \
#   2   5
#  / \   \
# 3   4   6
#
# The flattened tree should look like:
#
# 1
#  \
#   2
#    \
#     3
#      \
#       4
#        \
#         5
#          \
#           6
#
################################################################################################################################

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

class Solution:

    def __init__(self):
        self.prev = None

    def flatten(self, root: TreeNode) -> None:
        """
        Do not return anything, modify root in-place instead.
        """
        if not root:
            return

        self.flatten(root.right)
        self.flatten(root.left)
        root.right = self.prev
        root.left = None
        self.prev = root

################################################################################################################################

class Solution2:
    def flatten(self, root: TreeNode) -> None:
        """
        Do not return anything, modify root in-place instead.
        """

        self.flattenInner(root)

    def flattenInner(self, root):
        if not root:
            return None

        # Flatten right
        right_end = self.flattenInner(root.right)

        # Flatten left
        left_end = self.flattenInner(root.left)

        # Move right to end of left, move left to right
        if left_end:
            left_end.right = root.right
            root.right = root.left
            root.left = None

        return right_end or left_end or root
