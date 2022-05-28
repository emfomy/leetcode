// Source: https://leetcode.com/problems/missing-number/
// Title: Missing Number
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array nums containing n distinct numbers in the range [0, n], return the only number in the range that is missing from the array.
//
// Example 1:
//
//   Input: nums = [3,0,1]
//   Output: 2
//   Explanation: n = 3 since there are 3 numbers, so all numbers are in the range [0,3]. 2 is the missing number in the range since it does not appear in nums.
//
// Example 2:
//
//   Input: nums = [0,1]
//   Output: 2
//   Explanation: n = 2 since there are 2 numbers, so all numbers are in the range [0,2]. 2 is the missing number in the range since it does not appear in nums.
//
// Example 3:
//
//   Input: nums = [9,6,4,2,3,5,7,0,1]
//   Output: 8
//   Explanation: n = 9 since there are 9 numbers, so all numbers are in the range [0,9]. 8 is the missing number in the range since it does not appear in nums.
//
// Constraints:
//
//   n == nums.length
//   1 <= n <= 104
//   0 <= nums[i] <= n
//   All the numbers of nums are unique.
//
// Follow up: Could you implement a solution using only O(1) extra space complexity and O(n) runtime complexity?
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// Sum 0~n and substract by the sum of the array. Only the missing will not be canceled.
func missingNumber(nums []int) int {
	res := 0
	for i, num := range nums {
		res += i
		res -= num
	}
	return res + len(nums)
}

// The sum of 0~n is n(n+1)/2.
// Sum 0~n and substract by the sum of the array. Only the missing will not be canceled.
func missingNumber2(nums []int) int {
	n := len(nums)
	res := n * (n + 1) / 2
	for _, num := range nums {
		res -= num
	}
	return res
}

// Use bit manipulation.
// Xor sum 0~n and the array. Only the missing will not be canceled.
func missingNumber3(nums []int) int {
	res := 0
	for i, num := range nums {
		res ^= (i + 1)
		res ^= num
	}
	return res
}

// Use bit manipulation.
// Xor sum 0~n and the array. Only the missing will not be canceled.
// There is a pattern here in sum 0~n.
func missingNumber4(nums []int) int {
	n := len(nums)
	var res int
	switch n % 4 {
	case 0:
		res = n
	case 1:
		res = 1
	case 2:
		res = n + 1
	case 3:
		res = 0
	}

	// Xor on array
	for _, num := range nums {
		res ^= num
	}
	return res
}
