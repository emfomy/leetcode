# Source: https://leetcode.com/problems/minimum-genetic-mutation
# Title: Minimum Genetic Mutation
# Difficulty: Medium
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given the `root` of a binary search tree, and an integer `k`, return the `k^th` smallest value (**1-indexed**) of all the values of the nodes in the tree.
#
# **Example 1:**
# https://assets.leetcode.com/uploads/2021/01/28/kthtree1.jpg
#
# ```
# Input: root = [3,1,4,null,2], k = 1
# Output: 1
# ```
#
# **Example 2:**
# https://assets.leetcode.com/uploads/2021/01/28/kthtree2.jpg
#
# ```
# Input: root = [5,3,6,2,4,null,null,1], k = 3
# Output: 3
# ```
#
# **Constraints:**
#
# - The number of nodes in the tree is `n`.
# - `1 <= k <= n <= 10^4`
# - `0 <= Node.val <= 10^4`
#
# **Follow up:** If the BST is modified often (i.e., we can do insert and delete operations) and you need to find the kth smallest frequently, how would you optimize?
#
################################################################################################################################


from collections import defaultdict, deque
from typing import List


# Create Graph
class Solution:
    def minMutation(self, startGene: str, endGene: str, bank: List[str]) -> int:
        def diff(str1: str, str2: str) -> int:
            return sum((int(ch1 != ch2) for ch1, ch2 in zip(str1, str2)))

        # Prepare graph
        graph: defaultdict[str, list[str]] = defaultdict(list)
        for gene in bank:
            if diff(startGene, gene) == 1:
                graph[startGene].append(gene)
                graph[gene].append(startGene)
        for i, gene1 in enumerate(bank):
            for gene2 in bank[:i]:
                if diff(gene1, gene2) == 1:
                    graph[gene1].append(gene2)
                    graph[gene2].append(gene1)

        # BFS
        visited: defaultdict[str, bool] = defaultdict(bool)
        queue: deque[tuple[str, int]] = deque()  # node, dist
        queue.append((startGene, 0))
        visited[startGene] = True

        while queue:
            head, dist = queue.popleft()
            for gene in graph[head]:
                if gene == endGene:
                    return dist + 1
                if not visited[gene]:
                    visited[gene] = True
                    queue.append((gene, dist + 1))

        return -1
