// Source: https://leetcode.com/problems/rabbits-in-forest
// Title: Rabbits in Forest
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There is a forest with an unknown number of rabbits. We asked n rabbits **"How many rabbits have the same color as you?"** and collected the answers in an integer array `answers` where `answers[i]` is the answer of the `i^th` rabbit.
//
// Given the array `answers`, return the minimum number of rabbits that could be in the forest.
//
// **Example 1:**
//
// ```
// Input: answers = [1,1,2]
// Output: 5
// Explanation:
// The two rabbits that answered "1" could both be the same color, say red.
// The rabbit that answered "2" can't be red or the answers would be inconsistent.
// Say the rabbit that answered "2" was blue.
// Then there should be 2 other blue rabbits in the forest that didn't answer into the array.
// The smallest possible number of rabbits in the forest is therefore 5: 3 that answered plus 2 that didn't.
// ```
//
// **Example 2:**
//
// ```
// Input: answers = [10,10,10]
// Output: 11
// ```
//
// **Constraints:**
//
// - `1 <= answers.length <= 1000`
// - `0 <= answers[i] < 1000`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import "fmt"

// The rabbits with different answer must be in different color.
// Say there are m rabbits answered k.
//
// If m <= k+1, then they could be the same color (that is, at least k+1 rabbits).
// If m > k+1, then there must be more than one color.
// Assume that first k+1 rabbits the same color.
// Next we have (m-k-1) rabbits answered k (keep doing with recursion).
//
// Now we can conclude that there are ceil(m / (k+1)) * (k+1) rabbits (i.e. round m up to the multiple of (k+1)).
func numRabbits(answers []int) int {
	ansCount := make(map[int]int) // answer to rabbit count
	for _, ans := range answers {
		ansCount[ans]++
	}

	res := 0
	for ans, count := range ansCount {
		fmt.Println(ans, count)
		res += ((count + ans) / (ans + 1)) * (ans + 1)
	}

	return res
}
