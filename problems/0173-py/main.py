# Source: https://leetcode.com/problems/binary-search-tree-iterator
# Title: Binary Search Tree Iterator
# Difficulty: Medium
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Implement the `BSTIterator` class that represents an iterator over the **in-order traversal** of a binary search tree (BST):
#
# - `BSTIterator(TreeNode root)` Initializes an object of the `BSTIterator` class. The `root` of the BST is given as part of the constructor. The pointer should be initialized to a non-existent number smaller than any element in the BST.
# - `boolean hasNext()` Returns `true` if there exists a number in the traversal to the right of the pointer, otherwise returns `false`.
# - `int next()` Moves the pointer to the right, then returns the number at the pointer.
#
# Notice that by initializing the pointer to a non-existent smallest number, the first call to `next()` will return the smallest element in the BST.
#
# You may assume that `next()` calls will always be valid. That is, there will be at least a next number in the in-order traversal when `next()` is called.
#
# **Example 1:**
# https://assets.leetcode.com/uploads/2018/12/25/bst-tree.png
#
# ```
# Input
#
# ["BSTIterator", "next", "next", "hasNext", "next", "hasNext", "next", "hasNext", "next", "hasNext"]
# [[[7, 3, 15, null, null, 9, 20]], [], [], [], [], [], [], [], [], []]
# Output
#
# [null, 3, 7, true, 9, true, 15, true, 20, false]
#
# Explanation
#
# BSTIterator bSTIterator = new BSTIterator([7, 3, 15, null, null, 9, 20]);
# bSTIterator.next();    // return 3
# bSTIterator.next();    // return 7
# bSTIterator.hasNext(); // return True
# bSTIterator.next();    // return 9
# bSTIterator.hasNext(); // return True
# bSTIterator.next();    // return 15
# bSTIterator.hasNext(); // return True
# bSTIterator.next();    // return 20
# bSTIterator.hasNext(); // return False
# ```
#
# **Constraints:**
#
# - The number of nodes in the tree is in the range `[1, 10^5]`.
# - `0 <= Node.val <= 10^6`
# - At most `10^5` calls will be made to `hasNext`, and `next`.
#
# **Follow up:**
#
# - Could you implement `next()` and `hasNext()` to run in average `O(1)` time and use`O(h)` memory, where `h` is the height of the tree?
#
################################################################################################################################


from collections import deque
from typing import Optional


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class BSTIterator:
    def __init__(self, root: Optional[TreeNode]):
        self.stack = deque([root])

    def next(self) -> int:
        # Find left most child
        node = self.stack.pop()
        while node.left:
            left = node.left
            node.left = None
            self.stack.append(node)
            node = left

        # Push right child
        if node.right:
            self.stack.append(node.right)

        return node.val

    def hasNext(self) -> bool:
        return bool(self.stack)


# Since the tree is Binary Search Tree,
# We can track last returned number so that we won't go to the wrong child
class BSTIterator:
    def __init__(self, root: Optional[TreeNode]):
        self.last = -1
        self.stack = deque([root])

    def next(self) -> int:
        # Find left most child
        node = self.stack.pop()
        while node.left and node.left.val > self.last:
            self.stack.append(node)
            node = node.left

        # Push right child
        if node.right:
            self.stack.append(node.right)

        self.last = node.val
        return node.val

    def hasNext(self) -> bool:
        return bool(self.stack)


# Use build-in iterator
class BSTIterator:
    def __init__(self, root: Optional[TreeNode]):

        def dfs(node: Optional[TreeNode]):
            if not node:
                return
            yield from dfs(node.left)
            yield node.val
            yield from dfs(node.right)

        def iter():
            yield from dfs(root)
            yield None

        self.iter = iter()
        self.curr = next(self.iter)

    def next(self) -> int:
        val = self.curr
        self.curr = next(self.iter)
        return val

    def hasNext(self) -> bool:
        return self.curr is not None
