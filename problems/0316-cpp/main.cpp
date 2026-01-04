// Source: https://leetcode.com/problems/remove-duplicate-letters
// Title: Remove Duplicate Letters
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a string `s`, remove duplicate letters so that every letter appears once and only once. You must make sure your result is **the smallest in lexicographical order** among all possible results.
//
// **Example 1:**
//
// ```
// Input: s = "bcabc"
// Output: "abc"
// ```
//
// **Example 2:**
//
// ```
// Input: s = "cbacdcbc"
// Output: "acdb"
// ```
//
// **Constraints:**
//
// - `1 <= s.length <= 10^4`
// - `s` consists of lowercase English letters.
//
// **Note:** This question is the same as 1081: https://leetcode.com/problems/smallest-subsequence-of-distinct-characters
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>

using namespace std;

// Greedy + Stack
//
// For each step, try to put the current char into the stack.
// If it already in the stack, then skip it.
// It it is smaller then the top one, try to pop the top one.
// However, we only pop the top one if there is another same alphabet to the right.
class Solution {
 public:
  string removeDuplicateLetters(string s) {
    int n = s.size();

    // Find frequency
    auto count = vector<int>(128);
    for (auto ch : s) ++count[ch];

    // Loop
    auto ans = ""s;  // stack
    auto seen = vector<bool>(128);
    for (auto ch : s) {
      --count[ch];

      if (seen[ch]) continue;

      while (!ans.empty() && ans.back() > ch && count[ans.back()]) {
        seen[ans.back()] = false;
        ans.pop_back();
      }

      seen[ch] = true;
      ans.push_back(ch);
    }

    return ans;
  }
};
