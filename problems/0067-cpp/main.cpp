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
  string addBinary(const string &a, const string &b) {
    const int aLen = a.size(), bLen = b.size();

    // Prepare c
    string c;
    c.reserve(max(aLen, bLen) + 1);

    // Add
    int i = aLen - 1;  // a index
    int j = bLen - 1;  // b index
    int carry = 0;
    for (; i >= 0 || j >= 0 || carry > 0; --i, --j) {
      if (i >= 0) carry += (a[i] - '0');
      if (j >= 0) carry += (b[j] - '0');

      c.push_back('0' + carry % 2);
      carry /= 2;
    }

    // Reverse
    reverse(c.begin(), c.end());

    return c;
  }
};
