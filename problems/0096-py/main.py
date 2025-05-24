# Source: https://leetcode.com/problems/unique-binary-search-trees
# Title: Unique Binary Search Trees
# Difficulty: Medium
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given an integer n, return the number of structurally unique BST's (binary search trees) which has exactly n nodes of unique values from 1 to n.
#
# Example 1:
#
#   https://assets.leetcode.com/uploads/2021/01/18/uniquebstn3.jpg
#   Input: n = 3
#   Output: 5
#
# Example 2:
#
#   Input: n = 1
#   Output: 1
#
# Constraints:
#
#   1 <= n <= 19
#
################################################################################################################################

class Solution:
    """
    This problem is the same as find unique BST's structure (since there are only one valid way to store 1 ... n in a tree)

    Store the number of BST's of each n in an array.

    Put a node at root, any loop for all possible splits of the (n-1) nodes to left and right children
    i.e. 0 & (n-1), 1 & (n-2), ..., (n-1) & 0 nodes at left and right.
    """
    def numTrees(self, n: int) -> int:

        ans_list = [1] * (n+1)

        for i in range(1, n+1):
            ans_i = 0
            for j in range(i):
                ans_i += ans_list[j] * ans_list[i-1-j]
            ans_list[i] = ans_i

        return ans_list[n]
