// Source: https://leetcode.com/problems/candy
// Title: Candy
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There are `n` children standing in a line. Each child is assigned a rating value given in the integer array `ratings`.
//
// You are giving candies to these children subjected to the following requirements:
//
// - Each child must have at least one candy.
// - Children with a higher rating get more candies than their neighbors.
//
// Return the minimum number of candies you need to have to distribute the candies to the children.
//
// **Example 1:**
//
// ```
// Input: ratings = [1,0,2]
// Output: 5
// Explanation: You can allocate to the first, second and third child with 2, 1, 2 candies respectively.
// ```
//
// **Example 2:**
//
// ```
// Input: ratings = [1,2,2]
// Output: 4
// Explanation: You can allocate to the first, second and third child with 1, 2, 1 candies respectively.
// The third child gets 1 candy because it satisfies the above two conditions.
// ```
//
// **Constraints:**
//
// - `n == ratings.length`
// - `1 <= n <= 2 * 10^4`
// - `0 <= ratings[i] <= 2 * 10^4`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"slices"
)

// Sort
func candy(ratings []int) int {
	n := len(ratings)

	// Sort with indices
	idxs := make([]int, n)
	for i := range n {
		idxs[i] = i
	}
	slices.SortFunc(idxs, func(i, j int) int {
		return ratings[i] - ratings[j]
	})

	// Distribute candies
	candies := make([]int, n)
	ans := 0
	for _, i := range idxs {
		candy := 1
		if i > 0 && ratings[i] > ratings[i-1] {
			candy = max(candy, candies[i-1]+1)
		}
		if i < n-1 && ratings[i] > ratings[i+1] {
			candy = max(candy, candies[i+1]+1)
		}
		candies[i] = candy
		ans += candy
	}

	return ans
}

// Traversal in both direction
func candy2(ratings []int) int {
	n := len(ratings)
	candies := make([]int, n) // stores less 1 candy than actual value

	// Forward
	for i := 1; i < n; i++ {
		if ratings[i] > ratings[i-1] {
			candies[i] = max(candies[i], candies[i-1]+1)
		}
	}

	// Backward
	for i := n - 2; i >= 0; i-- {
		if ratings[i] > ratings[i+1] {
			candies[i] = max(candies[i], candies[i+1]+1)
		}
	}

	// Answer
	ans := n
	for _, candy := range candies {
		ans += candy
	}
	return ans
}
