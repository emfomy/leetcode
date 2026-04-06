// Source: https://leetcode.com/problems/string-matching-in-an-array
// Title: String Matching in an Array
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array of string `words`, return all strings in `words` that are a <button>substring</button> of another word. You can return the answer in **any order**.
//
// **Example 1:**
//
// ```
// Input: words = ["mass","as","hero","superhero"]
// Output: ["as","hero"]
// Explanation: "as" is substring of "mass" and "hero" is substring of "superhero".
// ["hero","as"] is also a valid answer.
// ```
//
// **Example 2:**
//
// ```
// Input: words = ["leetcode","et","code"]
// Output: ["et","code"]
// Explanation: "et", "code" are substring of "leetcode".
// ```
//
// **Example 3:**
//
// ```
// Input: words = ["blue","green","bu"]
// Output: []
// Explanation: No string of words is substring of another string.
// ```
//
// **Constraints:**
//
// - `1 <= words.length <= 100`
// - `1 <= words[i].length <= 30`
// - `words[i]` contains only lowercase English letters.
// - All the strings of `words` are **unique**.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>

using namespace std;

// Brute-Force
class Solution {
 public:
  vector<string> stringMatching(const vector<string>& words) {
    const int n = words.size();

    // Prepare
    auto ans = vector<string>();
    ans.reserve(n);

    // Loop
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (i == j) continue;
        if (words[j].find(words[i]) != string::npos) {
          ans.push_back(words[i]);
          break;
        }
      }
    }

    return ans;
  }
};

// KMP
class Solution2 {
  vector<int> buildLPS(const string& str) {
    const int n = str.size();
    auto lps = vector<int>(n);

    int prev = 0;
    int i = 1;
    while (i < n) {
      if (str[i] == str[prev]) {
        lps[i++] = ++prev;
      } else if (prev == 0) {
        lps[i++] = 0;
      } else {
        prev = lps[prev - 1];
      }
    }

    return lps;
  }

  bool matchSubstr(const string& text, const string& pattern, const vector<int>& lps) {
    const int n = text.size(), m = pattern.size();

    int i = 0, j = 0;
    while (i < n) {
      if (text[i] == pattern[j]) {
        ++i, ++j;
      } else if (j == 0) {
        ++i;
      } else {
        j = lps[j - 1];
      }
      if (j == m) return true;
    }
    return false;
  }

 public:
  vector<string> stringMatching(const vector<string>& words) {
    const int n = words.size();

    // Prepare
    auto ans = vector<string>();
    ans.reserve(n);

    // Loop
    for (int i = 0; i < n; ++i) {
      const auto& lps = buildLPS(words[i]);
      for (int j = 0; j < n; ++j) {
        if (i == j) continue;
        if (matchSubstr(words[j], words[i], lps)) {
          ans.push_back(words[i]);
          break;
        }
      }
    }

    return ans;
  }
};
