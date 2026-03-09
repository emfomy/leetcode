// Source: https://leetcode.com/problems/longest-common-prefix
// Title: Longest Common Prefix
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Write a function to find the longest common prefix string amongst an array of strings.
//
// If there is no common prefix, return an empty string `""`.
//
// **Example 1:**
//
// ```
// Input: strs = ["flower","flow","flight"]
// Output: "fl"
// ```
//
// **Example 2:**
//
// ```
// Input: strs = ["dog","racecar","car"]
// Output: ""
// Explanation: There is no common prefix among the input strings.
// ```
//
// **Constraints:**
//
// - `1 <= strs.length <= 200`
// - `0 <= strs[i].length <= 200`
// - `strs[i]` consists of only lowercase English letters if it is non-empty.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

class Solution {
 public:
  string longestCommonPrefix(const vector<string>& strs) {
    // Guard
    if (strs.empty()) return "";

    // Find minimal length
    int n = strs[0].size();
    for (const auto& str : strs) {
      n = min(n, int(str.size()));
    }

    // Try [0, j] as common prefix
    int j = 0;
    for (; j < n; ++j) {
      const char ch = strs[0][j];
      auto cond = [ch, j](const string& str) { return str[j] == ch; };
      if (!all_of(strs.cbegin(), strs.cend(), cond)) break;
    }

    return strs[0].substr(0, j);
  }
};
