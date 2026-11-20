# Source: https://leetcode.com/problems/symmetric-tree
# Title: Symmetric Tree
# Difficulty: Easy
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given the `root` of a binary tree, check whether it is a mirror of itself (i.e., symmetric around its center).
#
# **Example 1:**
# https://assets.leetcode.com/uploads/2021/02/19/symtree1.jpg
#
# ```
# Input: root = [1,2,2,3,4,4,3]
# Output: true
# ```
#
# **Example 2:**
# https://assets.leetcode.com/uploads/2021/02/19/symtree2.jpg
#
# ```
# Input: root = [1,2,2,null,3,null,3]
# Output: false
# ```
#
# **Constraints:**
#
# - The number of nodes in the tree is in the range `[1, 1000]`.
# - `-100 <= Node.val <= 100`
#
# **Follow up:** Could you solve it both recursively and iteratively?
#
################################################################################################################################


from typing import Optional


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def isSymmetric(self, root: Optional[TreeNode]) -> bool:
        return self._isSymmetric(root, root)

    def _isSymmetric(self, a: Optional[TreeNode], b: Optional[TreeNode]) -> bool:
        if not a and not b:
            return True

        if not a or not b:
            return False

        return (
            a.val == b.val
            and self._isSymmetric(a.left, b.right)
            and self._isSymmetric(a.right, b.left)
        )
