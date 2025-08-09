# Source: https://leetcode.com/problems/same-tree
# Title: Same Tree
# Difficulty: Easy
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given the roots of two binary trees `p` and `q`, write a function to check if they are the same or not.
#
# Two binary trees are considered the same if they are structurally identical, and the nodes have the same value.
#
# **Example 1:**
# https://assets.leetcode.com/uploads/2020/12/20/ex1.jpg
#
# ```
# Input: p = [1,2,3], q = [1,2,3]
# Output: true
# ```
#
# **Example 2:**
# https://assets.leetcode.com/uploads/2020/12/20/ex2.jpg
#
# ```
# Input: p = [1,2], q = [1,null,2]
# Output: false
# ```
#
# **Example 3:**
# https://assets.leetcode.com/uploads/2020/12/20/ex3.jpg
#
# ```
# Input: p = [1,2,1], q = [1,1,2]
# Output: false
# ```
#
# **Constraints:**
#
# - The number of nodes in both trees is in the range `[0, 100]`.
# - `-10^4 <= Node.val <= 10^4`
#
################################################################################################################################


from typing import Optional


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def isSameTree(self, p: Optional[TreeNode], q: Optional[TreeNode]) -> bool:
        if not p and not q:
            return True

        if not p or not q:
            return False

        return (
            p.val == q.val
            and self.isSameTree(p.left, q.left)
            and self.isSameTree(p.right, q.right)
        )
