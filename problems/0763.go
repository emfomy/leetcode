// Source: https://leetcode.com/problems/partition-labels
// Title: Partition Labels
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a string `s`. We want to partition the string into as many parts as possible so that each letter appears in at most one part. For example, the string `"ababcc"` can be partitioned into `["abab", "cc"]`, but partitions such as `["aba", "bcc"]` or `["ab", "ab", "cc"]` are invalid.
//
// Note that the partition is done so that after concatenating all the parts in order, the resultant string should be `s`.
//
// Return a list of integers representing the size of these parts.
//
// **Example 1:**
//
// ```
// Input: s = "ababcbacadefegdehijhklij"
// Output: [9,7,8]
// Explanation:
// The partition is "ababcbaca", "defegde", "hijhklij".
// This is a partition so that each letter appears in at most one part.
// A partition like "ababcbacadefegde", "hijhklij" is incorrect, because it splits s into less parts.
// ```
//
// **Example 2:**
//
// ```
// Input: s = "eccbbbbdec"
// Output: [10]
// ```
//
// **Constraints:**
//
// - `1 <= s.length <= 500`
// - `s` consists of lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func partitionLabels(s string) []int {
	n := len(s)

	// Find last index
	lastIdxs := make([]int, 26)
	for i := range n {
		lastIdxs[s[i]-'a'] = i + 1
	}

	// Do partition
	res := make([]int, 0, 26)
	start, end := 0, lastIdxs[s[0]-'a']
	for true {
		for i := start; i < end; i++ {
			end = max(end, lastIdxs[s[i]-'a'])
		}
		res = append(res, end-start)
		if end >= n {
			break
		}
		start, end = end, lastIdxs[s[end]-'a']
	}
	return res
}
