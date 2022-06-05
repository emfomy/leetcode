// Source: https://leetcode.com/problems/can-make-arithmetic-progression-from-sequence/
// Title: Can Make Arithmetic Progression From Sequence
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// A sequence of numbers is called an arithmetic progression if the difference between any two consecutive elements is the same.
//
// Given an array of numbers arr, return true if the array can be rearranged to form an arithmetic progression. Otherwise, return false.
//
// Example 1:
//
//   Input: arr = [3,5,1]
//   Output: true
//   Explanation: We can reorder the elements as [1,3,5] or [5,3,1] with differences 2 and -2 respectively, between each consecutive elements.
//
// Example 2:
//
//   Input: arr = [1,2,4]
//   Output: false
//   Explanation: There is no way to reorder the elements to obtain an arithmetic progression.
//
// Constraints:
//
//   2 <= arr.length <= 1000
//   -10^6 <= arr[i] <= 10^6
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"sort"
)

type void struct{}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Using sort; O(nlogn) time, O(1) space
func canMakeArithmeticProgression(arr []int) bool {
	sort.Ints(arr)

	step := arr[1] - arr[0]
	for i := 2; i < len(arr); i++ {
		if arr[i]-arr[i-1] != step {
			return false
		}
	}
	return true
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Using set; O(n) time, O(n) space
func canMakeArithmeticProgression2(arr []int) bool {
	n := len(arr)
	if n == 2 {
		return true
	}

	// Get min and max
	minV := arr[0]
	maxV := arr[0]
	for _, v := range arr {
		minV = _min(minV, v)
		maxV = _max(maxV, v)
	}

	if maxV == minV {
		return true
	}

	// Get step
	if (maxV-minV)%(n-1) != 0 {
		return false
	}
	step := (maxV - minV) / (n - 1)

	set := make(map[int]void, n)
	for _, v := range arr {
		if (v-minV)%step != 0 {
			return false
		}

		nStep := (v - minV) / step
		if _, ok := set[nStep]; ok {
			return false
		}
		set[nStep] = void{}
	}

	return true
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Using swap; O(n) time, O(1) space
func canMakeArithmeticProgression3(arr []int) bool {
	n := len(arr)
	if n == 2 {
		return true
	}

	// Get min and max
	minV := arr[0]
	maxV := arr[0]
	for _, v := range arr {
		minV = _min(minV, v)
		maxV = _max(maxV, v)
	}

	if maxV == minV {
		return true
	}

	// Get step
	if (maxV-minV)%(n-1) != 0 {
		return false
	}
	step := (maxV - minV) / (n - 1)

	// Swap value in step i to position i
	for i := 0; i < n; {
		if (arr[i]-minV)%step != 0 { // Not arithmetic progression
			return false
		}

		pos := (arr[i] - minV) / step

		if pos == i {
			i++
			continue
		}

		if arr[pos] == arr[i] { // Duplicate value
			return false
		}

		arr[pos], arr[i] = arr[i], arr[pos]
	}

	return true
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

func _max(a, b int) int {
	if a > b {
		return a
	}
	return b
}

func _min(a, b int) int {
	if a < b {
		return a
	}
	return b
}
