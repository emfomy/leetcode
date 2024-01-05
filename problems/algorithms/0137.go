// Source: https://leetcode.com/problems/single-number-ii/
// Title: Single Number II
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer array nums where every element appears three times except for one, which appears exactly once. Find the single element and return it.
//
// You must implement a solution with a linear runtime complexity and use only constant extra space.
//
// Example 1:
//
//   Input: nums = [2,2,3,2]
//   Output: 3
//
// Example 2:
//
//   Input: nums = [0,1,0,1,0,1,99]
//   Output: 99
//
// Constraints:
//
//   1 <= nums.length <= 3 * 10^4
//   -2^31 <= nums[i] <= 2^31-1
//   Each element in nums appears exactly three times except for one element which appears once.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import "fmt"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Count bits; O(n) time, O(1) space
func singleNumber(nums []int) int {
	res := 0

	for i := 0; i < 32; i++ { // loop for bits
		sum := 0
		for _, num := range nums {
			sum += num >> i & 1 // count i-th bits
		}
		res += (sum % 3) << i
	}

	return int(int32(res))
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Count bits; O(n) time, O(1) space
// once := XOR nums XOR twice
func singleNumber2(nums []int) int {
	once := 0  // bits that appeared once
	twice := 0 // bits that appeared twice

	for _, num := range nums {
		once ^= num & ^twice
		twice ^= num & ^once
	}

	return once
}

func main() {
	fmt.Println(singleNumber2([]int{2, 2, 3, 2}))
}
