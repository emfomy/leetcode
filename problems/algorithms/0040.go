// Source: https://leetcode.com/problems/combination-sum-ii/
// Title: Combination Sum II
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a collection of candidate numbers (candidates) and a target number (target), find all unique combinations in candidates where the candidate numbers sum to target.
//
// Each number in candidates may only be used once in the combination.
//
// Note: The solution set must not contain duplicate combinations.
//
// Example 1:
//
//   Input: candidates = [10,1,2,7,6,1,5], target = 8
//   Output:
//     [
//       [1,1,6],
//       [1,2,5],
//       [1,7],
//       [2,6]
//     ]
//
// Example 2:
//
//   Input: candidates = [2,5,2,1,2], target = 5
//   Output:
//     [
//       [1,2,2],
//       [5]
//     ]
//
// Constraints:
//
//   1 <= candidates.length <= 100
//   1 <= candidates[i] <= 50
//   1 <= target <= 30
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func combinationSum2(candidates []int, target int) [][]int {
	candidateMap := make(map[int]int, len(candidates)) // map candidate to its numbers
	for _, num := range candidates {
		candidateMap[num]++
	}
	nums := make([]int, 0, len(candidateMap))
	counts := make([]int, 0, len(candidateMap))
	for num, count := range candidateMap {
		nums = append(nums, num)
		counts = append(counts, count)
	}

	res := make([][]int, 0)
	_combinationSum2(nums, counts, 0, target, &res)
	return res
}

func _combinationSum2(nums, counts []int, idx int, target int, res *[][]int, solution ...int) {
	if target < 0 {
		return
	}
	if target == 0 {
		*res = append(*res, append([]int{}, solution...))
		return
	}

	solution = append(solution, 0)
	for i := idx; i < len(nums); i++ {
		count := counts[i]
		if count == 0 {
			continue
		}

		num := nums[i]
		solution[len(solution)-1] = num
		counts[i]--
		_combinationSum2(nums, counts, i, target-num, res, solution...)
		counts[i]++
	}
}
