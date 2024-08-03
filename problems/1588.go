// Source: https://leetcode.com/problems/sum-of-all-odd-length-subarrays
// Title: Sum of All Odd Length Subarrays
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array of positive integers arr, return the sum of all possible odd-length subarrays of arr.
//
// A subarray is a contiguous subsequence of the array.
//
// Example 1:
//
//   Input: arr = [1,4,2,5,3]
//   Output: 58
//   Explanation:
//     The odd-length subarrays of arr and their sums are:
//       [1] = 1
//       [4] = 4
//       [2] = 2
//       [5] = 5
//       [3] = 3
//       [1,4,2] = 7
//       [4,2,5] = 11
//       [2,5,3] = 10
//       [1,4,2,5,3] = 15
//     If we add all these together we get 1 + 4 + 2 + 5 + 3 + 7 + 11 + 10 + 15 = 58
//
// Example 2:
//
//   Input: arr = [1,2]
//   Output: 3
//   Explanation: There are only 2 subarrays of odd length, [1] and [2]. Their sum is 3.
//
// Example 3:
//
//   Input: arr = [10,11,12]
//   Output: 66
//
// Constraints:
//
//   1 <= arr.length <= 100
//   1 <= arr[i] <= 1000
//
// Follow up: Could you solve this problem in O(n) time complexity?
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// First, we ignore the odd length constarint.
// Given any number arr[i], a subarray [x, y] contains arr[i] iff. x <= i <= y.
// Therefore, there are i+1 choices (0~i) for x, and n-i choices (i~n-1) for y,
// which gives us total S = (i+1) * (n-i) subarries that contain arr[i].
//
// Note that the parity of lengh is decided by the parity of x and y.
// Therefore, if the number of choices for x (or y) is even, then exactly half of the subarries are odd.
// If both (i+1) and (n-i) are odd, then there are exactly one more odd subarries then the even ones.
// Hence, there are S/2 (round up) odd subarries.
func sumOddLengthSubarrays(arr []int) int {
	n := len(arr)
	res := 0
	for i, v := range arr {
		s := (i + 1) * (n - i)
		res += (s + 1) / 2 * v
	}
	return res
}
