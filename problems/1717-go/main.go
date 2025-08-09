// Source: https://leetcode.com/problems/maximum-score-from-removing-substrings
// Title: Maximum Score From Removing Substrings
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a string `s` and two integers `x` and `y`. You can perform two types of operations any number of times.
//
// - Remove substring `"ab"` and gain `x` points.
//
// - For example, when removing `"ab"` from `"cabxbae"` it becomes `"cxbae"`.
//
// - Remove substring `"ba"` and gain `y` points.
//
// - For example, when removing `"ba"` from `"cabxbae"` it becomes `"cabxe"`.
//
// Return the maximum points you can gain after applying the above operations on `s`.
//
// **Example 1:**
//
// ```
// Input: s = "cdbcbbaaabab", x = 4, y = 5
// Output: 19
// Explanation:
// - Remove the "ba" underlined in "cdbcbbaaabab". Now, s = "cdbcbbaaab" and 5 points are added to the score.
// - Remove the "ab" underlined in "cdbcbbaaab". Now, s = "cdbcbbaa" and 4 points are added to the score.
// - Remove the "ba" underlined in "cdbcbbaa". Now, s = "cdbcba" and 5 points are added to the score.
// - Remove the "ba" underlined in "cdbcba". Now, s = "cdbc" and 5 points are added to the score.
// Total score = 5 + 4 + 5 + 5 = 19.```
//
// **Example 2:**
//
// ```
// Input: s = "aabbaaxybbaabb", x = 5, y = 4
// Output: 20
// ```
//
// **Constraints:**
//
// - `1 <= s.length <= 10^5`
// - `1 <= x, y <= 10^4`
// - `s` consists of lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// Use Greedy + Stack
//
// WLOG, assume x > y.
// We push letters into stack one by one, and erase immediately if the top letters are `ab`.
// After pushing all letters, we erase `ba`.
func maximumGain(s string, x int, y int) int {
	n := len(s)

	ab := []rune{'a', 'b'}
	ba := []rune{'b', 'a'}

	// WLOG assume x > y
	if x < y {
		x, y = y, x
		ab, ba = ba, ab
	}

	ans := 0

	stack1 := make([]rune, 0, n)
	for _, ch := range s {
		stack1 = append(stack1, ch)
		if len(stack1) >= 2 && stack1[len(stack1)-2] == ab[0] && stack1[len(stack1)-1] == ab[1] {
			ans += x
			stack1 = stack1[:len(stack1)-2]
		}
	}

	stack2 := make([]rune, 0, n)
	for _, ch := range stack1 {
		stack2 = append(stack2, ch)
		if len(stack2) >= 2 && stack2[len(stack2)-2] == ba[0] && stack2[len(stack2)-1] == ba[1] {
			ans += y
			stack2 = stack2[:len(stack2)-2]
		}
	}

	return ans
}
