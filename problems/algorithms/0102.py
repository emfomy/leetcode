# Source: https://leetcode.com/problems/binary-tree-level-order-traversal/
# Title: Binary Tree Level Order Traversal
# Difficulty: Medium
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given a binary tree, return the level order traversal of its nodes' values. (ie, from left to right, level by level).
#
# For example:
# Given binary tree [3,9,20,null,null,15,7],
#
#     3
#    / \
#   9  20
#     /  \
#    15   7
#
# return its level order traversal as:
#
# [
#   [3],
#   [9,20],
#   [15,7]
# ]
#
################################################################################################################################

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

from collections import deque

class Solution:
    def levelOrder(self, root: TreeNode) -> List[List[int]]:
        queue = deque([root, None])

        ans = []
        row = []

        while True:
            # Pop node
            root = queue.popleft()
            if root is None:
                if not row:
                    break
                ans.append(row)
                row = []
                queue.append(None)
                continue

            # Push into result
            row.append(root.val)

            # Push next level
            if root.left:
                queue.append(root.left)
            if root.right:
                queue.append(root.right)

        return ans
