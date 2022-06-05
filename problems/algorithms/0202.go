// Source: https://leetcode.com/problems/happy-number/
// Title: Happy Number
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Write an algorithm to determine if a number n is happy.
//
// A happy number is a number defined by the following process:
//
//   Starting with any positive integer, replace the number by the sum of the squares of its digits.
//   Repeat the process until the number equals 1 (where it will stay), or it loops endlessly in a cycle which does not include 1.
//   Those numbers for which this process ends in 1 are happy.
//
// Return true if n is a happy number, and false if not.
//
// Example 1:
//
//   Input: n = 19
//   Output: true
//   Explanation:
//     12 + 92 = 82
//     82 + 22 = 68
//     62 + 82 = 100
//     12 + 02 + 02 = 1
//
// Example 2:
//
//   Input: n = 2
//   Output: false
//
// Constraints:
//
//   1 <= n <= 2^31 - 1
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

type void struct{}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Hash set; O(n) space
func isHappy(n int) bool {
	set := make(map[int]void) // stores visited numbers

	for ; n != 1; n = _getNext(n) {
		if _, ok := set[n]; ok { // in cycle
			return false
		}
		set[n] = void{}
	}
	return true
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Floyd's Cycle-Finding Algorithm; O(1) space
func isHappy2(n int) bool {
	slow := n           // slow runner
	fast := _getNext(n) // fast runner

	for fast != 1 && slow != fast {
		slow = _getNext(slow)
		fast = _getNext(_getNext(fast))
	}

	return fast == 1
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

func _getNext(n int) int {
	res := 0
	for ; n > 0; n /= 10 {
		res += (n % 10) * (n % 10)
	}
	return res
}
