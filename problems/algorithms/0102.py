# Source: https://leetcode.com/problems/binary-tree-level-order-traversal/
# Title: Binary Tree Level Order Traversal
# Difficulty: Medium
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given the root of a binary tree, return the level order traversal of its nodes' values. (i.e., from left to right, level by level).
#
# Example 1:
#
#   https://assets.leetcode.com/uploads/2021/02/19/tree1.jpg
#
#   Input: root = [3,9,20,null,null,15,7]
#   Output: [[3],[9,20],[15,7]]
#
# Example 2:
#
#   Input: root = [1]
#   Output: [[1]]
#
# Example 3:
#
#   Input: root = []
#   Output: []
#
# Constraints:
#
#   The number of nodes in the tree is in the range [0, 2000].
#   -1000 <= Node.val <= 1000
#
################################################################################################################################

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

from collections import deque

class Solution:
    def levelOrder(self, root: TreeNode) -> List[List[int]]:
        queue = deque([root, None])

        ans = []
        row = []

        while True:
            # Pop node
            root = queue.popleft()
            if root is None:
                if not row:
                    break
                ans.append(row)
                row = []
                queue.append(None)
                continue

            # Push into result
            row.append(root.val)

            # Push next level
            if root.left:
                queue.append(root.left)
            if root.right:
                queue.append(root.right)

        return ans
