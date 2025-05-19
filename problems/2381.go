// Source: https://leetcode.com/problems/shifting-letters-ii
// Title: Shifting Letters II
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a string `s` of lowercase English letters and a 2D integer array `shifts` where `shifts[i] = [start_i, end_i, direction_i]`. For every `i`, **shift** the characters in `s` from the index `start_i` to the index `end_i` (**inclusive** ) forward if `direction_i = 1`, or shift the characters backward if `direction_i = 0`.
//
// Shifting a character **forward** means replacing it with the **next** letter in the alphabet (wrapping around so that `'z'` becomes `'a'`). Similarly, shifting a character **backward** means replacing it with the **previous** letter in the alphabet (wrapping around so that `'a'` becomes `'z'`).
//
// Return the final string after all such shifts to `s` are applied.
//
// **Example 1:**
//
// ```
// Input: s = "abc", shifts = [[0,1,0],[1,2,1],[0,2,1]]
// Output: "ace"
// Explanation: Firstly, shift the characters from index 0 to index 1 backward. Now s = "zac".
// Secondly, shift the characters from index 1 to index 2 forward. Now s = "zbd".
// Finally, shift the characters from index 0 to index 2 forward. Now s = "ace".```
//
// **Example 2:**
//
// ```
// Input: s = "dztz", shifts = [[0,0,0],[1,1,1]]
// Output: "catz"
// Explanation: Firstly, shift the characters from index 0 to index 0 backward. Now s = "cztz".
// Finally, shift the characters from index 1 to index 1 forward. Now s = "catz".
// ```
//
// **Constraints:**
//
// - `1 <= s.length, shifts.length <= 5 * 10^4`
// - `shifts[i].length == 3`
// - `0 <= start_i <= end_i < s.length`
// - `0 <= direction_i <= 1`
// - `s` consists of lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func shiftingLetters(s string, shifts [][]int) string {
	n := len(s)
	bytes := []byte(s)

	moves := make([]int, n)
	for i := 0; i < n; i++ {
		moves[i] = int(bytes[i] - 'a')
	}

	for _, shift := range shifts {
		start, end, dir := shift[0], shift[1], shift[2]
		if dir == 0 {
			dir = -1
		}
		for i := start; i <= end; i++ {
			moves[i] += dir
		}
	}

	for i := 0; i < n; i++ {
		moves[i] = _mod(moves[i], 26)
		bytes[i] = 'a' + byte(moves[i])
	}

	return string(bytes)
}

// Use prefix sum
//
// presum[i] = sum of shift from 0 to i
//
// When we add shift (start, end, 1),
// the presum between "start" and "end" are not changed.
// We only need to update "start" and "end+1"
func shiftingLetters2(s string, shifts [][]int) string {
	n := len(s)
	bytes := []byte(s)

	presum := make([]int, n+1)
	for _, shift := range shifts {
		start, end, dir := shift[0], shift[1], shift[2]
		if dir == 1 {
			presum[start]++
			presum[end+1]--
		} else {
			presum[start]--
			presum[end+1]++
		}
	}

	move := 0
	for i := 0; i < n; i++ {
		move += presum[i]
		bytes[i] = byte(_mod(int(bytes[i]-'a')+move, 26)) + 'a'
	}

	return string(bytes)
}

func _mod(a, b int) int {
	a %= b
	if a < 0 {
		a += b
	}
	return a
}
