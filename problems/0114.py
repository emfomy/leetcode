# Source: https://leetcode.com/problems/flatten-binary-tree-to-linked-list
# Title: Flatten Binary Tree to Linked List
# Difficulty: Medium
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given the root of a binary tree, flatten the tree into a "linked list":
#
#   The "linked list" should use the same TreeNode class where the right child pointer points to the next node in the list and the left child pointer is always null.
#   The "linked list" should be in the same order as a pre-order traversal of the binary tree.
#
# Example 1:
#
#   https://assets.leetcode.com/uploads/2021/01/14/flaten.jpg
#
#   Input: root = [1,2,5,3,4,null,6]
#   Output: [1,null,2,null,3,null,4,null,5,null,6]
#
# Example 2:
#
#   Input: root = []
#   Output: []
#
# Example 3:
#
#   Input: root = [0]
#   Output: [0]
#
# Constraints:
#
#   The number of nodes in the tree is in the range [0, 2000].
#   -100 <= Node.val <= 100
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
