# Source: https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal
# Title: Binary Tree Zigzag Level Order Traversal
# Difficulty: Medium
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given the `root` of a binary tree, return the zigzag level order traversal of its nodes' values. (i.e., from left to right, then right to left for the next level and alternate between).
#
# **Example 1:**
# https://assets.leetcode.com/uploads/2021/02/19/tree1.jpg
#
# ```
# Input: root = [3,9,20,null,null,15,7]
# Output: [[3],[20,9],[15,7]]
# ```
#
# **Example 2:**
#
# ```
# Input: root = [1]
# Output: [[1]]
# ```
#
# **Example 3:**
#
# ```
# Input: root = []
# Output: []
# ```
#
# **Constraints:**
#
# - The number of nodes in the tree is in the range `[0, 2000]`.
# - `-100 <= Node.val <= 100`
#
################################################################################################################################

from typing import List, Optional


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def zigzagLevelOrder(self, root: Optional[TreeNode]) -> List[List[int]]:
        if not root:
            return []

        ans = []
        prev = [root]
        isLeft = True
        while prev:
            ans.append([node.val for node in prev])
            curr = []
            if isLeft:
                for node in reversed(prev):
                    if node.right:
                        curr.append(node.right)
                    if node.left:
                        curr.append(node.left)
            else:
                for node in reversed(prev):
                    if node.left:
                        curr.append(node.left)
                    if node.right:
                        curr.append(node.right)
            prev = curr
            isLeft = not isLeft
        return ans
