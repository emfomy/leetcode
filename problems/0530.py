# Source: https://leetcode.com/problems/minimum-absolute-difference-in-bst
# Title: Minimum Absolute Difference in BST
# Difficulty: Easy
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given the `root` of a Binary Search Tree (BST), return the minimum absolute difference between the values of any two different nodes in the tree.
#
# **Example 1:**
# https://assets.leetcode.com/uploads/2021/02/05/bst1.jpg
#
# ```
# Input: root = [4,2,6,1,3]
# Output: 1
# ```
#
# **Example 2:**
# https://assets.leetcode.com/uploads/2021/02/05/bst2.jpg
#
# ```
# Input: root = [1,0,48,null,null,12,49]
# Output: 1
# ```
#
# **Constraints:**
#
# - The number of nodes in the tree is in the range `[2, 10^4]`.
# - `0 <= Node.val <= 10^5`
#
# **Note:** This question is the same as 783: https://leetcode.com/problems/minimum-distance-between-bst-nodes/
#
################################################################################################################################

from typing import Optional


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


# Use FFS + Array
class Solution:
    def getMinimumDifference(self, root: Optional[TreeNode]) -> int:
        vals = []

        def dfs(node: TreeNode):
            if not node:
                return
            dfs(node.left)
            vals.append(node.val)
            dfs(node.right)

        dfs(root)

        n = len(vals)
        ans = int(1e5)
        for i in range(n - 1):
            ans = min(ans, vals[i + 1] - vals[i])

        return ans


# Use DFS
class Solution:
    def getMinimumDifference(self, root: Optional[TreeNode]) -> int:

        ans = int(1e5)

        def dfs(node: TreeNode) -> tuple[int, int]:
            nonlocal ans

            left, right = node.val, node.val
            if node.left:
                leftLeft, leftRight = dfs(node.left)
                ans = min(ans, node.val - leftRight)
                left = leftLeft
            if node.right:
                rightLeft, rightRight = dfs(node.right)
                ans = min(ans, rightLeft - node.val)
                right = rightRight
            return left, right

        dfs(root)

        return ans
