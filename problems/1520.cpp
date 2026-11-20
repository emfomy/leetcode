// Source: https://leetcode.com/problems/maximum-number-of-non-overlapping-substrings
// Title: Maximum Number of Non-Overlapping Substrings
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a string `s` of lowercase letters, you need to find the maximum number of **non-empty** substrings of `s` that meet the following conditions:
//
// - The substrings do not overlap, that is for any two substrings `s[i..j]` and `s[x..y]`, either `j < x` or `i > y` is true.
// - A substring that contains a certain character `c` must also contain all occurrences of `c`.
//
// Find the maximum number of substrings that meet the above conditions. If there are multiple solutions with the same number of substrings, return the one with minimum total length. It can be shown that there exists a unique solution of minimum total length.
//
// Notice that you can return the substrings in **any** order.
//
// **Example 1:**
//
// ```
// Input: s = "adefaddaccc"
// Output: ["e","f","ccc"]
// **Explanation:**The following are all the possible substrings that meet the conditions:
// [
//  "adefaddaccc"
//  "adefadda",
//  "ef",
//  "e",
//   "f",
//  "ccc",
// ]
// If we choose the first string, we cannot choose anything else and we'd get only 1. If we choose "adefadda", we are left with "ccc" which is the only one that doesn't overlap, thus obtaining 2 substrings. Notice also, that it's not optimal to choose "ef" since it can be split into two. Therefore, the optimal way is to choose ["e","f","ccc"] which gives us 3 substrings. No other solution of the same number of substrings exist.
// ```
//
// **Example 2:**
//
// ```
// Input: s = "abbaccd"
// Output: ["d","bb","cc"]
// **Explanation: **Notice that while the set of substrings ["d","abba","cc"] also has length 3, it's considered incorrect since it has larger total length.
// ```
//
// **Constraints:**
//
// - `1 <= s.length <= 10^5`
// - `s` contains only lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <array>
#include <string>
#include <vector>

using namespace std;

// Greedy + DP
//
// First find the first and the last index of each alphabet.
// Denote as L[x] and R[x].
//
// For each alphabet `c`, find the valid substring start with it.
// The substring range is initialized as [L[c], E[c]],
// where E[c] is the end of the substring, initialized as R[c].
//
// We loop through all the letters `x` in the range, and check the followings:
// If L[x] < L[c], then the substring is invalid (first of x too left).
// If L[c] < L[x] <= R[x] <= E[c], then do nothing (already contained).
// If L[c] < L[x] < E[c] < R[x], then set E[c] = R[x] (extending the substring).
//
// Note that in the loop, E[c] only increase.
// Therefore it won't break the conditions except the fourth one (extending).
// However, the fourth case becomes the third after extending, so we it won't matter.
//
// Next loop through the string,
// and use DP to find the maximum number.
class Solution {
 public:
  vector<string> maxNumOfSubstrings(const string& s) {
    const int n = s.size();

    // Find first and last
    auto firsts = array<int, 128>();
    auto lasts = array<int, 128>();
    fill(firsts.begin(), firsts.end(), n);
    fill(lasts.begin(), lasts.end(), -1);
    for (int i = 0; i < n; ++i) {
      char ch = s[i];
      firsts[ch] = min(firsts[ch], i);
      lasts[ch] = max(lasts[ch], i);
    }

    // Find valid substrings
    auto startOf = vector<char>(n);  // s[i] is start of substr of what alphabet
    auto endOf = vector<char>(n);    // s[i] is end of substr of what alphabet

    auto starts = array<int, 128>();
    auto ends = array<int, 128>();
    for (char ch = 'a'; ch <= 'z'; ++ch) {
      if (firsts[ch] == n) continue;  // not exist

      int start = firsts[ch];
      int end = lasts[ch];
      bool valid = true;
      for (int i = start + 1; i <= end; ++i) {
        char x = s[i];

        // L[x] < L[c]
        if (firsts[x] < start) {
          valid = false;
          break;
        }

        // L[c] < L[x] <= R[x] <= E[c]
        if (lasts[x] <= end) continue;

        // L[c] < L[x] < E[c] < R[x]
        end = lasts[x];
      }

      // Invalid, erase it
      if (valid) {
        starts[ch] = start;
        ends[ch] = end;
        startOf[start] = ch;
        endOf[end] = ch;
      }
    }

    // Loop
    auto cnts = array<int, 128>();
    auto lens = array<int, 128>();
    auto prevs = array<int, 128>();
    char prevCh = 0;
    for (int i = 0; i < n; ++i) {
      // Check start
      if (startOf[i] != '\0') {
        char ch = startOf[i];
        cnts[ch] = cnts[prevCh] + 1;
        lens[ch] = lens[prevCh] + ends[ch] - starts[ch] + 1;
        prevs[ch] = prevCh;
      }

      // Check end
      if (endOf[i] != '\0') {
        char ch = endOf[i];
        if (cnts[ch] > cnts[prevCh] || cnts[ch] == cnts[prevCh] && lens[ch] < lens[prevCh]) {
          prevCh = ch;
        }
      }
    }

    // Construct
    auto ans = vector<string>();
    ans.reserve(26);
    while (prevCh) {
      ans.push_back(s.substr(starts[prevCh], ends[prevCh] - starts[prevCh] + 1));
      prevCh = prevs[prevCh];
    }

    return ans;
  }
};
