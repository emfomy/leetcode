// Source: https://leetcode.com/problems/delete-and-earn/
// Title: Delete and Earn
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array nums. You want to maximize the number of points you get by performing the following operation any number of times:
//
// Pick any nums[i] and delete it to earn nums[i] points. Afterwards, you must delete every element equal to nums[i] - 1 and every element equal to nums[i] + 1.
// Return the maximum number of points you can earn by applying the above operation some number of times.
//
// Example 1:
//
//   Input: nums = [3,4,2]
//   Output: 6
//   Explanation:
//      You can perform the following operations:
//     - Delete 4 to earn 4 points. Consequently, 3 is also deleted. nums = [2].
//     - Delete 2 to earn 2 points. nums = [].
//     You earn a total of 6 points.
//
// Example 2:
//
//   Input: nums = [2,2,3,3,3,4]
//   Output: 9
//   Explanation:
//     You can perform the following operations:
//     - Delete a 3 to earn 3 points. All 2's and 4's are also deleted. nums = [3,3].
//     - Delete a 3 again to earn 3 points. nums = [3].
//     - Delete a 3 once more to earn 3 points. nums = [].
//     You earn a total of 9 points.
//
// Constraints:
//
//   1 <= nums.length <= 2 * 10^4
//   1 <= nums[i] <= 10^4
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// Be pick from the smallest to the largest
// Let P(i) be the points if you pick number i
// Let N(i) be the points if you don't pick number i
// P(i) = N(i-1) + points of number i
// N(i) = max(P(i-1), N(i-1))
func deleteAndEarn(nums []int) int {
	amounts := make([]int, 20_000) // num -> amount of num

	// Sum numbers
	minNum := 10_000
	maxNum := 1
	for _, num := range nums {
		amounts[num] += num
		maxNum = _max(maxNum, num)
		minNum = _min(minNum, num)
	}

	// DP
	p := 0
	n := 0
	for num := minNum; num <= maxNum; num++ {
		p, n = amounts[num]+n, _max(p, n)
	}
	return _max(p, n)
}

func _max(a, b int) int {
	if a > b {
		return a
	}
	return b
}

func _min(a, b int) int {
	if a < b {
		return a
	}
	return b
}
