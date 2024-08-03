// Source: https://leetcode.com/problems/queue-reconstruction-by-height
// Title: Queue Reconstruction by Height
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an array of people, people, which are the attributes of some people in a queue (not necessarily in order). Each people[i] = [h_i, k_i] represents the ith person of height h_i with exactly k_i other people in front who have a height greater than or equal to h_i.
//
// Reconstruct and return the queue that is represented by the input array people. The returned queue should be formatted as an array queue, where queue[j] = [hj, kj] is the attributes of the jth person in the queue (queue[0] is the person at the front of the queue).
//
// Example 1:
//
//   Input: people = [[7,0],[4,4],[7,1],[5,0],[6,1],[5,2]]
//   Output: [[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]]
//   Explanation:
//     Person 0 has height 5 with no other people taller or the same height in front.
//     Person 1 has height 7 with no other people taller or the same height in front.
//     Person 2 has height 5 with two persons taller or the same height in front, which is person 0 and 1.
//     Person 3 has height 6 with one person taller or the same height in front, which is person 1.
//     Person 4 has height 4 with four people taller or the same height in front, which are people 0, 1, 2, and 3.
//     Person 5 has height 7 with one person taller or the same height in front, which is person 1.
//     Hence [[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]] is the reconstructed queue.
//
// Example 2:
//
//   Input: people = [[6,0],[5,0],[4,0],[3,2],[2,2],[1,4]]
//   Output: [[4,0],[5,0],[2,2],[3,2],[1,4],[6,0]]
//
// Constraints:
//
//   1 <= people.length <= 2000
//   0 <= h_i <= 10^6
//   0 <= k_i < people.length
//   It is guaranteed that the queue can be reconstructed.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"sort"
)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Use swap
func reconstructQueue(people [][]int) [][]int {
	n := len(people)
	tmp := make([]int, n)

	for i := 0; i < n; i++ {
		for j := 0; j < i; j++ {
			if people[j][0] >= people[i][0] {
				tmp[i]++
			}
		}
	}

	done := false
	for !done {
		done = true
		for i := 0; i < n; i++ {
			if tmp[i] < people[i][1] {
				done = false
				if people[i][0] <= people[i+1][0] {
					tmp[i]++
				}
				if people[i][0] >= people[i+1][0] {
					tmp[i+1]--
				}
				people[i], people[i+1] = people[i+1], people[i]
				tmp[i], tmp[i+1] = tmp[i+1], tmp[i]
			} else if tmp[i] > people[i][1] {
				done = false
				if people[i][0] <= people[i-1][0] {
					tmp[i]--
				}
				if people[i][0] >= people[i-1][0] {
					tmp[i-1]++
				}
				people[i], people[i-1] = people[i-1], people[i]
				tmp[i], tmp[i-1] = tmp[i-1], tmp[i]
			}
		}
	}

	return people
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Use sort and insert
func reconstructQueue2(people [][]int) [][]int {
	sort.Slice(people, func(i, j int) bool {
		if people[i][0] == people[j][0] {
			return people[i][1] < people[j][1]
		}
		return people[i][0] > people[j][0]
	})

	for i, p := range people {
		// Move p to p[1]
		for j := i; j > p[1]; j-- {
			people[j] = people[j-1]
		}
		people[p[1]] = p
	}

	return people
}