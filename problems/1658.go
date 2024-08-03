// Source: https://leetcode.com/problems/minimum-operations-to-reduce-x-to-zero
// Title: Minimum Operations to Reduce X to Zero
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array nums and an integer x. In one operation, you can either remove the leftmost or the rightmost element from the array nums and subtract its value from x. Note that this modifies the array for future operations.
//
// Return the minimum number of operations to reduce x to exactly 0 if it is possible, otherwise, return -1.
//
// Example 1:
//
//   Input: nums = [1,1,4,2,3], x = 5
//   Output: 2
//   Explanation: The optimal solution is to remove the last two elements to reduce x to zero.
//
// Example 2:
//
//   Input: nums = [5,6,7,8,9], x = 4
//   Output: -1
//
// Example 3:
//
//   Input: nums = [3,2,20,1,1,3], x = 10
//   Output: 5
//   Explanation: The optimal solution is to remove the last three elements and the first two elements (5 operations in total) to reduce x to zero.
//
// Constraints:
//
//   1 <= nums.length <= 10^5
//   1 <= nums[i] <= 10^4
//   1 <= x <= 10^9
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"math"
)

// Use two pointer
func minOperations(nums []int, x int) int {
	n := len(nums)
	res := math.MaxInt32

	i := 0 // left pointer
	j := n // right pointer
	sum := 0

	// Only pick from left
	for i < j && sum < x {
		sum += nums[i]
		i++
	}
	if sum == x {
		res = _min(res, i)
	}

	// Remove from left if too large, otherwise pick from right
	for i < j {
		if sum >= x {
			if i == 0 {
				break
			}
			i--
			sum -= nums[i]
		} else {
			j--
			sum += nums[j]
		}

		if sum == x {
			res = _min(res, n-j+i)
		}
	}

	if res == math.MaxInt32 {
		return -1
	}
	return res
}

func _min(a, b int) int {
	if a < b {
		return a
	}
	return b
}
