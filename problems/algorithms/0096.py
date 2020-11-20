# Source: https://leetcode.com/problems/unique-binary-search-trees/
# Title: Unique Binary Search Trees
# Difficulty: Medium
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given n, how many structurally unique BST's (binary search trees) that store values 1 ... n?
#
# Example:
#
#   Input: 3
#   Output: 5
#   Explanation:
#   Given n = 3, there are a total of 5 unique BST's:
#
#      1         3     3      2      1
#       \       /     /      / \      \
#        3     2     1      1   3      2
#       /     /       \                 \
#      2     1         2                 3
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
