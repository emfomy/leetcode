// Source: https://leetcode.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit
// Title: Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array of integers nums and an integer limit, return the size of the longest non-empty subarray such that the absolute difference between any two elements of this subarray is less than or equal to limit.
//
// Example 1:
//
//   Input: nums = [8,2,4,7], limit = 4
//   Output: 2
//   Explanation:
//     All subarrays are:
//       - [8] with maximum absolute diff |8-8| = 0 <= 4.
//       - [8,2] with maximum absolute diff |8-2| = 6 > 4.
//       - [8,2,4] with maximum absolute diff |8-2| = 6 > 4.
//       - [8,2,4,7] with maximum absolute diff |8-2| = 6 > 4.
//       - [2] with maximum absolute diff |2-2| = 0 <= 4.
//       - [2,4] with maximum absolute diff |2-4| = 2 <= 4.
//       - [2,4,7] with maximum absolute diff |2-7| = 5 > 4.
//       - [4] with maximum absolute diff |4-4| = 0 <= 4.
//       - [4,7] with maximum absolute diff |4-7| = 3 <= 4.
//       - [7] with maximum absolute diff |7-7| = 0 <= 4.
//     Therefore, the size of the longest subarray is 2.
//
// Example 2:
//
//   Input: nums = [10,1,2,4,7,2], limit = 5
//   Output: 4
//   Explanation: The subarray [2,4,7,2] is the longest since the maximum absolute diff is |2-7| = 5 <= 5.
//
// Example 3:
//
//   Input: nums = [4,2,2,2,4,4,2,2], limit = 0
//   Output: 3
//
// Constraints:
//
//   1 <= nums.length <= 10^5
//   1 <= nums[i] <= 10^9
//   0 <= limit <= 10^9
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

type queue struct {
	data []int
	lIdx int
	rIdx int
}

func newQueue(size int) *queue {
	return &queue{
		data: make([]int, size),
		lIdx: 0,
		rIdx: -1,
	}
}

func (q queue) empty() bool {
	return q.lIdx > q.rIdx
}

func (q queue) peekLeft() int {
	return q.data[q.lIdx]
}

func (q queue) peekRight() int {
	return q.data[q.rIdx]
}

func (q *queue) popLeft() {
	q.lIdx++
}

func (q *queue) popRight() {
	q.rIdx--
}

// func (q *queue) pushLeft(val int) {
// 	q.lIdx--
// 	q.data[q.lIdx] = val
// }

func (q *queue) pushRight(val int) {
	q.rIdx++
	q.data[q.rIdx] = val
}

func longestSubarray(nums []int, limit int) int {
	n := len(nums)
	decQ := newQueue(n)
	incQ := newQueue(n)

	ans := 0
	lIdx := 0

	for rIdx, rVal := range nums {
		for !decQ.empty() && decQ.peekRight() < rVal {
			decQ.popRight()
		}
		decQ.pushRight(rVal)

		for !incQ.empty() && incQ.peekRight() > rVal {
			incQ.popRight()
		}
		incQ.pushRight(rVal)

		for decQ.peekLeft()-incQ.peekLeft() > limit {
			if decQ.peekLeft() == nums[lIdx] {
				decQ.popLeft()
			}
			if incQ.peekLeft() == nums[lIdx] {
				incQ.popLeft()
			}
			lIdx++
		}

		ans = max(ans, rIdx-lIdx+1)
	}

	return ans
}
