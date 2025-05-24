// Source: https://leetcode.com/problems/reduce-array-size-to-the-half
// Title: Reduce Array Size to The Half
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array arr. You can choose a set of integers and remove all the occurrences of these integers in the array.
//
// Return the minimum size of the set so that at least half of the integers of the array are removed.
//
// Example 1:
//
//   Input: arr = [3,3,3,3,5,5,5,2,2,7]
//   Output: 2
//   Explanation:
//     Choosing {3,7} will make the new array [5,5,5,2,2] which has size 5 (i.e equal to half of the size of the old array).
//     Possible sets of size 2 are {3,5},{3,2},{5,2}.
//     Choosing set {2,7} is not possible as it will make the new array [3,3,3,3,5,5,5] which has a size greater than half of the size of the old array.
//
// Example 2:
//
//   Input: arr = [7,7,7,7,7,7]
//   Output: 1
//   Explanation: The only possible set you can choose is {7}. This will make the new array empty.
//
// Constraints:
//
//   2 <= arr.length <= 10^5
//   arr.length is even.
//   1 <= arr[i] <= 10^5
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"sort"
)

func minSetSize(arr []int) int {
	l := len(arr)

	countMap := make(map[int]int, l)
	for _, num := range arr {
		countMap[num]++
	}

	counts := make([]int, 0, len(countMap))
	for _, cnt := range countMap {
		counts = append(counts, cnt)
	}

	sort.Sort(sort.Reverse(sort.IntSlice(counts)))

	sum := 0
	for i, v := range counts {
		sum += v
		if 2*sum >= l {
			return i + 1
		}
	}

	return -1
}
