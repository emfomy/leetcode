// Source: https://leetcode.com/problems/the-number-of-beautiful-subsets
// Title: The Number of Beautiful Subsets
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an array nums of positive integers and a positive integer k.
// A subset of nums is beautiful if it does not contain two integers with an absolute difference equal to k.
// Return the number of non-empty beautiful subsets of the array nums.
// A subset of nums is an array that can be obtained by deleting some (possibly none) elements from nums. Two subsets are different if and only if the chosen indices to delete are different.
//
// Example 1:
//
//   Input: nums = [2,4,6], k = 2
//   Output: 4
//   Explanation: The beautiful subsets of the array nums are: [2], [4], [6], [2, 6].
//   It can be proved that there are only 4 beautiful subsets in the array [2,4,6].
//
// Example 2:
//
//   Input: nums = [1], k = 1
//   Output: 1
//   Explanation: The beautiful subset of the array nums is [1].
//   It can be proved that there is only 1 beautiful subset in the array [1].
//
// Constraints:
//
//   1 <= nums.length <= 20
//   1 <= nums[i], k <= 1000
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"sort"
)

// First group by modulo of k.
// Next compute the number of beautiful subsets in a group.
// Note that above number inclues empty subset.
// Finally, we multiply above number, and substract by 1 (the empty subset)
func beautifulSubsets(nums []int, k int) int {
	sort.Ints(nums)

	buckets := make([][]int, k)
	for i := 0; i < k; i++ {
		buckets[i] = make([]int, 0)
	}
	for _, num := range nums {
		buckets[num%k] = append(buckets[num%k], num)
	}

	count := 1
	for _, bucket := range buckets {
		count *= _bucketSubsets(bucket, k)
	}

	return count - 1
}

func _bucketSubsets(bucket []int, k int) int {
	n := len(bucket)
	if n == 0 {
		return 1
	}

	counts := make([]int, 2*n)
	{
		prevNum := bucket[0]
		i := 0
		for _, num := range bucket {
			switch num - prevNum {
			case 0:
			case k:
				i++
			default:
				i += 2
			}
			counts[i]++
			prevNum = num
		}
	}

	// DP
	pick, noPick := 0, 1
	for _, count := range counts {
		pick, noPick = count*noPick, pick+noPick
	}
	return pick + noPick
}
