// Source: https://leetcode.com/problems/word-break
// Title: Word Break
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a string `s` and a dictionary of strings `wordDict`, return `true` if `s` can be segmented into a space-separated sequence of one or more dictionary words.
//
// **Note** that the same word in the dictionary may be reused multiple times in the segmentation.
//
// **Example 1:**
//
// ```
// Input: s = "leetcode", wordDict = ["leet","code"]
// Output: true
// Explanation: Return true because "leetcode" can be segmented as "leet code".
// ```
//
// **Example 2:**
//
// ```
// Input: s = "applepenapple", wordDict = ["apple","pen"]
// Output: true
// Explanation: Return true because "applepenapple" can be segmented as "apple pen apple".
// Note that you are allowed to reuse a dictionary word.
// ```
//
// **Example 3:**
//
// ```
// Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
// Output: false
// ```
//
// **Constraints:**
//
// - `1 <= s.length <= 300`
// - `1 <= wordDict.length <= 1000`
// - `1 <= wordDict[i].length <= 20`
// - `s` and `wordDict[i]` consist of only lowercase English letters.
// - All the strings of `wordDict` are **unique**.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  bool wordBreak(string s, vector<string>& wordDict) {
    int n = s.size();

    // Word Map
    auto wordMap = unordered_set<string>(wordDict.begin(), wordDict.end());

    // DP
    auto dp = vector<bool>(n + 1);
    dp[0] = true;
    for (auto i = 0; i < n; i++) {
      if (!dp[i]) continue;

      for (auto l = 1; l < 20; l++) {
        auto j = i + l;
        if (j > n) break;

        if (wordMap.count(s.substr(i, l))) {
          dp[j] = true;
        }
      }
    }

    return dp[n];
  }
};
