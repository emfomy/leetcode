// Source: https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string-ii
// Title: Remove All Adjacent Duplicates in String II
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a string `s` and an integer `k`, a `k` **duplicate removal** consists of choosing `k` adjacent and equal letters from `s` and removing them, causing the left and the right side of the deleted substring to concatenate together.
//
// We repeatedly make `k` **duplicate removals** on `s` until we no longer can.
//
// Return the final string after all such duplicate removals have been made. It is guaranteed that the answer is **unique**.
//
// **Example 1:**
//
// ```
// Input: s = "abcd", k = 2
// Output: "abcd"
// Explanation: There's nothing to delete.```
//
// **Example 2:**
//
// ```
// Input: s = "deeedbbcccbdaa", k = 3
// Output: "aa"
// **Explanation:
// **First delete "eee" and "ccc", get "ddbbbdaa"
// Then delete "bbb", get "dddaa"
// Finally delete "ddd", get "aa"```
//
// **Example 3:**
//
// ```
// Input: s = "pbbcggttciiippooaais", k = 2
// Output: "ps"
// ```
//
// **Constraints:**
//
// - `1 <= s.length <= 10^5`
// - `2 <= k <= 10^4`
// - `s` only contains lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <utility>
#include <vector>

using namespace std;

// Stack
//
// Store the letter and its duplicate counts.
class Solution {
 public:
  string removeDuplicates(const string &s, const int k) {
    const int n = s.size();
    if (k == 1) return "";
    if (k > n) return s;

    // Loop
    auto st = vector<pair<char, int>>();
    st.reserve(n);
    for (char ch : s) {
      if (st.empty() || st.back().first != ch) {
        st.emplace_back(ch, 1);
      } else {
        if (++st.back().second == k) {
          st.pop_back();
        }
      }
    }

    // Answer
    string ans;
    ans.reserve(n);
    for (auto [ch, cnt] : st) {
      ans.append(cnt, ch);
    }

    return ans;
  }
};
