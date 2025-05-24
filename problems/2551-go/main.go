// Source: https://leetcode.com/problems/put-marbles-in-bags
// Title: Put Marbles in Bags
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You have `k` bags. You are given a **0-indexed** integer array `weights` where `weights[i]` is the weight of the `i^th` marble. You are also given the integer `k`.
//
// Divide the marbles into the `k` bags according to the following rules:
//
// - No bag is empty.
// - If the `i^th` marble and `j^th` marble are in a bag, then all marbles with an index between the `i^th` and `j^th` indices should also be in that same bag.
// - If a bag consists of all the marbles with an index from `i` to `j` inclusively, then the cost of the bag is `weights[i] + weights[j]`.
//
// The **score** after distributing the marbles is the sum of the costs of all the `k` bags.
//
// Return the **difference** between the **maximum** and **minimum** scores among marble distributions.
//
// **Example 1:**
//
// ```
// Input: weights = [1,3,5,1], k = 2
// Output: 4
// Explanation:
// The distribution [1],[3,5,1] results in the minimal score of (1+1) + (3+1) = 6.
// The distribution [1,3],[5,1], results in the maximal score of (1+3) + (5+1) = 10.
// Thus, we return their difference 10 - 6 = 4.
// ```
//
// **Example 2:**
//
// ```
// Input: weights = [1, 3], k = 2
// Output: 0
// Explanation: The only distribution possible is [1],[3].
// Since both the maximal and minimal score are the same, we return 0.
// ```
//
// **Constraints:**
//
// - `1 <= k <= weights.length <= 10^5`
// - `1 <= weights[i] <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"slices"
)

// Say we put [a_i, a_{i+1} - 1] in bag i, a_1 = 1, a_k = n.
// The score is w[1] + w[a_2 - 1] + w[a_2] + ... + w[a_k].
// That is, we need to maximum / minimum sum(w[a_i - 1] + w[a_i])
func putMarbles(weights []int, k int) int64 {
	n := len(weights)

	scores := make([]int, n-1)
	for i := range n - 1 {
		scores[i] = weights[i] + weights[i+1]
	}
	slices.Sort(scores)

	maxScore, minScore := 0, 0
	for i := range k - 1 {
		maxScore += scores[n-2-i]
		minScore += scores[i]
	}

	return int64(maxScore - minScore)
}
