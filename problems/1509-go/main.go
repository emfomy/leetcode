// Source: https://leetcode.com/problems/minimum-difference-between-largest-and-smallest-value-in-three-moves
// Title: Minimum Difference Between Largest and Smallest Value in Three Moves
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array nums.
//
// In one move, you can choose one element of nums and change it to any value.
//
// Return the minimum difference between the largest and smallest value of nums after performing at most three moves.
//
// Example 1:
//
//   Input: nums = [5,3,2,4]
//   Output: 0
//   Explanation:
//     We can make at most 3 moves.
//     - In the first move, change 2 to 3. nums becomes [5,3,3,4].
//     - In the second move, change 4 to 3. nums becomes [5,3,3,3].
//     - In the third move, change 5 to 3. nums becomes [3,3,3,3].
//     After performing 3 moves, the difference between the minimum and maximum is 3 - 3 = 0.
//
// Example 2:
//
//   Input: nums = [1,5,0,10,14]
//   Output: 1
//   Explanation:
//     We can make at most 3 moves.
//     - In the first move, change 5 to 0. nums becomes [1,0,0,10,14].
//     - In the second move, change 10 to 0. nums becomes [1,0,0,0,14].
//     - In the third move, change 14 to 1. nums becomes [1,0,0,0,1].
//     After performing 3 moves, the difference between the minimum and maximum is 1 - 0 = 1.
//     It can be shown that there is no way to make the difference 0 in 3 moves.
//
// Example 3:
//
//   Input: nums = [3,100,20]
//   Output: 0
//   Explanation:
//     We can make at most 3 moves.
//     - In the first move, change 100 to 7. nums becomes [3,7,20].
//     - In the second move, change 20 to 7. nums becomes [3,7,7].
//     - In the third move, change 3 to 7. nums becomes [7,7,7].
//     After performing 3 moves, the difference between the minimum and maximum is 7 - 7 = 0.
//
// Constraints:
//
//   1 <= nums.length <= 10^5
//   -10^9 <= nums[i] <= 10^9
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"sort"
)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Assume the (sorted) numbers are [a1, a2, a3, a4, ..., b4, b3, b2, b1]
// The result must be one of (a1-b4), (a2-b3), (a3-b2), (a4-b1)

// Use sort; O(nlogn) time, O(1) space
func minDifference(nums []int) int {
	n := len(nums)
	if n <= 4 {
		return 0
	}

	sort.Ints(nums)

	return min(nums[n-4]-nums[0], nums[n-3]-nums[1], nums[n-2]-nums[2], nums[n-1]-nums[3])
}

// O(n) time, O(1) space
func minDifference2(nums []int) int {
	n := len(nums)
	if n <= 4 {
		return 0
	}

	min1, min2, min3, min4 := int(1e9), int(1e9), int(1e9), int(1e9)
	max1, max2, max3, max4 := int(-1e9), int(-1e9), int(-1e9), int(-1e9)

	for _, n := range nums {
		if n < min1 {
			min1, min2, min3, min4 = n, min1, min2, min3
		} else if n < min2 {
			min2, min3, min4 = n, min2, min3
		} else if n < min3 {
			min3, min4 = n, min3
		} else if n < min4 {
			min4 = n
		}

		if n > max1 {
			max1, max2, max3, max4 = n, max1, max2, max3
		} else if n > max2 {
			max2, max3, max4 = n, max2, max3
		} else if n > max3 {
			max3, max4 = n, max3
		} else if n > max4 {
			max4 = n
		}
	}

	return min(max1-min4, max2-min3, max3-min2, max4-min1)
}
