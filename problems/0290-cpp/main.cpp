// Source: https://leetcode.com/problems/word-pattern
// Title: Word Pattern
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

#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

class Solution {
 public:
  vector<string> split(string& s) {
    istringstream iss(s);
    vector<string> words;
    string word;
    while (iss >> word) {
      words.push_back(word);
    }
    return words;
  }

  bool wordPattern(string pattern, string s) {
    auto n = pattern.size();

    auto words = split(s);
    if (words.size() != n) {
      return false;
    }

    unordered_set<char> cSet;
    unordered_set<string> wSet;
    unordered_set<string> pSet;  // pair, char + ':' + string
    for (auto i = 0; i < n; i++) {
      cSet.insert(pattern[i]);
      wSet.insert(words[i]);
      pSet.insert(string(1, pattern[i]) + ":" + words[i]);
    }

    return cSet.size() == wSet.size() && cSet.size() == pSet.size();
  }
};
