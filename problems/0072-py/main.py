# Source: https://leetcode.com/problems/edit-distance
# Title: Edit Distance
# Difficulty: Hard
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given two strings word1 and word2, return the minimum number of operations required to convert word1 to word2.
#
# You have the following three operations permitted on a word:
#
#   Insert a character
#   Delete a character
#   Replace a character
#
# Example 1:
#
#   Input: word1 = "horse", word2 = "ros"
#   Output: 3
#   Explanation:
#     horse -> rorse (replace 'h' with 'r')
#     rorse -> rose (remove 'r')
#     rose -> ros (remove 'e')
#
# Example 2:
#
#   Input: word1 = "intention", word2 = "execution"
#   Output: 5
#   Explanation:
#     intention -> inention (remove 't')
#     inention -> enention (replace 'i' with 'e')
#     enention -> exention (replace 'n' with 'x')
#     exention -> exection (replace 'n' with 'c')
#     exection -> execution (insert 'u')
#
# Constraints:
#
#   0 <= word1.length, word2.length <= 500
#   word1 and word2 consist of lowercase English letters.
#
################################################################################################################################

class Solution:
    """
    Needleman–Wunsch algorithm
    Time: O(mn); Space: O(m) or O(n)
    """
    def minDistance(self, word1: str, word2: str) -> int:

        n = len(word1)+1
        m = len(word2)+1

        if n < m:
            n, m = m, n
            word1, word2 = word2, word1

        # Initialize first row
        score = list(range(m))

        # Update matrix
        for i, c1 in enumerate(word1, 1):
            diag = i-1
            score[0] = i
            for j, c2 in enumerate(word2, 1):
                newscore = min(
                    score[j-1],  # Insert
                    score[j],    # Delete
                    diag - (c1 == c2),  # Replace/No Change
                ) + 1
                diag = score[j]
                score[j] = newscore

        return score[-1]

################################################################################################################################

class Solution1:
    """
    Needleman–Wunsch algorithm
    Time: O(mn); Space: O(mn)
    """
    def minDistance(self, word1: str, word2: str) -> int:

        n = len(word1)+1
        m = len(word2)+1

        # Create empty (n+1)x(m+1) matrix
        score = [None]*n
        for i in range(n):
            score[i] = [0]*m

        # Initialize first row and column
        score[0][0] = 0
        for i in range(1, n):
            score[i][0] = i
        for j in range(1, m):
            score[0][j] = j

        # Update matrix
        for i, c1 in enumerate(word1, 1):
            for j, c2 in enumerate(word2, 1):
                score[i][j] = min(
                    score[i][j-1],  # Insert
                    score[i-1][j],  # Delete
                    score[i-1][j-1] - (c1 == c2),  # Replace/No Change
                ) + 1

        return score[-1][-1]

################################################################################################################################

from collections import deque

class Solution2:
    """Find using BFS"""
    def minDistance(self, word1: str, word2: str) -> int:
        queue = deque([(0, word1,)])
        vocab = set(word2)
        visited = set()

        while True:
            ops, word = queue.popleft()
            newops = ops+1
            visited.add(word)

            # Insert 0
            for newchar in vocab:
                newword = list(word)
                newword.insert(0, newchar)
                newword = ''.join(newword)
                if newword == word2:
                    return newops
                if newword not in visited:
                    queue.append((newops, newword,))

            for i, char in enumerate(word):
                # Insert
                for newchar in vocab:
                    newword = list(word)
                    newword.insert(i+1, newchar)
                    newword = ''.join(newword)
                    if newword == word2:
                        return newops
                    if newword not in visited:
                        queue.append((newops, newword,))

                # Delete
                newword = list(word)
                del newword[i]
                newword = ''.join(newword)
                if newword == word2:
                    return newops
                if newword not in visited:
                    queue.append((newops, newword,))

                # Replace
                for newchar in vocab:
                    if newchar != char:
                        newword = list(word)
                        newword[i] = newchar
                        newword = ''.join(newword)
                        if newword == word2:
                            return newops
                        if newword not in visited:
                            queue.append((newops, newword,))
