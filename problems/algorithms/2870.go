// Source: https://leetcode.com/problems/minimum-number-of-operations-to-make-array-empty
// Title: Minimum Number of Operations to Make Array Empty
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a 0-indexed array nums consisting of positive integers.
// There are two types of operations that you can apply on the array any number of times:
// * Choose two elements with equal values and delete them from the array.
// * Choose three elements with equal values and delete them from the array.
// Return the minimum number of operations required to make the array empty, or -1 if it is not possible.
//
// Example 1:
//
//   Input: nums = [2,3,3,2,2,4,2,3,4]
//   Output: 4
//   Explanation:
//     We can apply the following operations to make the array empty:
//     * Apply the first operation on the elements at indices 0 and 3. The resulting array is nums = [3,3,2,4,2,3,4].
//     * Apply the first operation on the elements at indices 2 and 4. The resulting array is nums = [3,3,4,3,4].
//     * Apply the second operation on the elements at indices 0, 1, and 3. The resulting array is nums = [4,4].
//     * Apply the first operation on the elements at indices 0 and 1. The resulting array is nums = [].
//     It can be shown that we cannot make the array empty in less than 4 operations.
//
// Example 2:
//
//   Input: nums = [2,1,2,2,3,3]
//   Output: -1
//   Explanation: It is impossible to empty the array.
//
// Constraints:
//
//   * 2 <= nums.length <= 105
//   * 1 <= nums[i] <= 106
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func minOperations(nums []int) int {
	res := 0

	// Count numbers
	numCount := make(map[int]int, len(nums))
	for _, num := range nums {
		numCount[num]++
	}

	// Loop for numbers
	for _, count := range numCount {
		if count == 1 {
			return -1
		}

		switch count % 3 {
		case 0: // (count/3) * 3
			res += count / 3
		case 1: // (count/3-1) * 3 + 2 * 2
			res += count/3 + 1
		case 2: // (count/3) * 3 + 2
			res += count/3 + 1
		}
	}

	return res
}
