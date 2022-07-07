// Source: https://leetcode.com/problems/candy/
// Title: Candy
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There are n children standing in a line. Each child is assigned a rating value given in the integer array ratings.
//
// You are giving candies to these children subjected to the following requirements:
//
// Each child must have at least one candy.
// Children with a higher rating get more candies than their neighbors.
// Return the minimum number of candies you need to have to distribute the candies to the children.
//
// Example 1:
//
//   Input: ratings = [1,0,2]
//   Output: 5
//   Explanation: You can allocate to the first, second and third child with 2, 1, 2 candies respectively.
//
// Example 2:
//
//   Input: ratings = [1,2,2]
//   Output: 4
//   Explanation:
//     You can allocate to the first, second and third child with 1, 2, 1 candies respectively.
//     The third child gets 1 candy because it satisfies the above two conditions.
//
// Constraints:
//
//   n == ratings.length
//   1 <= n <= 2 * 10^4
//   0 <= ratings[i] <= 2 * 10^4
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Use Sort

import (
	"sort"
)

type IdxSlice struct {
	sort.IntSlice
	indices []int
}

func (s IdxSlice) Swap(i, j int) {
	s.IntSlice.Swap(i, j)
	s.indices[i], s.indices[j] = s.indices[j], s.indices[i]
}

func candy(ratings []int) int {
	n := len(ratings)

	// Set indices
	tmp := make([]int, n)
	indices := make([]int, n)
	for i := 0; i < n; i++ {
		tmp[i] = ratings[i]
		indices[i] = i
	}

	// Sort indices
	sort.Sort(IdxSlice{
		IntSlice: tmp,
		indices:  indices,
	})

	res := 0
	candies := tmp // Reuse space

	for _, idx := range indices {
		candies[idx] = 1
		if idx > 0 && ratings[idx] > ratings[idx-1] {
			candies[idx] = _max(candies[idx], candies[idx-1]+1)
		}
		if idx < n-1 && ratings[idx] > ratings[idx+1] {
			candies[idx] = _max(candies[idx], candies[idx+1]+1)
		}
		res += candies[idx]
	}

	return res
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Use Two Arries

func candy2(ratings []int) int {
	n := len(ratings)
	left := make([]int, n)
	right := make([]int, n)

	left[0] = 1
	for i := 1; i < n; i++ {
		if ratings[i] > ratings[i-1] {
			left[i] = left[i-1] + 1
		} else {
			left[i] = 1
		}
	}

	right[n-1] = 1
	for i := n - 2; i >= 0; i-- {
		if ratings[i] > ratings[i+1] {
			right[i] = right[i+1] + 1
		} else {
			right[i] = 1
		}
	}

	res := 0
	for i := 0; i < n; i++ {
		res += _max(left[i], right[i])
	}
	return res
}

func _max(a, b int) int {
	if a > b {
		return a
	}
	return b
}
