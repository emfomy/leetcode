# Source: https://leetcode.com/problems/generate-parentheses
# Title: Generate Parentheses
# Difficulty: Medium
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.
#
# For example, given n = 3, a solution set is:
#
#   [
#     "((()))",
#     "(()())",
#     "(())()",
#     "()(())",
#     "()()()"
#   ]
#
################################################################################################################################

class Solution:
    def generateParenthesis(self, n: int) -> List[str]:

        if n == 0:
            yield ''
            return

        for m in range(n):
            for left in self.generateParenthesis(m):
                for right in self.generateParenthesis(n-m-1):
                    yield f'({left}){right}'

################################################################################################################################

from itertools import product

class Solution2:
    def generateParenthesis(self, n: int) -> List[str]:

        if n == 0:
            yield ''
            return

        if n == 1:
            yield '()'
            return

        for m in range(1, n+1):
            yield from self.generateParenthesisBase(n, m)

    def generateParenthesisBase(self, n: int, m: int):

        for ls in product(*(range(n-m+1) for _ in range(m))):
            if sum(ls) != n-m:
                continue

            template = '({})'*m
            for subp in product(*map(self.generateParenthesis, ls)):
                yield template.format(*subp)

