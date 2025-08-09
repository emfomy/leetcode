# Source: https://leetcode.com/problems/generate-parentheses
# Title: Generate Parentheses
# Difficulty: Medium
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given `n` pairs of parentheses, write a function to generate all combinations of well-formed parentheses.
#
# **Example 1:**
#
# ```
# Input: n = 3
# Output: ["((()))","(()())","(())()","()(())","()()()"]
# ```
#
# **Example 2:**
#
# ```
# Input: n = 1
# Output: ["()"]
# ```
#
# **Constraints:**
#
# - `1 <= n <= 8`
#
################################################################################################################################

from typing import List


class Solution:
    # Divide & Conquer
    #
    # First we know that the first character must be `(`.
    # We can split the string into (xxx)yyy, where `)` is the corresponding parenthesis.
    # Here xxx and yyy are both valid parentheses.
    def generateParenthesis(self, n: int) -> List[str]:
        if n == 0:
            return [""]

        ans = []

        for i in range(n):
            lefts = self.generateParenthesis(i)
            rights = self.generateParenthesis(n - i - 1)
            for left in lefts:
                for right in rights:
                    ans.append(f"({left}){right}")

        return ans


class Solution:
    # DP
    #
    # First we know that the first character must be `(`.
    # We can split the string into (xxx)yyy, where `)` is the corresponding parenthesis.
    # Here xxx and yyy are both valid parentheses.
    def generateParenthesis(self, n: int) -> List[str]:
        ansList = [[] for _ in range(n + 1)]
        ansList[0].append("")

        for m in range(n + 1):
            for i in range(m):
                for left in ansList[i]:
                    for right in ansList[m - i - 1]:
                        ansList[m].append(f"({left}){right}")

        return ansList[n]
