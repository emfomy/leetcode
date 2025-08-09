# Source: https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal
# Title: Construct Binary Tree from Preorder and Inorder Traversal
# Difficulty: Medium
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given two integer arrays `preorder` and `inorder` where `preorder` is the preorder traversal of a binary tree and `inorder` is the inorder traversal of the same tree, construct and return the binary tree.
#
# **Example 1:**
# https://assets.leetcode.com/uploads/2021/02/19/tree.jpg
#
# ```
# Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
# Output: [3,9,20,null,null,15,7]
# ```
#
# **Example 2:**
#
# ```
# Input: preorder = [-1], inorder = [-1]
# Output: [-1]
# ```
#
# **Constraints:**
#
# - `1 <= preorder.length <= 3000`
# - `inorder.length == preorder.length`
# - `-3000 <= preorder[i], inorder[i] <= 3000`
# - `preorder` and `inorder` consist of **unique** values.
# - Each value of `inorder` also appears in `preorder`.
# - `preorder` is **guaranteed** to be the preorder traversal of the tree.
# - `inorder` is **guaranteed** to be the inorder traversal of the tree.
#
################################################################################################################################


from typing import List, Optional


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


# Divide and Conquer
# O(n logn)
#
# The first value in `preorder` is the root.
# We may find this not in `inorder`, and split the left and right parts into subtrees.
# Using size of the subtrees, we can also split `preorder` into two parts.
class Solution:
    def buildTree(self, preorder: List[int], inorder: List[int]) -> Optional[TreeNode]:
        if not preorder:
            return None
        root = TreeNode(val=preorder[0])
        idx = inorder.index(preorder[0])
        root.left = self.buildTree(preorder[1 : idx + 1], inorder[:idx])
        root.right = self.buildTree(preorder[idx + 1 :], inorder[idx + 1 :])
        return root


# Divide and Conquer
# O(n)
#
# Use hash map to store the indices
class Solution:
    def buildTree(self, preorder: List[int], inorder: List[int]) -> Optional[TreeNode]:
        self.inIdxs = {val: idx for idx, val in enumerate(inorder)}
        return self._buildTree(preorder, inorder, 0)

    def _buildTree(
        self, preorder: List[int], inorder: List[int], shift: int
    ) -> Optional[TreeNode]:
        if not preorder:
            return None
        root = TreeNode(val=preorder[0])
        idx = self.inIdxs[preorder[0]] - shift
        root.left = self._buildTree(preorder[1 : idx + 1], inorder[:idx], shift + 0)
        root.right = self._buildTree(
            preorder[idx + 1 :], inorder[idx + 1 :], shift + idx + 1
        )
        return root
