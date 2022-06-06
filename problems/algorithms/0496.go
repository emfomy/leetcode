// Source: https://leetcode.com/problems/next-greater-element-i/
// Title: Next Greater Element I
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The next greater element of some element x in an array is the first greater element that is to the right of x in the same array.
//
// You are given two distinct 0-indexed integer arrays nums1 and nums2, where nums1 is a subset of nums2.
//
// For each 0 <= i < nums1.length, find the index j such that nums1[i] == nums2[j] and determine the next greater element of nums2[j] in nums2. If there is no next greater element, then the answer for this query is -1.
//
// Return an array ans of length nums1.length such that ans[i] is the next greater element as described above.
//
// Example 1:
//
//   Input: nums1 = [4,1,2], nums2 = [1,3,4,2]
//   Output: [-1,3,-1]
//   Explanation: The next greater element for each value of nums1 is as follows:
//     4 is underlined in nums2 = [1,3,4_,2]. There is no next greater element, so the answer is -1.
//     1 is underlined in nums2 = [1_,3,4,2]. The next greater element is 3.
//     2 is underlined in nums2 = [1,3,4,2_]. There is no next greater element, so the answer is -1.
//
// Example 2:
//
//   Input: nums1 = [2,4], nums2 = [1,2,3,4]
//   Output: [3,-1]
//   Explanation: The next greater element for each value of nums1 is as follows:
//     2 is underlined in nums2 = [1,2_,3,4]. The next greater element is 3.
//     4 is underlined in nums2 = [1,2,3,4_]. There is no next greater element, so the answer is -1.
//
// Constraints:
//
//   1 <= nums1.length <= nums2.length <= 1000
//   0 <= nums1[i], nums2[i] <= 10^4
//   All integers in nums1 and nums2 are unique.
//   All the integers of nums1 also appear in nums2.
//
// Follow up: Could you find an O(nums1.length + nums2.length) solution?
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func nextGreaterElement(nums1 []int, nums2 []int) []int {
	l2 := len(nums2)

	idx2 := make(map[int]int, l2) // nums in nums2 to its idx
	next2 := make([]int, l2)      // store next greater values of nums2
	for i, v := range nums2 {
		idx2[v] = i
		next2[i] = -1
	}

	stack := make([]int, l2)
	stackSizeM1 := -1

	// Fill next2
	for currIdx, currVal := range nums2 {
		for ; stackSizeM1 >= 0; stackSizeM1-- { // pop if the value is smaller then current value
			numIdx := stack[stackSizeM1]
			if nums2[numIdx] >= currVal {
				break
			}
			next2[numIdx] = currVal
		}

		// Push
		stackSizeM1++
		stack[stackSizeM1] = currIdx
	}

	// Fill next1
	next1 := make([]int, len(nums1)) // store next greater values of nums1
	for i, v := range nums1 {
		next1[i] = next2[idx2[v]]
	}

	return next1
}
