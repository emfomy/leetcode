// Source: https://leetcode.com/problems/median-of-two-sorted-arrays/
// Title: Median of Two Sorted Arrays
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given two sorted arrays nums1 and nums2 of size m and n respectively, return the median of the two sorted arrays.
//
// The overall run time complexity should be O(log (m+n)).
//
// Example 1:
//
//   Input: nums1 = [1,3], nums2 = [2]
//   Output: 2.00000
//   Explanation: merged array = [1,2,3] and median is 2.
//
// Example 2:
//
//   Input: nums1 = [1,2], nums2 = [3,4]
//   Output: 2.50000
//   Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.
//
// Constraints:
//
//   nums1.length == m
//   nums2.length == n
//   0 <= m <= 1000
//   0 <= n <= 1000
//   1 <= m + n <= 2000
//   -10^6 <= nums1[i], nums2[i] <= 10^6
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func findMedianSortedArrays(nums1 []int, nums2 []int) float64 {

	len1 := len(nums1)
	len2 := len(nums2)
	totalLen := len1 + len2

	merge := func() chan int { // Merge sort
		ch := make(chan int)
		go func() {
			idx1 := 0
			idx2 := 0
			for idx1 < len1 && idx2 < len2 {
				val1 := nums1[idx1]
				val2 := nums2[idx2]
				if val1 < val2 {
					ch <- val1
					idx1++
				} else {
					ch <- val2
					idx2++
				}
			}
			for idx1 < len1 {
				ch <- nums1[idx1]
				idx1++
			}
			for idx2 < len2 {
				ch <- nums2[idx2]
				idx2++
			}
			close(ch)
		}()
		return ch
	}

	idx := 0
	medIdx := totalLen / 2
	currVal := 0
	prevVal := 0
	for currVal = range merge() {
		if idx == medIdx {
			break
		}
		prevVal = currVal
		idx++
	}

	if totalLen%2 == 1 {
		return float64(currVal)
	} else {
		return float64(currVal+prevVal) / 2
	}
}
