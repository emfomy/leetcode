// Source: https://leetcode.com/problems/special-array-ii
// Title: Special Array II
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// An array is considered **special** if every pair of its adjacent elements contains two numbers with different parity.
//
// You are given an array of integer `nums` and a 2D integer matrix `queries`, where for `queries[i] = [from_i, to_i]` your task is to check that <div aria-expanded="false" data-headlessui-state="" id="headlessui-popover-button-:ro:">subarray<div style="position: fixed; z-index: 40; inset: 0px auto auto 0px; transform: translate(310px, 262px);"> `nums[from_i..to_i]` is **special** or not.
//
// Return an array of booleans `answer` such that `answer[i]` is `true` if `nums[from_i..to_i]` is special.
//
// **Example 1:**
//
// Input: nums = [3,4,1,2,6], queries = [[0,4]]
//
// Output: [false]
//
// Explanation:
//
// The subarray is `[3,4,1,2,6]`. 2 and 6 are both even.
//
// **Example 2:**
//
// Input: nums = [4,3,1,6], queries = [[0,2],[2,3]]
//
// Output: [false,true]
//
// Explanation:
//
// - The subarray is `[4,3,1]`. 3 and 1 are both odd. So the answer to this query is `false`.
// - The subarray is `[1,6]`. There is only one pair: `(1,6)` and it contains numbers with different parity. So the answer to this query is `true`.
//
// **Constraints:**
//
// - `1 <= nums.length <= 10^5`
// - `1 <= nums[i] <= 10^5`
// - `1 <= queries.length <= 10^5`
// - `queries[i].length == 2`
// - `0 <= queries[i][0] <= queries[i][1] <= nums.length - 1`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func isArraySpecial(nums []int, queries [][]int) []bool {
	n := len(nums)

	groups := make([]int, n)
	group := 0
	for i := 1; i < n; i++ {
		if nums[i]%2 == nums[i-1]%2 { // not special
			group++
		}
		groups[i] = group
	}

	res := make([]bool, len(queries))
	for i, query := range queries {
		from, to := query[0], query[1]
		res[i] = (groups[from] == groups[to])
	}

	return res
}
