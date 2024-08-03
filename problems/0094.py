# Source: https://leetcode.com/problems/binary-tree-inorder-traversal
# Title: Binary Tree Inorder Traversal
# Difficulty: Medium
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given the root of a binary tree, return the inorder traversal of its nodes' values.
#
# Example 1:
#
#   Input: root = [1,null,2,3]
#   Output: [1,3,2]
#
# Example 2:
#
#   Input: root = []
#   Output: []
#
# Example 3:
#
#   Input: root = [1]
#   Output: [1]
#
# Example 4:
#
#   Input: root = [1,2]
#   Output: [2,1]
#
# Example 5:
#
#   Input: root = [1,null,2]
#   Output: [1,2]
#
# Constraints:
#
#   The number of nodes in the tree is in the range [0, 100].
#   -100 <= Node.val <= 100
#
# Follow up:
#
#   Recursive solution is trivial, could you do it iteratively?
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
    def inorderTraversal(self, root: TreeNode) -> List[int]:

        stack = [(None, None,)]
        status = None
        while stack:
            if root:
                if status is None:  # start
                    stack.append((root, 'L'))
                    root = root.left
                    status = None
                elif status == 'L': # Left finished
                    yield root.val
                    stack.append((root, 'R'))
                    root = root.right
                    status = None
                else: # Right finished
                    root, status = stack.pop()
            else:
                root, status = stack.pop()

################################################################################################################################

class Solution2:
    """Recursion"""
    def inorderTraversal(self, root: TreeNode) -> List[int]:
        if root:
            yield from self.inorderTraversal(root.left)
            yield root.val
            yield from self.inorderTraversal(root.right)
