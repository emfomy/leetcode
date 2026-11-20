// Source: https://leetcode.com/problems/minimum-window-substring
// Title: Minimum Window Substring
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given two strings `s` and `t` of lengths `m` and `n` respectively, return the **minimum window** <button type="button" aria-haspopup="dialog" aria-expanded="false" aria-controls="radix-:rs:" data-state="closed" class="">**substring**</button> of `s` such that every character in `t` (**including duplicates**) is included in the window. If there is no such substring, return the empty string `""`.
//
// The testcases will be generated such that the answer is **unique**.
//
// **Example 1:**
//
// ```
// Input: s = "ADOBECODEBANC", t = "ABC"
// Output: "BANC"
// Explanation: The minimum window substring "BANC" includes 'A', 'B', and 'C' from string t.
// ```
//
// **Example 2:**
//
// ```
// Input: s = "a", t = "a"
// Output: "a"
// Explanation: The entire string s is the minimum window.
// ```
//
// **Example 3:**
//
// ```
// Input: s = "a", t = "aa"
// Output: ""
// Explanation: Both 'a's from t must be included in the window.
// Since the largest window of s only has one 'a', return empty string.
// ```
//
// **Constraints:**
//
// - `m == s.length`
// - `n == t.length`
// - `1 <= m, n <= 10^5`
// - `s` and `t` consist of uppercase and lowercase English letters.
//
// **Follow up:** Could you find an algorithm that runs in `O(m + n)` time?
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// Use two pointer
class Solution {
 public:
  string minWindow(string s, string t) {
    int n = s.size();
    unordered_map<char, int> tCounter;
    unordered_map<char, int> sCounter;

    // Count chars
    for (auto ch : t) {
      tCounter[ch]++;
    }

    // Compare counter
    auto check = [&]() -> bool {
      for (auto [ch, tCount] : tCounter) {
        if (sCounter[ch] < tCount) {
          return false;
        }
      }
      return true;
    };

    auto ansSize = n + 1;
    auto ansI = 0;
    int i = 0;
    int j = 0;
    while (j <= n) {
      int size = j - i;
      if (check()) {
        if (ansSize > size) {
          ansSize = size;
          ansI = i;
        }
        sCounter[s[i]]--;
        i++;
      } else {
        sCounter[s[j]]++;
        j++;
      }
    }

    if (ansSize == n + 1) {
      return "";
    }
    return s.substr(ansI, ansSize);
  }
};

// Use two pointer
class Solution2 {
 public:
  string minWindow(string s, string t) {
    int n = s.size();

    // Count chars
    vector<int> counter(128);  // remaining char count need
    auto count = 0;            // number of positive count
    for (auto ch : t) {
      counter[ch]++;
    }
    for (auto c : counter) {
      if (c > 0) count++;
    }

    auto ansSize = n + 1;
    auto ansI = 0;
    int i = 0;
    int j = 0;
    while (j <= n) {
      int size = j - i;
      if (count == 0) {
        if (ansSize > size) {
          ansSize = size;
          ansI = i;
        }
        if (counter[s[i]] == 0) count++;
        counter[s[i]]++;
        i++;
      } else {
        counter[s[j]]--;
        if (counter[s[j]] == 0) count--;
        j++;
      }
    }

    if (ansSize == n + 1) {
      return "";
    }
    return s.substr(ansI, ansSize);
  }
};
