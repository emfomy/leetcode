// Source: https://leetcode.com/problems/merge-sorted-array
// Title: Merge Sorted Array
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given two integer arrays `nums1` and `nums2`, sorted in **non-decreasing order**, and two integers `m` and `n`, representing the number of elements in `nums1` and `nums2` respectively.
//
// **Merge** `nums1` and `nums2` into a single array sorted in **non-decreasing order**.
//
// The final sorted array should not be returned by the function, but instead be stored inside the array `nums1`. To accommodate this, `nums1` has a length of `m + n`, where the first `m` elements denote the elements that should be merged, and the last `n` elements are set to `0` and should be ignored. `nums2` has a length of `n`.
//
// **Example 1:**
//
// ```
// Input: nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
// Output: [1,2,2,3,5,6]
// Explanation: The arrays we are merging are [1,2,3] and [2,5,6].
// The result of the merge is [1,2,2,3,5,6] with the underlined elements coming from nums1.
// ```
//
// **Example 2:**
//
// ```
// Input: nums1 = [1], m = 1, nums2 = [], n = 0
// Output: [1]
// Explanation: The arrays we are merging are [1] and [].
// The result of the merge is [1].
// ```
//
// **Example 3:**
//
// ```
// Input: nums1 = [0], m = 0, nums2 = [1], n = 1
// Output: [1]
// Explanation: The arrays we are merging are [] and [1].
// The result of the merge is [1].
// Note that because m = 0, there are no elements in nums1. The 0 is only there to ensure the merge result can fit in nums1.
// ```
//
// **Constraints:**
//
// - `nums1.length == m + n`
// - `nums2.length == n`
// - `0 <= m, n <= 200`
// - `1 <= m + n <= 200`
// - `-10^9 <= nums1[i], nums2[j] <= 10^9`
//
// **Follow up: **Can you come up with an algorithm that runs in `O(m + n)` time?
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// Merge into another array
func merge(nums1 []int, m int, nums2 []int, n int) {
	nums3 := make([]int, m+n)

	i1, i2, i3 := 0, 0, 0
	for i1 < m && i2 < n {
		if nums1[i1] < nums2[i2] {
			nums3[i3] = nums1[i1]
			i1++
		} else {
			nums3[i3] = nums2[i2]
			i2++
		}
		i3++
	}

	if i1 < m {
		copy(nums3[i3:], nums1[i1:])
	}
	if i2 < n {
		copy(nums3[i3:], nums2[i2:])
	}
	copy(nums1, nums3)
}

// In-place merge
func merge2(nums1 []int, m int, nums2 []int, n int) {
	// Move nums1 to the end
	for i := m - 1; i >= 0; i-- {
		nums1[n+i] = nums1[i]
	}

	// Merge
	i1, i2, i3 := n, 0, 0
	for i1 < m+n && i2 < n {
		if nums1[i1] < nums2[i2] {
			nums1[i3] = nums1[i1]
			i1++
		} else {
			nums1[i3] = nums2[i2]
			i2++
		}
		i3++
	}

	if i1 < m+n {
		copy(nums1[i3:], nums1[i1:])
	}
	if i2 < n {
		copy(nums1[i3:], nums2[i2:])
	}
}

// In-place merge (from end)
func merge3(nums1 []int, m int, nums2 []int, n int) {
	// Merge
	i1, i2, i3 := m-1, n-1, m+n-1
	for i1 >= 0 && i2 >= 0 {
		if nums1[i1] > nums2[i2] {
			nums1[i3] = nums1[i1]
			i1--
		} else {
			nums1[i3] = nums2[i2]
			i2--
		}
		i3--
	}

	for i1 >= 0 {
		nums1[i3] = nums1[i1]
		i1--
		i3--
	}
	for i2 >= 0 {
		nums1[i3] = nums2[i2]
		i2--
		i3--
	}
}
