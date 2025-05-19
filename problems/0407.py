# Source: https://leetcode.com/problems/trapping-rain-water-ii
# Title: Trapping Rain Water II
# Difficulty: Medium
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given an `m x n` integer matrix `heightMap` representing the height of each unit cell in a 2D elevation map, return the volume of water it can trap after raining.
#
# **Example 1:**
# https://assets.leetcode.com/uploads/2021/04/08/trap1-3d.jpg
#
# ```
# Input: heightMap = [[1,4,3,1,3,2],[3,2,1,3,2,4],[2,3,3,2,3,1]]
# Output: 4
# Explanation: After the rain, water is trapped between the blocks.
# We have two small ponds 1 and 3 units trapped.
# The total volume of water trapped is 4.
# ```
#
# **Example 2:**
# https://assets.leetcode.com/uploads/2021/04/08/trap2-3d.jpg
#
# ```
# Input: heightMap = [[3,3,3,3,3],[3,2,2,2,3],[3,2,1,2,3],[3,2,2,2,3],[3,3,3,3,3]]
# Output: 10
# ```
#
# **Constraints:**
#
# - `m == heightMap.length`
# - `n == heightMap[i].length`
# - `1 <= m, n <= 200`
# - `0 <= heightMap[i][j] <= 2 * 10^4`
#
################################################################################################################################

import heapq


# BFS + heap
class Solution:
    def trapRainWater(self, heightMap: list[list[int]]) -> int:
        m, n = len(heightMap), len(heightMap[0])

        dirs = [
            (-1, 0),
            (1, 0),
            (0, -1),
            (0, 1),
        ]

        # Track visited
        visited = [[False] * n for _ in range(m)]

        # Min-heap for boundary
        boundary: list[tuple[int, int, int]] = []
        for i in [0, m - 1]:
            for j in range(n):
                boundary.append((heightMap[i][j], i, j))
                visited[i][j] = True
        for j in [0, n - 1]:
            for i in range(1, m - 1):
                boundary.append((heightMap[i][j], i, j))
                visited[i][j] = True
        heapq.heapify(boundary)

        totalWater = 0
        while boundary:
            currVal, currI, currJ = heapq.heappop(boundary)
            for dI, dJ in dirs:
                nextI, nextJ = currI + dI, currJ + dJ

                if not (0 <= nextI < m and 0 <= nextJ < n):
                    continue
                if visited[nextI][nextJ]:
                    continue

                nextVal = heightMap[nextI][nextJ]
                totalWater += max(currVal - nextVal, 0)

                heapq.heappush(boundary, (max(currVal, nextVal), nextI, nextJ))
                visited[nextI][nextJ] = True

        return totalWater


# BFS + heap
#
# Use `-1`` on `heightMap` for visited
# Use stack for each height
class Solution2:
    def trapRainWater(self, heightMap: list[list[int]]) -> int:
        m, n = len(heightMap), len(heightMap[0])

        dirs = [
            (-1, 0),
            (1, 0),
            (0, -1),
            (0, 1),
        ]

        # Min-heap for boundary
        boundary: list[tuple[int, int, int]] = []
        for i in [0, m - 1]:
            for j in range(n):
                boundary.append((heightMap[i][j], i, j))
                heightMap[i][j] = -1
        for j in [0, n - 1]:
            for i in range(1, m - 1):
                boundary.append((heightMap[i][j], i, j))
                heightMap[i][j] = -1
        heapq.heapify(boundary)

        totalWater = 0
        while boundary:
            currVal, i, j = heapq.heappop(boundary)
            stack = [(i, j)]
            while boundary and boundary[0][0] == currVal:
                _, i, j = heapq.heappop(boundary)
                stack.append((i, j))

            while stack:
                currI, currJ = stack.pop()
                for dI, dJ in dirs:
                    nextI, nextJ = currI + dI, currJ + dJ

                    if not (0 <= nextI < m and 0 <= nextJ < n):
                        continue
                    if heightMap[nextI][nextJ] < 0:
                        continue

                    nextVal = heightMap[nextI][nextJ]
                    heightMap[nextI][nextJ] = -1
                    if currVal > nextVal:
                        totalWater += currVal - nextVal
                        stack.append((nextI, nextJ))
                    else:
                        heapq.heappush(boundary, (nextVal, nextI, nextJ))

        return totalWater


print(
    Solution2.trapRainWater(
        None,
        [[5, 5, 5, 1], [5, 1, 1, 5], [5, 1, 5, 5], [5, 2, 5, 8]],
    )
)
