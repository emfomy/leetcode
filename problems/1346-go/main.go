// Source: https://leetcode.com/problems/check-if-n-and-its-double-exist
// Title: Check If N and Its Double Exist
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array `arr` of integers, check if there exist two indices `i` and `j` such that :
//
// - `i != j`
// - `0 <= i, j < arr.length`
// - `arr[i] == 2 * arr[j]`
//
// **Example 1:**
//
// ```
// Input: arr = [10,2,5,3]
// Output: true
// Explanation: For i = 0 and j = 2, arr[i] == 10 == 2 * 5 == 2 * arr[j]
// ```
//
// **Example 2:**
//
// ```
// Input: arr = [3,1,7,11]
// Output: false
// Explanation: There is no i and j that satisfy the conditions.
// ```
//
// **Constraints:**
//
// - `2 <= arr.length <= 500`
// - `-10^3 <= arr[i] <= 10^3`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func checkIfExist(arr []int) bool {
	for i, num1 := range arr {
		for j, num2 := range arr {
			if i != j && num1 == 2*num2 {
				return true
			}
		}
	}

	return false
}

func checkIfExist2(arr []int) bool {
	n := len(arr)
	counter := make(map[int]int, n)

	for _, num := range arr {
		counter[num]++
	}

	for _, num := range arr {
		if num == 0 {
			if counter[0] > 1 {
				return true
			}
		} else {
			if counter[2*num] > 0 {
				return true
			}
		}
	}
	return false
}
