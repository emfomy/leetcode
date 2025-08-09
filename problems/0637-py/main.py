# Source: https://leetcode.com/problems/average-of-levels-in-binary-tree
# Title: Average of Levels in Binary Tree
# Difficulty: Easy
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given the `root` of a binary tree, return the average value of the nodes on each level in the form of an array. Answers within `10^-5` of the actual answer will be accepted.
#
# **Example 1:**
# https://assets.leetcode.com/uploads/2021/03/09/avg1-tree.jpg
#
# ```
# Input: root = [3,9,20,null,null,15,7]
# Output: [3.00000,14.50000,11.00000]
# Explanation: The average value of nodes on level 0 is 3, on level 1 is 14.5, and on level 2 is 11.
# Hence return [3, 14.5, 11].
# ```
#
# **Example 2:**
# https://assets.leetcode.com/uploads/2021/03/09/avg2-tree.jpg
#
# ```
# Input: root = [3,9,20,15,7]
# Output: [3.00000,14.50000,11.00000]
# ```
#
# **Constraints:**
#
# - The number of nodes in the tree is in the range `[1, 10^4]`.
# - `-2^31 <= Node.val <= 2^31 - 1`
#
################################################################################################################################


from typing import List, Optional


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def averageOfLevels(self, root: Optional[TreeNode]) -> List[float]:
        if not root:
            return []

        ans = []
        prev = [root]
        while prev:
            ans.append(sum((node.val for node in prev)) / len(prev))
            curr = []
            for node in prev:
                if node.left:
                    curr.append(node.left)
                if node.right:
                    curr.append(node.right)
            prev = curr
        return ans
