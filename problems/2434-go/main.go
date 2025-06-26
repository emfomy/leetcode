// Source: httphttps://leetcode.com/problems/using-a-robot-to-print-the-lexicographically-smallest-string
// Title: Using a Robot to Print the Lexicographically Smallest String
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a string `s` and a robot that currently holds an empty string `t`. Apply one of the following operations until `s` and `t` **are both empty**:
//
// - Remove the **first** character of a string `s` and give it to the robot. The robot will append this character to the string `t`.
// - Remove the **last** character of a string `t` and give it to the robot. The robot will write this character on paper.
//
// Return the lexicographically smallest string that can be written on the paper.
//
// **Example 1:**
//
// ```
// Input: s = "zza"
// Output: "azz"
// Explanation: Let p denote the written string.
// Initially p="", s="zza", t="".
// Perform first operation three times p="", s="", t="zza".
// Perform second operation three times p="azz", s="", t="".
// ```
//
// **Example 2:**
//
// ```
// Input: s = "bac"
// Output: "abc"
// Explanation: Let p denote the written string.
// Perform first operation twice p="", s="c", t="ba".
// Perform second operation twice p="ab", s="c", t="".
// Perform first operation p="ab", s="", t="c".
// Perform second operation p="abc", s="", t="".
// ```
//
// **Example 3:**
//
// ```
// Input: s = "bdda"
// Output: "addb"
// Explanation: Let p denote the written string.
// Initially p="", s="bdda", t="".
// Perform first operation four times p="", s="", t="bdda".
// Perform second operation four times p="addb", s="", t="".
// ```
//
// **Constraints:**
//
// - `1 <= s.length <= 10^5`
// - `s` consists of only English lowercase letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// Simulation
//
// We only pop from the stack `t` when top letter is less than the minimal letter in `s`.
func robotWithString(s string) string {
	n := len(s)
	stack := make([]byte, 0, n)

	// Counter
	counter := [27]int{}
	for i := range n {
		counter[s[i]-'a']++
	}
	counter[26] = 1

	// Simulation
	minS := byte('a')
	ans := make([]byte, 0, n)
	for i := range n {
		c := s[i]
		stack = append(stack, c)
		counter[c-'a']--

		for counter[minS-'a'] == 0 {
			minS++
		}

		for len(stack) > 0 && stack[len(stack)-1] <= minS {
			ans = append(ans, stack[len(stack)-1])
			stack = stack[:len(stack)-1]
		}
	}

	return string(ans)
}
