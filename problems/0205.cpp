// Source: https://leetcode.com/problems/isomorphic-strings
// Title: Isomorphic Strings
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given two strings `s` and `t`, determine if they are isomorphic.
//
// Two strings `s` and `t` are isomorphic if the characters in `s` can be replaced to get `t`.
//
// All occurrences of a character must be replaced with another character while preserving the order of characters. No two characters may map to the same character, but a character may map to itself.
//
// **Example 1:**
//
// ```
// Input: s = "egg", t = "add"
// Output: true
// Explanation:
// The strings `s` and `t` can be made identical by:
// - Mapping `'e'` to `'a'`.
// - Mapping `'g'` to `'d'`.
// ```
//
// **Example 2:**
//
// ```
// Input: s = "foo", t = "bar"
// Output: false
// Explanation:
// The strings `s` and `t` can not be made identical as `'o'` needs to be mapped to both `'a'` and `'r'`.
// ```
//
// **Example 3:**
//
// ```
// Input: s = "paper", t = "title"
// Output: true
// ```
//
// **Constraints:**
//
// - `1 <= s.length <= 5 * 10^4`
// - `t.length == s.length`
// - `s` and `t` consist of any valid ascii character.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <unordered_map>
#include <unordered_set>
using namespace std;

// Use counter
class Solution {
 public:
  bool isIsomorphic(string s, string t) {
    int n = s.size();
    unordered_set<char> used;
    unordered_map<char, char> mapping;

    for (auto i = 0; i < n; i++) {
      if (mapping[s[i]] == 0 && !used.count(t[i])) {
        mapping[s[i]] = t[i];
        used.insert(t[i]);
      }

      if (mapping[s[i]] != t[i]) {
        return false;
      }
    }
    return true;
  }
};

// Use set size
// Check if everything can be paired
class Solution2 {
 public:
  bool isIsomorphic(string s, string t) {
    int n = s.size();

    unordered_set<char> sSet;
    unordered_set<char> tSet;
    unordered_set<int> pSet;

    for (auto i = 0; i < n; i++) {
      sSet.insert(s[i]);
      tSet.insert(t[i]);
      pSet.insert((s[i] << 8) + t[i]);
    }

    return sSet.size() == tSet.size() && sSet.size() == pSet.size();
  }
};
