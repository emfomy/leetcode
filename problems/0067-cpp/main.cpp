// Source: https://leetcode.com/problems/add-binary
// Title: Add Binary
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given two binary strings `a` and `b`, return their sum as a binary string.
//
// **Example 1:**
//
// ```
// Input: a = "11", b = "1"
// Output: "100"
// ```
//
// **Example 2:**
//
// ```
// Input: a = "1010", b = "1011"
// Output: "10101"
// ```
//
// **Constraints:**
//
// - `1 <= a.length, b.length <= 10^4`
// - `a` and `b` consistonly of `'0'` or `'1'` characters.
// - Each string does not contain leading zeros except for the zero itself.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <string>

using namespace std;

class Solution {
 public:
  string addBinary(string a, string b) {
    int i = a.size(), j = b.size();

    // Add
    string c;
    auto carry = 0;
    while (i > 0 || j > 0) {
      i--;
      j--;
      auto aBit = (i >= 0) ? (a[i] - '0') : 0;
      auto bBit = (j >= 0) ? (b[j] - '0') : 0;
      carry += aBit + bBit;
      c.push_back('0' + carry % 2);
      carry /= 2;
    }
    if (carry) c.push_back('1');

    // Reverse
    reverse(c.begin(), c.end());

    return c;
  }
};
