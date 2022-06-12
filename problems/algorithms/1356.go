// Source: https://leetcode.com/problems/sort-integers-by-the-number-of-1-bits/
// Title: Sort Integers by The Number of 1 Bits
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array arr. Sort the integers in the array in ascending order by the number of 1's in their binary representation and in case of two or more integers have the same number of 1's you have to sort them in ascending order.
//
// Return the array after sorting it.
//
// Example 1:
//
//   Input: arr = [0,1,2,3,4,5,6,7,8]
//   Output: [0,1,2,4,8,3,5,6,7]
//   Explantion: [0] is the only integer with 0 bits.
//   [1,2,4,8] all have 1 bit.
//   [3,5,6] have 2 bits.
//   [7] has 3 bits.
//   The sorted array by bits is [0,1,2,4,8,3,5,6,7]
//
// Example 2:
//
//   Input: arr = [1024,512,256,128,64,32,16,8,4,2,1]
//   Output: [1,2,4,8,16,32,64,128,256,512,1024]
//   Explantion: All integers have 1 bit in the binary representation, you should just sort them in ascending order.
//
// Constraints:
//
//   1 <= arr.length <= 500
//   0 <= arr[i] <= 10^4
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"sort"
)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

func sortByBits(arr []int) []int {
	bitCounts := make(map[int]int, len(arr)) // map number to bit count

	for _, num := range arr {
		bitCounts[num] = _countBit(num)
	}

	sort.Slice(arr, func(i, j int) bool {
		num1 := arr[i]
		num2 := arr[j]
		count1 := bitCounts[num1]
		count2 := bitCounts[num2]
		if count1 != count2 {
			return count1 < count2
		}
		return num1 < num2
	})

	return arr
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Add number by 10,0000 * bit-count
func sortByBits2(arr []int) []int {
	n := len(arr)

	for i := 0; i < n; i++ {
		arr[i] += _countBit(arr[i]) * 100_000
	}

	sort.Ints(arr)

	for i := 0; i < n; i++ {
		arr[i] %= 100_000
	}

	return arr
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

func _countBit(num int) int {
	count := 0
	for num > 0 {
		count += num % 2
		num >>= 1
	}
	return count
}
