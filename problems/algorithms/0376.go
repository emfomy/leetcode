// Source: https://leetcode.com/problems/wiggle-subsequence/
// Title: Wiggle Subsequence
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// A wiggle sequence is a sequence where the differences between successive numbers strictly alternate between positive and negative. The first difference (if one exists) may be either positive or negative. A sequence with one element and a sequence with two non-equal elements are trivially wiggle sequences.
//
//   For example, [1, 7, 4, 9, 2, 5] is a wiggle sequence because the differences (6, -3, 5, -7, 3) alternate between positive and negative.
//   In contrast, [1, 4, 7, 2, 5] and [1, 7, 4, 5, 5] are not wiggle sequences. The first is not because its first two differences are positive, and the second is not because its last difference is zero.
//
// A subsequence is obtained by deleting some elements (possibly zero) from the original sequence, leaving the remaining elements in their original order.
//
// Given an integer array nums, return the length of the longest wiggle subsequence of nums.
//
// Example 1:
//
//   Input: nums = [1,7,4,9,2,5]
//   Output: 6
//   Explanation: The entire sequence is a wiggle sequence with differences (6, -3, 5, -7, 3).
//
// Example 2:
//
//   Input: nums = [1,17,5,10,13,15,10,5,16,8]
//   Output: 7
//   Explanation:
//     There are several subsequences that achieve this length.
//     One is [1, 17, 10, 13, 10, 16, 8] with differences (16, -7, 3, -3, 6, -8).
//
// Example 3:
//
//   Input: nums = [1,2,3,4,5,6,7,8,9]
//   Output: 2
//
// Constraints:
//
//   1 <= nums.length <= 1000
//   0 <= nums[i] <= 1000
//
// Follow up: Could you solve this in O(n) time?
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Use DP
// Time: O(n^2); Space: O(n)
func wiggleMaxLength(nums []int) int {
	n := len(nums)

	pos := make([]int, n) // length of subsequence ends here with positive difference at last
	neg := make([]int, n) // length of subsequence ends here with negative difference at last
	for i := 0; i < n; i++ {
		pos[i] = 1
		neg[i] = 1
	}

	for i := 0; i < n; i++ {
		for j := 0; j < i; j++ {
			if nums[i] > nums[j] && pos[i] <= neg[j] {
				pos[i] = neg[j] + 1
			} else if nums[i] < nums[j] && neg[i] <= pos[j] {
				neg[i] = pos[j] + 1
			}
		}
	}

	res := 0
	for i := 0; i < n; i++ {
		res = _max(res, pos[i])
		res = _max(res, neg[i])
	}
	return res
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Use DP
// Time: O(n); Space: O(1)
func wiggleMaxLength2(nums []int) int {
	n := len(nums)
	posLen := 1
	negLen := 1

	for i := 1; i < n; i++ {
		if nums[i] > nums[i-1] {
			posLen = _max(posLen, negLen+1)
		} else if nums[i] < nums[i-1] {
			negLen = _max(negLen, posLen+1)
		}
	}

	return len(nums)
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Use Greedy
// Time: O(n); Space: O(1)
func wiggleMaxLength3(nums []int) int {
	n := len(nums)
	if n <= 1 {
		return 1
	}

	// Find first different
	i := 1
	for i = 1; i < n; i++ {
		diff := nums[i] - nums[i-1]
		if diff != 0 {
			break
		}
	}

	// All numbers are the same
	if i == n {
		return 1
	}

	res := 2
	prevDiff := nums[i] - nums[i-1]

	for i++; i < n; i++ {
		diff := nums[i] - nums[i-1]
		if diff*prevDiff < 0 {
			res += 1
			prevDiff = diff
		}
	}

	return res
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

func _max(a, b int) int {
	if a > b {
		return a
	}
	return b
}
