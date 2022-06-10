// Source: https://leetcode.com/problems/word-break/
// Title: Word Break
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a string s and a dictionary of strings wordDict, return true if s can be segmented into a space-separated sequence of one or more dictionary words.
//
// Note that the same word in the dictionary may be reused multiple times in the segmentation.
//
// Example 1:
//
//   Input: s = "leetcode", wordDict = ["leet","code"]
//   Output: true
//   Explanation: Return true because "leetcode" can be segmented as "leet code".
//
// Example 2:
//
//   Input: s = "applepenapple", wordDict = ["apple","pen"]
//   Output: true
//   Explanation:
//     Return true because "applepenapple" can be segmented as "apple pen apple".
//     Note that you are allowed to reuse a dictionary word.
//
// Example 3:
//
//   Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
//   Output: false
//
// Constraints:
//
//   1 <= s.length <= 300
//   1 <= wordDict.length <= 1000
//   1 <= wordDict[i].length <= 20
//   s and wordDict[i] consist of only lowercase English letters.
//   All the strings of wordDict are unique.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func wordBreak(s string, wordDict []string) bool {
	n := len(s)
	dp := make([]bool, n+1) // whether s[0:i] can be segmented
	dp[0] = true

	for i := 0; i < n; i++ {
		if !dp[i] {
			continue
		}
		for _, word := range wordDict {
			j := i + len(word)
			if j <= n && s[i:j] == word {
				dp[j] = true
			}
		}
	}

	return dp[n]
}
