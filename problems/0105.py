# Source: https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal
# Title: Construct Binary Tree from Preorder and Inorder Traversal
# Difficulty: Medium
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given preorder and inorder traversal of a tree, construct the binary tree.
#
# Note:
# You may assume that duplicates do not exist in the tree.
#
# For example, given
#
#   preorder = [3,9,20,15,7]
#   inorder = [9,3,15,20,7]
#
# Return the following binary tree:
#
#     3
#    / \
#   9  20
#     /  \
#    15   7
#
################################################################################################################################

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

class Solution:
    """O(n)"""
    def buildTree(self, preorder: List[int], inorder: List[int]) -> TreeNode:

        preorder.reverse()
        inorder.reverse()
        return self.buildTreeInner(preorder, inorder, None)

    def buildTreeInner(self, preorder, inorder, parent_val):

        if not preorder:
            return None

        if inorder[-1] == parent_val:
            inorder.pop()
            return None

        # Create node
        root = TreeNode(val=preorder.pop())

        # Recursive
        root.left = self.buildTreeInner(preorder, inorder, root.val)
        root.right = self.buildTreeInner(preorder, inorder, parent_val)

        return root

class Solution2:
    """O(n)"""
    def buildTree(self, preorder: List[int], inorder: List[int]) -> TreeNode:

        self.preorder = preorder
        self.inorder = inorder
        self.preindex = 0
        self.inindex = 0

        return self.buildTreeInner(None)

    def buildTreeInner(self, parent_val):

        if self.preindex >= len(self.preorder):
            return None

        if self.inorder[self.inindex] == parent_val:
            self.inindex += 1
            return None

        # Create node
        root = TreeNode(val=self.preorder[self.preindex])
        self.preindex += 1

        # Recursive
        root.left = self.buildTreeInner(root.val)
        root.right = self.buildTreeInner(parent_val)

        return root

class Solution3:
    """O(n logn)"""
    def buildTree(self, preorder: List[int], inorder: List[int]) -> TreeNode:

        if not preorder:
            return None

        # Find root node in inorder
        root = TreeNode(val=preorder[0])
        index = inorder.index(root.val)

        # Recursive
        root.left = self.buildTree(preorder[1:index+1], inorder[:index])
        root.right = self.buildTree(preorder[index+1:], inorder[index+1:])

        return root
