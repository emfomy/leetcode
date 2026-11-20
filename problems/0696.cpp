// Source: https://leetcode.com/problems/count-binary-substrings
// Title: Count Binary Substrings
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a binary string `s`, return the number of non-empty substrings that have the same number of `0`'s and `1`'s, and all the `0`'s and all the `1`'s in these substrings are grouped consecutively.
//
// Substrings that occur multiple times are counted the number of times they occur.
//
// **Example 1:**
//
// ```
// Input: s = "00110011"
// Output: 6
// Explanation: There are 6 substrings that have equal number of consecutive 1's and 0's: "0011", "01", "1100", "10", "0011", and "01".
// Notice that some of these substrings repeat and are counted the number of times they occur.
// Also, "00110011" is not a valid substring because all the 0's (and 1's) are not grouped together.
// ```
//
// **Example 2:**
//
// ```
// Input: s = "10101"
// Output: 4
// Explanation: There are 4 substrings: "10", "01", "10", "01" that have equal number of consecutive 1's and 0's.
// ```
//
// **Constraints:**
//
// - `1 <= s.length <= 10^5`
// - `s[i]` is either `'0'` or `'1'`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <string>

using namespace std;

// Compute the size of 0-groups and 1-groups.
// For any two consecutive 0-group and 1-group (say with size a and b),
// we can form substrings using one 0&1, two 0&1, ..., min(a, b) 0&1;
// that is, min(a, b) substrings.
class Solution {
 public:
  int countBinarySubstrings(const string &s) {
    char currCh = '\0';
    int currSize = 0, prevSize = 0;

    int ans = 0;
    for (char ch : s) {
      if (ch != currCh) {
        ans += min(currSize, prevSize);
        currCh = ch;
        prevSize = currSize;
        currSize = 0;
      }
      ++currSize;
    }
    ans += min(currSize, prevSize);

    return ans;
  }
};
