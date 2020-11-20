# Source: https://leetcode.com/problems/validate-binary-search-tree/
# Title: Validate Binary Search Tree
# Difficulty: Medium
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given a binary tree, determine if it is a valid binary search tree (BST).
#
# Assume a BST is defined as follows:
#
# The left subtree of a node contains only nodes with keys less than the node's key.
# The right subtree of a node contains only nodes with keys greater than the node's key.
# Both the left and right subtrees must also be binary search trees.
#
# Example:
#
#       2
#      / \
#     1   3
#
#   Input: [2,1,3]
#   Output: true
#
# Example 2:
#
#       5
#      / \
#     1   4
#        / \
#       3   6
#
#   Input: [5,1,4,null,null,3,6]
#   Output: false
#   Explanation: The root node's value is 5 but its right child's value is 4.
#
################################################################################################################################

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

class Solution:
    def isValidBST(self, root: TreeNode) -> bool:
        if not root:
            return True

        valid, _, _ = self.isValidBSTInner(root)
        return valid

    def isValidBSTInner(self, root):
        # Check left
        if root.left:
            left_valid, left_min, left_max = self.isValidBSTInner(root.left)
            if not (left_valid and left_max < root.val):
                return False, None, None
        else:
            left_min = root.val

        # Check right
        if root.right:
            right_valid, right_min, right_max = self.isValidBSTInner(root.right)
            if not (right_valid and root.val < right_min):
                return False, None, None
        else:
            right_max = root.val

        return True, left_min, right_max
