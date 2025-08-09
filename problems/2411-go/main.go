// Source: https://leetcode.com/problems/smallest-subarrays-with-maximum-bitwise-or
// Title: Smallest Subarrays With Maximum Bitwise OR
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a **0-indexed** array `nums` of length `n`, consisting of non-negative integers. For each index `i` from `0` to `n - 1`, you must determine the size of the **minimum sized** non-empty subarray of `nums` starting at `i` (**inclusive**) that has the **maximum** possible **bitwise OR**.
//
// - In other words, let `B_ij` be the bitwise OR of the subarray `nums[i...j]`. You need to find the smallest subarray starting at `i`, such that bitwise OR of this subarray is equal to `max(B_ik)` where `i <= k <= n - 1`.
//
// The bitwise OR of an array is the bitwise OR of all the numbers in it.
//
// Return an integer array `answer` of size `n` where `answer[i]` is the length of the **minimum** sized subarray starting at `i` with **maximum** bitwise OR.
//
// A **subarray** is a contiguous non-empty sequence of elements within an array.
//
// **Example 1:**
//
// ```
// Input: nums = [1,0,2,1,3]
// Output: [3,3,2,2,1]
// Explanation:
// The maximum possible bitwise OR starting at any index is 3.
// - Starting at index 0, the shortest subarray that yields it is [1,0,2].
// - Starting at index 1, the shortest subarray that yields the maximum bitwise OR is [0,2,1].
// - Starting at index 2, the shortest subarray that yields the maximum bitwise OR is [2,1].
// - Starting at index 3, the shortest subarray that yields the maximum bitwise OR is [1,3].
// - Starting at index 4, the shortest subarray that yields the maximum bitwise OR is [3].
// Therefore, we return [3,3,2,2,1].
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [1,2]
// Output: [2,1]
// **Explanation:
// **Starting at index 0, the shortest subarray that yields the maximum bitwise OR is of length 2.
// Starting at index 1, the shortest subarray that yields the maximum bitwise OR is of length 1.
// Therefore, we return [2,1].
// ```
//
// **Constraints:**
//
// - `n == nums.length`
// - `1 <= n <= 10^5`
// - `0 <= nums[i] <= 10^9`
//
// **Note:** This question is the same as https://leetcode.com/problems/assign-cookies/
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import "sort"

// Prefix Sum + TLE
func smallestSubarrays(nums []int) []int {
	const B = 30

	n := len(nums)

	type bitType = [B]int
	newBit := func(num int) (bit bitType) {
		for i := range B {
			bit[i] = (num >> i) & 1
		}
		return
	}
	bitAdd := func(a, b bitType) bitType {
		for i := range B {
			a[i] += b[i]
		}
		return a
	}
	bitMinus := func(a, b bitType) bitType {
		for i := range B {
			a[i] -= b[i]
		}
		return a
	}
	bitMask := func(a bitType) bitType {
		for i := range B {
			a[i] = min(a[i], 1)
		}
		return a
	}
	bitGte := func(a, b bitType) bool {
		for i := range B {
			if a[i] < b[i] {
				return false
			}
		}
		return true
	}

	// Convert to bits
	bits := make([]bitType, n)
	for i, num := range nums {
		bits[i] = newBit(num)
	}

	// Pre OR
	preSum := make([]bitType, n+1) // OR[0...i)
	for i, bit := range bits {
		preSum[i+1] = bitAdd(preSum[i], bit)
	}

	ans := make([]int, n)
	for i := range n {
		mask := bitMask(bitMinus(preSum[n], preSum[i]))
		for j := i + 1; j <= n; j++ {
			if bitGte(bitMinus(preSum[j], preSum[i]), mask) {
				ans[i] = j - i
				break
			}
		}
	}

	return ans
}

// Prefix Sum + Binary Search
func smallestSubarrays2(nums []int) []int {
	const B = 30

	n := len(nums)

	type bitType = [B]int
	newBit := func(num int) (bit bitType) {
		for i := range B {
			bit[i] = (num >> i) & 1
		}
		return
	}
	bitAdd := func(a, b bitType) bitType {
		for i := range B {
			a[i] += b[i]
		}
		return a
	}
	bitMinus := func(a, b bitType) bitType {
		for i := range B {
			a[i] -= b[i]
		}
		return a
	}
	bitMask := func(a bitType) bitType {
		for i := range B {
			a[i] = min(a[i], 1)
		}
		return a
	}
	bitGte := func(a, b bitType) bool {
		for i := range B {
			if a[i] < b[i] {
				return false
			}
		}
		return true
	}

	// Convert to bits
	bits := make([]bitType, n)
	for i, num := range nums {
		bits[i] = newBit(num)
	}

	// Pre OR
	preSum := make([]bitType, n+1) // OR[0...i)
	for i, bit := range bits {
		preSum[i+1] = bitAdd(preSum[i], bit)
	}

	binarySearch := func(lo, hi int, check func(i int) bool) int {
		return lo + sort.Search(hi-lo, func(i int) bool {
			return check(lo + i)
		})
	}

	ans := make([]int, n)
	for i := range n {
		mask := bitMask(bitMinus(preSum[n], preSum[i]))
		j := binarySearch(i+1, n+1, func(k int) bool {
			return bitGte(bitMinus(preSum[k], preSum[i]), mask)
		})
		ans[i] = j - i
	}

	return ans
}

// Prefix Sum + Binary Search
//
// Loop from right to left.
// We track the left most 1 of each bit.
func smallestSubarrays3(nums []int) []int {
	const B = 30

	n := len(nums)

	pos := make([]int, B) // left most 1
	for i := range B {
		pos[i] = -1
	}

	ans := make([]int, n)

	for i := n - 1; i >= 0; i-- {
		j := i // end point
		for bit := range B {
			if (nums[i]>>bit)&1 == 1 { // is 1
				pos[bit] = i
			} else { // is not 1, find nearest 1
				j = max(j, pos[bit])
			}
		}
		ans[i] = j - i + 1
	}

	return ans
}
