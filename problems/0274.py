# Source: https://leetcode.com/problems/h-index
# Title: H-Index
# Difficulty: Medium
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given an array of integers `citations` where `citations[i]` is the number of citations a researcher received for their `i^th` paper, return the researcher's h-index.
#
# According to the Wikipedia (https://en.wikipedia.org/wiki/H-index): The h-index is defined as the maximum value of `h` such that the given researcher has published at least `h` papers that have each been cited at least `h` times.
#
# **Example 1:**
#
# ```
# Input: citations = [3,0,6,1,5]
# Output: 3
# Explanation: [3,0,6,1,5] means the researcher has 5 papers in total and each of them had received 3, 0, 6, 1, 5 citations respectively.
# Since the researcher has 3 papers with at least 3 citations each and the remaining two with no more than 3 citations each, their h-index is 3.
# ```
#
# **Example 2:**
#
# ```
# Input: citations = [1,3,1]
# Output: 1
# ```
#
# **Constraints:**
#
# - `n == citations.length`
# - `1 <= n <= 5000`
# - `0 <= citations[i] <= 1000`
#
################################################################################################################################


import heapq
from typing import List


# Use Sort
class Solution:
    def hIndex(self, citations: List[int]) -> int:
        citations.sort(reverse=True)

        for h, cite in enumerate(citations, 1):
            if h > cite:
                return h - 1
        return len(citations)


# Use Heap
class Solution2:
    def hIndex(self, citations: List[int]) -> int:
        n = len(citations)
        citations = [-x for x in citations]
        heapq.heapify(citations)  # max-heap

        for h in range(1, n + 1):
            cite = -heapq.heappop(citations)
            if h > cite:
                return h - 1
        return n


# Use Counting Sort
#
# Now use a counter to count the citations.
# And define s(k) as the sum of all counts with citation >= h;
# That is, s(k) = sum[i>=k] #(cite=i).
# Now we only need to find the maximum k satisfies s(k) >= k
class Solution3:
    def hIndex(self, citations: List[int]) -> int:
        n = len(citations)

        # Count
        counter = [0] * (n + 1)
        for cite in citations:
            counter[min(n, cite)] += 1  # use min to avoid outbound value

        # Find
        k, s = n, counter[n]
        while k > s:
            k -= 1
            s += counter[k]

        return k
