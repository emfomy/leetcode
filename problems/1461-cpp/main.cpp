// Source: https://leetcode.com/problems/check-if-a-string-contains-all-binary-codes-of-size-k
// Title: Check If a String Contains All Binary Codes of Size K
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a binary string `s` and an integer `k`, return `true` if every binary code of length `k` is a substring of `s`. Otherwise, return `false`.
//
// **Example 1:**
//
// ```
// Input: s = "00110110", k = 2
// Output: true
// Explanation: The binary codes of length 2 are "00", "01", "10" and "11". They can be all found as substrings at indices 0, 1, 3 and 2 respectively.
// ```
//
// **Example 2:**
//
// ```
// Input: s = "0110", k = 1
// Output: true
// Explanation: The binary codes of length 1 are "0" and "1", it is clear that both exist as a substring.
// ```
//
// **Example 3:**
//
// ```
// Input: s = "0110", k = 2
// Output: false
// Explanation: The binary code "00" is of length 2 and does not exist in the array.
// ```
//
// **Constraints:**
//
// - `1 <= s.length <= 5 * 10^5`
// - `s[i]` is either `'0'` or `'1'`.
// - `1 <= k <= 20`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

using namespace std;

// Slicing Window
class Solution {
 public:
  bool hasAllCodes(const string &s, int k) {
    // Guard, invalid k
    if (k < 0 || k >= 32) return false;

    // Sizes
    const int n = s.size();
    const unsigned int totalRequired = 1u << k;
    const unsigned int mask = totalRequired - 1;

    // Guard, string too short
    if (n < totalRequired + k - 1) return false;

    // Loop
    auto seen = vector<bool>(1 << k);
    int seenCount = 0;
    unsigned int code = 0u;
    for (int i = 0; i < n; ++i) {
      code = ((code << 1) & mask) | (s[i] - '0');
      if (i >= k - 1 && !seen[code]) {
        seen[code] = true;
        if (++seenCount == totalRequired) return true;
      }
    }

    return false;
  }
};
