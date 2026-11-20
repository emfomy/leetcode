// Source: https://leetcode.com/problems/find-k-length-substrings-with-no-repeated-characters
// Title: Find K-Length Substrings With No Repeated Characters
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a string `s` and an integer `k`, return the number of substrings in `s` of length `k` with no repeated characters.
//
// **Example 1:**
//
// ```
// Input: s = "havefunonleetcode", k = 5
// Output: 6
// Explanation: There are 6 substrings they are: 'havef','avefu','vefun','efuno','etcod','tcode'.
// ```
//
// **Example 2:**
//
// ```
// Input: s = "home", k = 5
// Output: 0
// Explanation: Notice k can be larger than the length of s. In this case, it is not possible to find any substring.
// ```
//
// **Constraints:**
//
// - `1 <= s.length <= 10^4`
// - `s` consists of lowercase English letters.
// - `1 <= k <= 10^4`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>

using namespace std;

// Sliding window
class Solution {
 public:
  int numKLenSubstrNoRepeats(string s, int k) {
    int n = s.size();
    if (k > n) return 0;

    auto freq = vector<int>(128);  // count of letters in the window
    auto dupCount = 0;             // number of duplicated letters

    // Loop
    auto ans = 0;
    for (auto i = 0; i < n; ++i) {
      auto ch = s[i];
      dupCount += (freq[ch] == 1);
      ++freq[ch];

      if (i + 1 >= k) {
        ans += (dupCount == 0);

        auto ch = s[i - k + 1];
        --freq[ch];
        dupCount -= (freq[ch] == 1);
      }
    }

    return ans;
  }
};

// Two Pointer
//
// Keep [l, r] without duplicated letters.
// The number of substring in [l, r] with length k is (l-r-k+2)
class Solution2 {
 public:
  int numKLenSubstrNoRepeats(string s, int k) {
    int n = s.size();
    if (k > n) return 0;

    // Loop
    auto freq = vector<bool>(128);  // count of letters in the window
    auto ans = 0;
    for (auto r = 0, l = 0; r < n; ++r) {
      auto ch = s[r];
      while (freq[ch] && l <= r) freq[s[l++]] = false;
      freq[ch] = true;
      ans += (r - l + 1 >= k);
    }

    return ans;
  }
};
