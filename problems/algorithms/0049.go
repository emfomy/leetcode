// Source: https://leetcode.com/problems/group-anagrams/
// Title: Group Anagrams
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array of strings strs, group the anagrams together. You can return the answer in any order.
// An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase, typically using all the original letters exactly once.
//
// Example 1:
//
//   Input: strs = ["eat","tea","tan","ate","nat","bat"]
//   Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
//
// Example 2:
//
//   Input: strs = [""]
//   Output: [[""]]
//
// Example 3:
//
//   Input: strs = ["a"]
//   Output: [["a"]]
//
// Constraints:
//
//   * 1 <= strs.length <= 10^4
//   * 0 <= strs[i].length <= 100
//   * strs[i] consists of lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"sort"
)

type RuneSlice []rune

func (x RuneSlice) Len() int           { return len(x) }
func (x RuneSlice) Less(i, j int) bool { return x[i] < x[j] }
func (x RuneSlice) Swap(i, j int)      { x[i], x[j] = x[j], x[i] }

func groupAnagrams(strs []string) [][]string {
	groupMap := make(map[string][]string, len(strs))
	for _, str := range strs {
		r := RuneSlice(str)
		sort.Sort(r)
		sorted := string(r)
		if _, ok := groupMap[sorted]; !ok {
			groupMap[sorted] = make([]string, 0)
		}
		groupMap[sorted] = append(groupMap[sorted], str)
	}

	groups := make([][]string, 0, len(groupMap))
	for _, group := range groupMap {
		groups = append(groups, group)
	}
	return groups
}
