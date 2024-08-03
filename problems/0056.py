# Source: https://leetcode.com/problems/merge-intervals
# Title: Merge Intervals
# Difficulty: Medium
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given a collection of intervals, merge all overlapping intervals.
#
# Example 1:
#
#   Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
#   Output: [[1,6],[8,10],[15,18]]
#   Explanation: Since intervals [1,3] and [2,6] overlaps, merge them into [1,6].
#
# Example 2:
#
#   Input: intervals = [[1,4],[4,5]]
#   Output: [[1,5]]
#   Explanation: Intervals [1,4] and [4,5] are considered overlapping.
#
# NOTE: input types have been changed on April 15, 2019. Please reset to default code definition to get new method signature.
#
# Constraints:
#
#   intervals[i][0] <= intervals[i][1]
#
################################################################################################################################

class Solution:
    def merge(self, intervals: List[List[int]]) -> List[List[int]]:
        # Sort intervals
        intervals.sort(key=lambda interval: interval[0])

        res = []
        cache = None
        for cur in intervals:
            if cache and cur[0] <= cache[1]:
                cache[1] = max(cache[1], cur[1])
            else:
                cache = cur
                res.append(cur)

        return res
