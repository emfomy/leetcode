// Source: https://leetcode.com/problems/group-anagrams
// Title: Group Anagrams
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array of strings `strs`, group the **anagrams** together. You can return the answer in **any order**.
//
// **Example 1:**
//
// Input: strs = ["eat","tea","tan","ate","nat","bat"]
//
// Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
//
// Explanation:
//
// - There is no string in strs that can be rearranged to form `"bat"`.
// - The strings `"nat"` and `"tan"` are anagrams as they can be rearranged to form each other.
// - The strings `"ate"`, `"eat"`, and `"tea"` are anagrams as they can be rearranged to form each other.
//
// **Example 2:**
//
// ```
// Input: strs = [""]
// Output: [[""]]
// ```
//
// **Example 3:**
//
// ```
// Input: strs = ["a"]
// Output: [["a"]]
// ```
//
// **Constraints:**
//
// - `1 <= strs.length <= 10^4`
// - `0 <= strs[i].length <= 100`
// - `strs[i]` consists of lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <unordered_map>
#include <vector>

using namespace std;

// Use sort + hashmap
class Solution {
 public:
  vector<vector<string>> groupAnagrams(const vector<string>& strs) {
    // Grouping
    unordered_map<string, vector<string>> groups;
    for (const string& str : strs) {
      string key = str;
      sort(key.begin(), key.end());
      groups[key].push_back(str);
    }

    // Output groups
    vector<vector<string>> ans;
    for (auto& [_, vals] : groups) {
      ans.push_back(vals);
    }

    return ans;
  }
};
