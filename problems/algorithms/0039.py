# Source: https://leetcode.com/problems/combination-sum/
# Title: Combination Sum
# Difficulty: Medium
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given a set of candidate numbers (candidates) (without duplicates) and a target number (target), find all unique combinations in candidates where the candidate numbers sums to target. You may return the combinations in any order.
#
# The same number may be chosen from candidates an unlimited number of times. Two combinations are unique if the frequency of at least one of the chosen numbers is different.
#
# It is guaranteed that the number of unique combinations that sum up to target is less than 150 combinations for the given input.
#
# Note:
#
# - All numbers (including target) will be positive integers.
# - The solution set must not contain duplicate combinations.
#
# Example 1:
#
#   Input: candidates = [2,3,6,7], target = 7
#   Output: [[2,2,3],[7]]
#   Explanation:
#     2 and 3 are candidates, and 2 + 2 + 3 = 7. Note that 2 can be used multiple times.
#     7 is a candidate, and 7 = 7.
#     These are the only two combinations.
#
# Example 2:
#
#   Input: candidates = [2,3,5], target = 8
#   Output: [[2,2,2,2],[2,3,3],[3,5]]
#
# Example 3:
#
#   Input: candidates = [2], target = 1
#   Output: []
#
# Example 4:
#
#   Input: candidates = [1], target = 1
#   Output: [[1]]
#
# Example 5:
#
#   Input: candidates = [1], target = 2
#   Output: [[1,1]]
#
################################################################################################################################

class Solution:
    def combinationSum(self, candidates: List[int], target: int) -> List[List[int]]:
        candidates.sort(reverse=True)
        yield from self.combinationSumInner(candidates, target)

    def combinationSumInner(self, candidates, target, *solution):
        if target <= 0:
            if target == 0:
                yield solution
            return

        prev = solution[-1] if solution else -1
        for i, c in enumerate(candidates):
            yield from self.combinationSumInner(candidates[i:], target-c, *solution, c)
