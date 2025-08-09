// Source: https://leetcode.com/problems/delete-characters-to-make-fancy-string
// Title: Delete Characters to Make Fancy String
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// A **fancy string** is a string where no **three** **consecutive** characters are equal.
//
// Given a string `s`, delete the **minimum** possible number of characters from `s` to make it **fancy**.
//
// Return the final string after the deletion. It can be shown that the answer will always be **unique**.
//
// **Example 1:**
//
// ```
// Input: s = "leeetcode"
// Output: "leetcode"
// Explanation:
// Remove an 'e' from the first group of 'e's to create "leetcode".
// No three consecutive characters are equal, so return "leetcode".
// ```
//
// **Example 2:**
//
// ```
// Input: s = "aaabaaaa"
// Output: "aabaa"
// Explanation:
// Remove an 'a' from the first group of 'a's to create "aabaaaa".
// Remove two 'a's from the second group of 'a's to create "aabaa".
// No three consecutive characters are equal, so return "aabaa".
// ```
//
// **Example 3:**
//
// ```
// Input: s = "aab"
// Output: "aab"
// Explanation: No three consecutive characters are equal, so return "aab".
// ```
//
// **Constraints:**
//
// - `1 <= s.length <= 10^5`
// - `s` consists only of lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func makeFancyString(s string) string {
	n := len(s)
	ans := make([]byte, 0, n)

	currCh := byte(' ')
	currCnt := 0
	for i := range n {
		ch := s[i]
		if ch == currCh {
			currCnt++
		} else {
			currCh = ch
			currCnt = 0
		}
		if currCnt < 2 {
			ans = append(ans, ch)
		}
	}

	return string(ans)
}
