# Source: https://leetcode.com/problems/word-search
# Title: Word Search
# Difficulty: Medium
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given an m x n board and a word, find if the word exists in the grid.
#
# The word can be constructed from letters of sequentially adjacent cells, where "adjacent" cells are horizontally or vertically neighboring. The same letter cell may not be used more than once.
#
# Example 1:
#
#   Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
#   Output: true
#
# Example 2:
#
#   Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "SEE"
#   Output: true
#
# Example 3:
#   Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCB"
#   Output: false
#
# Constraints:
#
#   m == board.length
#   n = board[i].length
#   1 <= m, n <= 200
#   1 <= word.length <= 10^3
#   board and word consists only of lowercase and uppercase English letters.
#
################################################################################################################################

class Solution:
    def exist(self, board: List[List[str]], word: str) -> bool:
        m, n = len(board), len(board[0])
        visited = [ [False] * n for _ in range(m) ]

        for i in range(m):
            for j in range(n):
                if board[i][j] == word[0]:
                    visited[i][j] = True
                    if self.findNext(m, n, board, visited, i, j, word[1:]):
                        return True
                    visited[i][j] = False
        return False

    def findNext(self, m, n, board, visited, i0, j0, word):
        if not word:
            return True

        for i, j in [
            (i0-1, j0),
            (i0+1, j0),
            (i0, j0-1),
            (i0, j0+1),
        ]:
            if 0 <= i < m and 0 <= j < n and not visited[i][j] and board[i][j] == word[0]:
                visited[i][j] = True
                if self.findNext(m, n, board, visited, i, j, word[1:]):
                    return True
                visited[i][j] = False
