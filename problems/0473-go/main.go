// Source: https://leetcode.com/problems/matchsticks-to-square
// Title: Matchsticks to Square
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array matchsticks where matchsticks[i] is the length of the ith matchstick. You want to use all the matchsticks to make one square. You should not break any stick, but you can link them up, and each matchstick must be used exactly one time.
//
// Return true if you can make this square and false otherwise.
//
// Example 1:
//
//   https://assets.leetcode.com/uploads/2021/04/09/matchsticks1-grid.jpg
//
//   Input: matchsticks = [1,1,2,2,2]
//   Output: true
//   Explanation: You can form a square with length 2, one side of the square came two sticks with length 1.
//
// Example 2:
//
//   Input: matchsticks = [3,3,3,3,4]
//   Output: false
//   Explanation: You cannot find a way to form a square with all the matchsticks.
//
// Constraints:
//
//   1 <= matchsticks.length <= 15
//   1 <= matchsticks[i] <= 10^8
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"sort"
)

type square struct {
	edges [4]int
}

func (s square) Hash() int {
	return s.edges[0] + s.edges[1]<<8 + s.edges[2]<<16 + s.edges[3]<<24
}

func (s square) IsSquare() bool {
	return s.edges[0] == s.edges[1] && s.edges[0] == s.edges[2] && s.edges[0] == s.edges[3]
}

func makesquare(matchsticks []int) bool {
	n := len(matchsticks)
	if n < 4 {
		return false
	}

	sum := 0
	for _, v := range matchsticks {
		sum += v
	}

	if sum%4 != 0 {
		return false
	}

	edge := sum / 4
	sort.Sort(sort.Reverse(sort.IntSlice(matchsticks)))
	if matchsticks[0] > edge {
		return false
	}

	seen := make(map[int]bool, 0)
	sq := square{}
	sq.edges[0] = matchsticks[0]

	return _makesquare(matchsticks, 1, sq, edge, seen)
}

func _makesquare(matchsticks []int, idx int, sq square, edge int, seen map[int]bool) bool {
	if idx == len(matchsticks) {
		return sq.IsSquare()
	}

	sort.Ints(sq.edges[:])

	hash := sq.Hash()
	if seen[hash] {
		return false
	}
	seen[hash] = true

	stick := matchsticks[idx]
	for i := 0; i < 4; i++ {
		sq.edges[i] += stick
		if sq.edges[i] <= edge && _makesquare(matchsticks, idx+1, sq, edge, seen) {
			return true
		}
		sq.edges[i] -= stick
	}

	return false
}
