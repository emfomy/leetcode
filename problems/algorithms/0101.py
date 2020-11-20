# Source: https://leetcode.com/problems/symmetric-tree/
# Title: Symmetric Tree
# Difficulty: Easy
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).
#
# For example, this binary tree [1,2,2,3,4,4,3] is symmetric:
#
#     1
#    / \
#   2   2
#  / \ / \
# 3  4 4  3
#
# But the following [1,2,2,null,3,null,3] is not:
#
#     1
#    / \
#   2   2
#    \   \
#    3    3
#
# Follow up: Solve it both recursively and iteratively.
#
################################################################################################################################

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

class Solution:
    """Iteration"""
    def isSymmetric(self, root: TreeNode) -> bool:
        if root:
            for left, right in zip(self.traversalLeft(root.left), self.traversalRight(root.right)):
                if left != right:
                    return False
        return True

    def traversalLeft(self, root):
        stack = [(None, None,)]
        status = None
        while stack:
            if root:
                if status is None:  # start
                    yield root.val
                    stack.append((root, 'L'))
                    root = root.left
                    status = None
                elif status == 'L': # Left finished
                    stack.append((root, 'R'))
                    root = root.right
                    status = None
                else: # Right finished
                    root, status = stack.pop()
            else:
                yield None
                root, status = stack.pop()

    def traversalRight(self, root):
        stack = [(None, None,)]
        status = None
        while stack:
            if root:
                if status is None:  # start
                    yield root.val
                    stack.append((root, 'R'))
                    root = root.right
                    status = None
                elif status == 'R': # Right finished
                    stack.append((root, 'L'))
                    root = root.left
                    status = None
                else: # Right finished
                    root, status = stack.pop()
            else:
                yield None
                root, status = stack.pop()

################################################################################################################################

class Solution2:
    """Recursion"""
    def isSymmetric(self, root: TreeNode) -> bool:
        if root:
            for left, right in zip(self.traversalLeft(root.left), self.traversalRight(root.right)):
                if left != right:
                    return False
        return True

    def traversalLeft(self, root):
        if root:
            yield root.val
            yield from self.traversalLeft(root.left)
            yield from self.traversalLeft(root.right)
        else:
            yield None

    def traversalRight(self, root):
        if root:
            yield root.val
            yield from self.traversalRight(root.right)
            yield from self.traversalRight(root.left)
        else:
            yield None
