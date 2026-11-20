# Source: https://leetcode.com/problems/binary-tree-maximum-path-sum
# Title: Binary Tree Maximum Path Sum
# Difficulty: Hard
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# A **path** in a binary tree is a sequence of nodes where each pair of adjacent nodes in the sequence has an edge connecting them. A node can only appear in the sequence **at most once**. Note that the path does not need to pass through the root.
#
# The **path sum** of a path is the sum of the node's values in the path.
#
# Given the `root` of a binary tree, return the maximum **path sum** of any **non-empty** path.
#
# **Example 1:**
# https://assets.leetcode.com/uploads/2020/10/13/exx1.jpg
#
# ```
# Input: root = [1,2,3]
# Output: 6
# Explanation: The optimal path is 2 -> 1 -> 3 with a path sum of 2 + 1 + 3 = 6.
# ```
#
# **Example 2:**
# https://assets.leetcode.com/uploads/2020/10/13/exx2.jpg
#
# ```
# Input: root = [-10,9,20,null,null,15,7]
# Output: 42
# Explanation: The optimal path is 15 -> 20 -> 7 with a path sum of 15 + 20 + 7 = 42.
# ```
#
# **Constraints:**
#
# - The number of nodes in the tree is in the range `[1, 3 * 10^4]`.
# - `-1000 <= Node.val <= 1000`
#
################################################################################################################################


from typing import Optional


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


# Use DFS
#
# For each node, compute the max sum of path includes left and right child.
# Use DFS to find max of all above sum.
class Solution:
    def maxPathSum(self, root: Optional[TreeNode]) -> int:
        ans = root.val

        def dfs(node: Optional[TreeNode]) -> int:
            nonlocal ans

            if not node:
                return 0

            # If child sum if negative, just remove them and use only current node
            leftSum = max(dfs(node.left), 0)
            rightSum = max(dfs(node.right), 0)

            ans = max(ans, node.val + leftSum + rightSum)

            return node.val + max(leftSum, rightSum)

        dfs(root)
        return ans
