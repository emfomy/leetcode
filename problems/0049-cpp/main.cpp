// Source: https://leetcode.com/problems/group-anagrams
// Title: Group Anagrams
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given two strings `s` and `t`, return `true` if `t` is an <button type="button" aria-haspopup="dialog" aria-expanded="false" aria-controls="radix-:rs:" data-state="closed" class="">anagram</button> of `s`, and `false` otherwise.
//
// **Example 1:**
//
// ```
// Input: s = "anagram", t = "nagaram"
// Output: true
// ```
//
// **Example 2:**
//
// ```
// Input: s = "rat", t = "car"
// Output: false
// ```
//
// **Constraints:**
//
// - `1 <= s.length, t.length <= 5 * 10^4`
// - `s` and `t` consist of lowercase English letters.
//
// **Follow up:** What if the inputs contain Unicode characters? How would you adapt your solution to such a case?
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <unordered_map>
#include <vector>

using namespace std;

// Use sort + hashmap
class Solution {
 public:
  vector<vector<string>> groupAnagrams(vector<string>& strs) {
    unordered_map<string, vector<string>> groups;
    for (auto& str : strs) {
      auto key = str;
      sort(key.begin(), key.end());
      groups[key].push_back(str);
    }

    vector<vector<string>> ans;
    for (auto& [_, vals] : groups) {
      ans.push_back(vals);
    }

    return ans;
  }
};
