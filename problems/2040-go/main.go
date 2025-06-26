// Source: https://leetcode.com/problems/kth-smallest-product-of-two-sorted-arrays
// Title: Kth Smallest Product of Two Sorted Arrays
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given two **sorted 0-indexed** integer arrays `nums1` and `nums2` as well as an integer `k`, return the `k^th` (**1-based**) smallest product of `nums1[i] * nums2[j]` where `0 <= i < nums1.length` and `0 <= j < nums2.length`.
//
// **Example 1:**
//
// ```
// Input: nums1 = [2,5], nums2 = [3,4], k = 2
// Output: 8
// Explanation: The 2 smallest products are:
// - nums1[0] * nums2[0] = 2 * 3 = 6
// - nums1[0] * nums2[1] = 2 * 4 = 8
// The 2^nd smallest product is 8.
// ```
//
// **Example 2:**
//
// ```
// Input: nums1 = [-4,-2,0,3], nums2 = [2,4], k = 6
// Output: 0
// Explanation: The 6 smallest products are:
// - nums1[0] * nums2[1] = (-4) * 4 = -16
// - nums1[0] * nums2[0] = (-4) * 2 = -8
// - nums1[1] * nums2[1] = (-2) * 4 = -8
// - nums1[1] * nums2[0] = (-2) * 2 = -4
// - nums1[2] * nums2[0] = 0 * 2 = 0
// - nums1[2] * nums2[1] = 0 * 4 = 0
// The 6^th smallest product is 0.
// ```
//
// **Example 3:**
//
// ```
// Input: nums1 = [-2,-1,0,1,2], nums2 = [-3,-1,2,4,5], k = 3
// Output: -6
// Explanation: The 3 smallest products are:
// - nums1[0] * nums2[4] = (-2) * 5 = -10
// - nums1[0] * nums2[3] = (-2) * 4 = -8
// - nums1[4] * nums2[0] = 2 * (-3) = -6
// The 3^rd smallest product is -6.
// ```
//
// **Constraints:**
//
// - `1 <= nums1.length, nums2.length <= 5 * 10^4`
// - `-10^5 <= nums1[i], nums2[j] <= 10^5`
// - `1 <= k <= nums1.length * nums2.length`
// - `nums1` and `nums2` are sorted.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"sort"
)

// Binary Search + Binary Search
//
// Use binary search to find product.
// For each product p, count all pairs that has product smaller than p.
// To count pairs, loop through nums1;
// For each number x1 in in nums1, use binary search on nums2 to count products.
//
// Time complexity: O[n1 log(n2) log(prod range)]
func kthSmallestProduct(nums1 []int, nums2 []int, k int64) int64 {
	n1, n2 := len(nums1), len(nums2)
	if n1 > n2 { // Ensure n1 < n2
		n1, n2 = n2, n1
		nums1, nums2 = nums2, nums1
	}
	_ = n1

	// Binary search
	bisect := func(lo, hi int, check func(int) bool) int {
		// check(lo-1)=false, check(lo=hi)=true
		for lo < hi { // find in range [lo, hi)
			mid := lo + (hi-lo)/2
			if check(mid) {
				hi = mid // goto range [lo, mid)
			} else {
				lo = mid + 1 // goto range [mid, hi)
			}
		}
		return lo
	}

	checkProd := func(prod int) bool {
		count := 0
		for _, x1 := range nums1 {
			if x1 >= 0 {
				count += bisect(0, n2, func(i2 int) bool {
					return x1*nums2[i2] > prod
				})
			} else {
				count += n2 - bisect(0, n2, func(i2 int) bool {
					return !(x1*nums2[i2] > prod)
				})
			}
		}
		return count >= int(k)
	}

	return int64(bisect(-1e10, 1e10, checkProd))
}

// Binary Search
//
// Use binary search to find product.
// For each product p, we loop though all 4 positive/negative cases.
// Use (pos, pos) as example, since the curve is monotonic decreasing,
// we can start from (0, n2) to (n1, 0) and find the zig-zag curve.
//
// Time complexity: O[(n1+n2) log(prod range)]
func kthSmallestProduct2(nums1 []int, nums2 []int, k int64) int64 {
	n1, n2 := len(nums1), len(nums2)
	pos1 := sort.SearchInts(nums1, 0) // start index of positive numbers
	pos2 := sort.SearchInts(nums2, 0) // start index of positive numbers

	// Binary search
	bisect := func(lo, hi int, check func(int) bool) int {
		// check(lo-1)=false, check(lo=hi)=true
		for lo < hi { // find in range [lo, hi)
			mid := lo + (hi-lo)/2
			if check(mid) {
				hi = mid // goto range [lo, mid)
			} else {
				lo = mid + 1 // goto range [mid, hi)
			}
		}
		return lo
	}

	checkProd := func(prod int) bool {
		count := 0

		{ // neg, pos
			i1, i2 := 0, pos2
			for i1 < pos1 && i2 < n2 {
				if nums1[i1]*nums2[i2] > prod {
					i2++
				} else {
					count += n2 - i2
					i1++
				}
			}
		}
		{ // pos, neg
			i1, i2 := pos1, 0
			for i1 < n1 && i2 < pos2 {
				if nums1[i1]*nums2[i2] > prod {
					i1++
				} else {
					count += n1 - i1
					i2++
				}
			}
		}
		{ // neg, neg
			i1, i2 := 0, pos2-1
			for i1 < pos1 && i2 >= 0 {
				if nums1[i1]*nums2[i2] > prod {
					i1++
				} else {
					count += pos1 - i1
					i2--
				}
			}
		}
		{ // pos, pos
			i1, i2 := pos1, n2-1
			for i1 < n1 && i2 >= pos2 {
				if nums1[i1]*nums2[i2] > prod {
					i2--
				} else {
					count += i2 - pos2 + 1
					i1++
				}
			}
		}

		return count >= int(k)
	}

	return int64(bisect(-1e10, 1e10, checkProd))
}
