# Source: https://leetcode.com/problems/binary-tree-right-side-view
# Title: Binary Tree Right Side View
# Difficulty: Medium
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given the `root` of a binary tree, imagine yourself standing on the **right side** of it, return the values of the nodes you can see ordered from top to bottom.
#
# **Example 1:**
#
# ```
# Input: root = [1,2,3,null,5,null,4]
# Output: [1,3,4]
# Explanation:
# https://assets.leetcode.com/uploads/2024/11/24/tmpd5jn43fs-1.png
# ```
#
# **Example 2:**
#
# ```
# Input: root = [1,2,3,4,null,null,null,5]
# Output: [1,3,4,5]
# Explanation:
# https://assets.leetcode.com/uploads/2024/11/24/tmpkpe40xeh-1.png
# ```
#
# **Example 3:**
#
# ```
# Input: root = [1,null,3]
# Output: [1,3]
# ```
#
# **Example 4:**
#
# ```
# Input: root = []
# Output: []
# ```
#
# **Constraints:**
#
# - The number of nodes in the tree is in the range `[0, 100]`.
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
    def rightSideView(self, root: Optional[TreeNode]) -> List[int]:
        if not root:
            return []

        ans = []
        prev = [root]
        while prev:
            ans.append(prev[0].val)
            curr = []
            for node in prev:
                if node.right:
                    curr.append(node.right)
                if node.left:
                    curr.append(node.left)
            prev = curr

        return ans
