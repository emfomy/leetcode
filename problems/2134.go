// Source: https://leetcode.com/problems/minimum-swaps-to-group-all-1s-together-ii
// Title: Minimum Swaps to Group All 1's Together II
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// A swap is defined as taking two distinct positions in an array and swapping the values in them.
//
// A circular array is defined as an array where we consider the first element and the last element to be adjacent.
//
// Given a binary circular array nums, return the minimum number of swaps required to group all 1's present in the array together at any location.
//
// Example 1:
//
//   Input: nums = [0,1,0,1,1,0,0]
//   Output: 1
//   Explanation:
//     Here are a few of the ways to group all the 1's together:
//       [0,0,1,1,1,0,0] using 1 swap.
//       [0,1,1,1,0,0,0] using 1 swap.
//       [1,1,0,0,0,0,1] using 2 swaps (using the circular property of the array).
//     There is no way to group all 1's together with 0 swaps.
//     Thus, the minimum number of swaps required is 1.
//
// Example 2:
//
//   Input: nums = [0,1,1,1,0,0,1,1,0]
//   Output: 2
//   Explanation:
//     Here are a few of the ways to group all the 1's together:
//       [1,1,1,0,0,0,0,1,1] using 2 swaps (using the circular property of the array).
//       [1,1,1,1,1,0,0,0,0] using 2 swaps.
//     There is no way to group all 1's together with 0 or 1 swaps.
//     Thus, the minimum number of swaps required is 2.
//
//   Example 3:
//
//   Input: nums = [1,1,0,0,1]
//   Output: 0
//   Explanation:
//     All the 1's are already grouped together due to the circular property of the array.
//     Thus, the minimum number of swaps required is 0.
//
// Constraints:
//
//   1 <= nums.length <= 10^5
//   nums[i] is either 0 or 1.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// Let's call the adjacent 1s as "chunk".
// The number of swaps is equal to the the number zeros in the chunk
// Therefore, we only need loop for all possible chunks and find the minimal value.
func minSwaps(nums []int) int {
	n := len(nums)

	// Count ones (c)
	ones := 0
	for _, num := range nums {
		ones += num
	}

	// Count zeros in chunk [0, c)
	chunk_zeros := 0
	for _, num := range nums[:ones] {
		chunk_zeros += (1 - num)
	}

	ans := chunk_zeros

	for i := 0; i < n-1; i++ {
		j := (i + ones) % n
		chunk_zeros -= (1 - nums[i]) // Remove number at i
		chunk_zeros += (1 - nums[j]) // Add number at j
		ans = min(ans, chunk_zeros)
	}

	return ans
}
