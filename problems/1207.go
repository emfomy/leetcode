// Source: https://leetcode.com/problems/unique-number-of-occurrences
// Title: Unique Number of Occurrences
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array of integers arr, return true if the number of occurrences of each value in the array is unique or false otherwise.
//
// Example 1:
//
//   Input: arr = [1,2,2,1,1,3]
//   Output: true
//   Explanation: The value 1 has 3 occurrences, 2 has 2 and 3 has 1. No two values have the same number of occurrences.
//
// Example 2:
//
//   Input: arr = [1,2]
//   Output: false
//
// Example 3:
//
//   Input: arr = [-3,0,1,-3,1,1,1,-3,10,0]
//   Output: true
//
// Constraints:
//   * 1 <= arr.length <= 1000
//   * -1000 <= arr[i] <= 1000
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"sort"
)

func uniqueOccurrences(arr []int) bool {
	counter := make(map[int]int)
	for _, item := range arr {
		counter[item]++
	}

	n := len(counter) // number of unique integer
	counts := make([]int, 0, n)
	for _, cnt := range counter {
		counts = append(counts, cnt)
	}

	// Find duplicate counts
	sort.Ints(counts)
	for i := 0; i < n-1; i++ {
		if counts[i] == counts[i+1] {
			return false
		}
	}
	return true
}
