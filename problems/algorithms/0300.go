// Source: https://leetcode.com/problems/longest-increasing-subsequence/
// Title: Longest Increasing Subsequence
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer array nums, return the length of the longest strictly increasing subsequence.
//
// A subsequence is a sequence that can be derived from an array by deleting some or no elements without changing the order of the remaining elements. For example, [3,6,2,7] is a subsequence of the array [0,3,1,6,2,2,7].
//
// Example 1:
//
// Input: nums = [10,9,2,5,3,7,101,18]
// Output: 4
// Explanation: The longest increasing subsequence is [2,3,7,101], therefore the length is 4.
//
// Example 2:
//
// Input: nums = [0,1,0,3,2,3]
// Output: 4
// Example 3:
//
// Input: nums = [7,7,7,7,7,7,7]
// Output: 1
//
// Constraints:
//
//   1 <= nums.length <= 2500
//   -10^4 <= nums[i] <= 10^4
//
// Follow up: Can you come up with an algorithm that runs in O(n log(n)) time complexity?
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Use DP
// Time: O(n^2); Space: O(n)
func lengthOfLIS(nums []int) int {
	n := len(nums)

	dp := make([]int, n) // length of longest increasing subsequence ends here
	for i := 0; i < n; i++ {
		dp[i] = 1
	}

	for i := 0; i < n; i++ {
		for j := 0; j < i; j++ {
			if nums[i] > nums[j] && dp[i] <= dp[j] {
				dp[i] = dp[j] + 1
			}
		}
	}

	res := 0
	for _, v := range dp {
		res = _max(res, v)
	}
	return res
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Use DP
// Time: O(n^2); Space: O(n)
func lengthOfLIS2(nums []int) int {
	n := len(nums)

	// Smallest tail of all increasing subsequences with length i+1
	// Note that it is always an increasing array
	tails := make([]int, 0, n)

	for _, num := range nums {
		found := false
		for i, tail := range tails {
			if num <= tail {
				tails[i] = num
				found = true
				break
			}
		}
		if !found {
			tails = append(tails, num)
		}
	}

	return len(tails)
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Use DP + binary search
// Time: O(nlogn); Space: O(n)
func lengthOfLIS3(nums []int) int {
	n := len(nums)

	// Smallest tail of all increasing subsequences with length i+1
	// Note that it is always an increasing array
	tails := make([]int, n)
	size := 0

	for _, num := range nums {
		idx := _binarySearch(tails, size, num)
		tails[idx] = num
		if idx == size {
			size += 1
		}
	}

	return size
}

// Returns the index such that arr[idx-1] < target <= arr[idx]
func _binarySearch(arr []int, size, target int) int {
	left := 0
	right := size
	for left != right {
		mid := (left + right) / 2
		if arr[mid] < target {
			left = mid + 1
		} else {
			right = mid
		}
	}
	return left
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

func _max(a, b int) int {
	if a > b {
		return a
	}
	return b
}
