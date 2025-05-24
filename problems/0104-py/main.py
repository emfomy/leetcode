# Source: https://leetcode.com/problems/maximum-depth-of-binary-tree
# Title: Maximum Depth of Binary Tree
# Difficulty: Easy
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given the root of a binary tree, return its maximum depth.
#
# A binary tree's maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.
#
# Example 1:
#
#   https://assets.leetcode.com/uploads/2020/11/26/tmp-tree.jpg
#   Input: root = [3,9,20,null,null,15,7]
#   Output: 3
#
# Example 2:
#
#   Input: root = [1,null,2]
#   Output: 2
#
# Constraints:
#
#   The number of nodes in the tree is in the range [0, 10^4].
#   -100 <= Node.val <= 100
#
################################################################################################################################

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def maxDepth(self, root: TreeNode) -> int:
        if not root:
            return 0
        left_depth = self.maxDepth(root.left)
        right_depth = self.maxDepth(root.right)
        return max(left_depth, right_depth) + 1
