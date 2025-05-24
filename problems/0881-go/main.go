// Source: https://leetcode.com/problems/boats-to-save-people
// Title: Boats to Save People
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an array people where people[i] is the weight of the ith person, and an infinite number of boats where each boat can carry a maximum weight of limit. Each boat carries at most two people at the same time, provided the sum of the weight of those people is at most limit.
// Return the minimum number of boats to carry every given person.
//
// Example 1:
//
//   Input: people = [1,2], limit = 3
//   Output: 1
//   Explanation: 1 boat (1, 2)
//
// Example 2:
//
//   Input: people = [3,2,2,1], limit = 3
//   Output: 3
//   Explanation: 3 boats (1, 2), (2) and (3)
//
// Example 3:
//
//   Input: people = [3,5,3,4], limit = 5
//   Output: 4
//   Explanation: 4 boats (3), (3), (4), (5)
//
// Constraints:
//
//   1 <= people.length <= 5 * 10^4
//   1 <= people[i] <= limit <= 3 * 10^4
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"slices"
)

func numRescueBoats(people []int, limit int) int {
	slices.Sort(people)

	i1 := 0
	i2 := len(people) - 1

	total := 0
	for i1 <= i2 { // Here we allow equals since the last people need a boat no matter what his/her weight is
		if people[i1]+people[i2] <= limit {
			i1++
			i2--
		} else {
			i2--
		}
		total++
	}

	return total
}
