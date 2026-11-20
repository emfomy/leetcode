# Source: https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal
# Title: Construct Binary Tree from Inorder and Postorder Traversal
# Difficulty: Medium
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given two integer arrays `inorder` and `postorder` where `inorder` is the inorder traversal of a binary tree and `postorder` is the postorder traversal of the same tree, construct and return the binary tree.
#
# **Example 1:**
# https://assets.leetcode.com/uploads/2021/02/19/tree.jpg
#
# ```
# Input: inorder = [9,3,15,20,7], postorder = [9,15,7,20,3]
# Output: [3,9,20,null,null,15,7]
# ```
#
# **Example 2:**
#
# ```
# Input: inorder = [-1], postorder = [-1]
# Output: [-1]
# ```
#
# **Constraints:**
#
# - `1 <= inorder.length <= 3000`
# - `postorder.length == inorder.length`
# - `-3000 <= inorder[i], postorder[i] <= 3000`
# - `inorder` and `postorder` consist of **unique** values.
# - Each value of `postorder` also appears in `inorder`.
# - `inorder` is **guaranteed** to be the inorder traversal of the tree.
# - `postorder` is **guaranteed** to be the postorder traversal of the tree.
#
################################################################################################################################


from typing import List, Optional


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


# Divide and Conquer
#
# The last value in `postorder` is the root.
# We may find this not in `inorder`, and split the left and right parts into subtrees.
# Using size of the subtrees, we can also split `postorder` into two parts.
class Solution:
    def buildTree(self, inorder: List[int], postorder: List[int]) -> Optional[TreeNode]:
        if not postorder:
            return None

        root = TreeNode(val=postorder[-1])
        idx = inorder.index(postorder[-1])
        root.left = self.buildTree(inorder[:idx], postorder[:idx])
        root.right = self.buildTree(inorder[idx + 1 :], postorder[idx:-1])
        return root


# Divide and Conquer
# O(n)
#
# Use hash map to store the indices
class Solution:
    def buildTree(self, inorder: List[int], postorder: List[int]) -> Optional[TreeNode]:
        self.inIdxs = {val: idx for idx, val in enumerate(inorder)}
        return self._buildTree(inorder, postorder, 0)

    def _buildTree(
        self, inorder: List[int], postorder: List[int], shift: int
    ) -> Optional[TreeNode]:
        if not postorder:
            return None
        root = TreeNode(val=postorder[-1])
        idx = self.inIdxs[postorder[-1]] - shift
        root.left = self._buildTree(inorder[:idx], postorder[:idx], shift)
        root.right = self._buildTree(
            inorder[idx + 1 :], postorder[idx:-1], shift + idx + 1
        )
        return root
