// Source: https://leetcode.com/problems/check-if-binary-string-has-at-most-one-segment-of-ones
// Title: Check if Binary String Has at Most One Segment of Ones
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a binary string `s` **without leading zeros**, return `true` if `s` contains **at most one contiguous segment of ones**. Otherwise, return `false`.
//
// **Example 1:**
//
// ```
// Input: s = "1001"
// Output: false
// Explanation: The ones do not form a contiguous segment.
// ```
//
// **Example 2:**
//
// ```
// Input: s = "110"
// Output: true```
//
// **Constraints:**
//
// - `1 <= s.length <= 100`
// - `s[i]` is either `'0'` or `'1'`.
// - `s[0]` is`'1'`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <string>

using namespace std;

class Solution {
 public:
  bool checkOnesSegment(const string &s) {
    const int n = s.size();

    // Find end of first segment
    auto it0 = find(s.cbegin(), s.cend(), '0');
    if (it0 == s.cend()) return true;  // all ones

    // Find next one
    auto it1 = find(it0, s.cend(), '1');
    return it1 == s.cend();  // should not has another one
  }
};

// Find any 0 before 1
class Solution2 {
 public:
  bool checkOnesSegment(const string &s) {  //
    return s.find("01") == string::npos;
  }
};
