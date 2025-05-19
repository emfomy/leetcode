// Source: https://leetcode.com/problems/bitwise-xor-of-all-pairings
// Title: Bitwise XOR of All Pairings
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given two **0-indexed** arrays, `nums1` and `nums2`, consisting of non-negative integers. There exists another array, `nums3`, which contains the bitwise XOR of **all pairings** of integers between `nums1` and `nums2` (every integer in `nums1` is paired with every integer in `nums2` **exactly once** ).
//
// Return the **bitwise XOR** of all integers in `nums3`.
//
// **Example 1:**
//
// ```
// Input: nums1 = [2,1,3], nums2 = [10,2,5,0]
// Output: 13
// Explanation:
// A possible nums3 array is [8,0,7,2,11,3,4,1,9,1,6,3].
// The bitwise XOR of all these numbers is 13, so we return 13.
// ```
//
// **Example 2:**
//
// ```
// Input: nums1 = [1,2], nums2 = [3,4]
// Output: 0
// Explanation:
// All possible pairs of bitwise XORs are nums1[0] ^ nums2[0], nums1[0] ^ nums2[1], nums1[1] ^ nums2[0],
// and nums1[1] ^ nums2[1].
// Thus, one possible nums3 array is [2,5,1,6].
// 2 ^ 5 ^ 1 ^ 6 = 0, so we return 0.
// ```
//
// **Constraints:**
//
// - `1 <= nums1.length, nums2.length <= 10^5`
// - `0 <= nums1[i], nums2[j] <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// Define a^n := a xor a ... a (n times)
// Note that a^n = 0 if n is even, a^n = a if n is odd
//
// The result is XOR_i,j (a_i xor b_j)
// Since xors are commutative,
// XOR_i,j (a_i xor b_j)
// = XOR_i (a_i)^n XOR_j (a_j)^m
func xorAllNums(nums1 []int, nums2 []int) int {
	m := len(nums1)
	n := len(nums2)

	res := 0
	if n%2 == 1 {
		for _, num := range nums1 {
			res ^= num
		}
	}
	if m%2 == 1 {
		for _, num := range nums2 {
			res ^= num
		}
	}

	return res
}
