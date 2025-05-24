// Source: https://leetcode.com/problems/count-of-smaller-numbers-after-self
// Title: Count of Smaller Numbers After Self
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array nums and you have to return a new counts array. The counts array has the property where counts[i] is the number of smaller elements to the right of nums[i].
//
// Example 1:
//
//   Input: nums = [5,2,6,1]
//   Output: [2,1,1,0]
//   Explanation:
//     To the right of 5 there are 2 smaller elements (2 and 1).
//     To the right of 2 there is only 1 smaller element (1).
//     To the right of 6 there is 1 smaller element (1).
//     To the right of 1 there is 0 smaller element.
//
// Example 2:
//
//   Input: nums = [-1]
//   Output: [0]
//
// Example 3:
//
// Input: nums = [-1,-1]
// Output: [0,0]
//
// Constraints:
//
//   1 <= nums.length <= 10^5
//   -10^4 <= nums[i] <= 10^4
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

type pair struct {
	val int
	idx int
}

// Use merge sort
func countSmaller(nums []int) []int {
	n := len(nums)
	arr := make([]pair, n)
	tmp := make([]pair, n)
	count := make([]int, n)

	for i, num := range nums {
		arr[i] = pair{val: num, idx: i}
	}
	_mergeSort(arr, tmp, count, 0, n)

	return count
}

func _mergeSort(arr, tmp []pair, count []int, left, right int) {
	if left == right || left+1 == right {
		return
	}

	mid := (left + right) / 2
	_mergeSort(arr, tmp, count, left, mid)
	_mergeSort(arr, tmp, count, mid, right)

	l := left
	r := mid
	o := left

	for l < mid && r < right {
		lPair := arr[l]
		rPair := arr[r]

		if lPair.val <= rPair.val {
			tmp[o] = lPair
			count[lPair.idx] += r - mid
			l++
			o++
		} else {
			tmp[o] = rPair
			r++
			o++
		}
	}

	for l < mid {
		lPair := arr[l]
		tmp[o] = lPair
		count[lPair.idx] += r - mid
		l++
		o++
	}

	for r < right {
		rPair := arr[r]
		tmp[o] = rPair
		r++
		o++
	}

	for i := left; i < right; i++ {
		arr[i] = tmp[i]
	}
}
