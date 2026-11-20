# Source: https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree
# Title: Lowest Common Ancestor of a Binary Tree
# Difficulty: Medium
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.
#
# According to the **definition of LCA on Wikipedia**: “The lowest common ancestor is defined between two nodes `p` and `q` as the lowest node in `T` that has both `p` and `q` as descendants (where we allow **a node to be a descendant of itself**).”
#
# **Example 1:**
# https://assets.leetcode.com/uploads/2018/12/14/binarytree.png
#
# ```
# Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
# Output: 3
# Explanation: The LCA of nodes 5 and 1 is 3.
# ```
#
# **Example 2:**
# https://assets.leetcode.com/uploads/2018/12/14/binarytree.png
#
# ```
# Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
# Output: 5
# Explanation: The LCA of nodes 5 and 4 is 5, since a node can be a descendant of itself according to the LCA definition.
# ```
#
# **Example 3:**
#
# ```
# Input: root = [1,2], p = 1, q = 2
# Output: 1
# ```
#
# **Constraints:**
#
# - The number of nodes in the tree is in the range `[2, 10^5]`.
# - `-10^9 <= Node.val <= 10^9`
# - All `Node.val` are **unique**.
# - `p != q`
# - `p` and `q` will exist in the tree.
#
################################################################################################################################


from collections import deque


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def lowestCommonAncestor(
        self, root: TreeNode, p: TreeNode, q: TreeNode
    ) -> TreeNode:
        ans: TreeNode = None

        def dfs(node: TreeNode) -> tuple[int, int]:  # check p, q exist in child
            nonlocal ans

            if not node:
                return False, False

            leftP, leftQ = dfs(node.left)
            rightP, rightQ = dfs(node.right)
            hasP = (node == p) or leftP or rightP
            hasQ = (node == q) or leftQ or rightQ

            if hasP and hasQ:
                if not ans:
                    ans = node
            return hasP, hasQ

        dfs(root)
        return ans


class Solution:
    def lowestCommonAncestor(
        self, root: TreeNode, p: TreeNode, q: TreeNode
    ) -> TreeNode:
        pFound, qFound = False, False
        pStack, qStack = deque(), deque()

        def dfs(node: TreeNode):
            nonlocal pFound, qFound
            if not node:
                return

            if not pFound:
                pStack.append(node)
            if not qFound:
                qStack.append(node)

            if node == p:
                pFound = True
            if node == q:
                qFound = True

            dfs(node.left)
            dfs(node.right)

            if not pFound:
                pStack.pop()
            if not qFound:
                qStack.pop()

        dfs(root)

        ans = root
        for pNode, qNode in zip(pStack, qStack):
            if pNode != qNode:
                break
            ans = pNode

        return ans


class Solution:
    def lowestCommonAncestor(
        self, root: TreeNode, p: TreeNode, q: TreeNode
    ) -> TreeNode:
        if not root or root == p or root == q:
            return root
        left = self.lowestCommonAncestor(root.left, p, q)
        right = self.lowestCommonAncestor(root.right, p, q)
        if left and right:
            return root
        return left or right
