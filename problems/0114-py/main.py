# Source: https://leetcode.com/problems/flatten-binary-tree-to-linked-list
# Title: Flatten Binary Tree to Linked List
# Difficulty: Medium
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given the `root` of a binary tree, flatten the tree into a "linked list":
#
# - The "linked list" should use the same `TreeNode` class where the `right` child pointer points to the next node in the list and the `left` child pointer is always `null`.
# - The "linked list" should be in the same order as a **pre-order traversal** of the binary tree.
#
# **Example 1:**
# https://assets.leetcode.com/uploads/2021/01/14/flaten.jpg
#
# ```
# Input: root = [1,2,5,3,4,null,6]
# Output: [1,null,2,null,3,null,4,null,5,null,6]
# ```
#
# **Example 2:**
#
# ```
# Input: root = []
# Output: []
# ```
#
# **Example 3:**
#
# ```
# Input: root = [0]
# Output: [0]
# ```
#
# **Constraints:**
#
# - The number of nodes in the tree is in the range `[0, 2000]`.
# - `-100 <= Node.val <= 100`
#
# **Follow up:** Can you flatten the tree in-place (with `O(1)` extra space)?
#
################################################################################################################################


from typing import Optional


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


# Recursion
# O(n) & O(n)
class Solution:
    def flatten(self, root: Optional[TreeNode]) -> None:
        if not root:
            return
        self._flatten(root)

    # Returns last node
    def _flatten(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        left, right = root.left, root.right
        if left:
            root.left = None
            root.right = left
            root = self._flatten(left)
        if right:
            root.right = right
            root = self._flatten(right)
        return root


# Loop
# O(n) & O(1)
class Solution:
    def flatten(self, root: Optional[TreeNode]) -> None:
        if not root:
            return

        while root:
            if root.left:
                tail = root.left
                while tail.right:
                    tail = tail.right
                tail.right = root.right
                root.right = root.left
                root.left = None
            root = root.right
