// Source: https://leetcode.com/problems/reverse-string
// Title: Reverse String
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Write a function that reverses a string. The input string is given as an array of characters `s`.
//
// You must do this by modifying the input array **in-place** with `O(1)` extra memory.
//
// **Example 1:**
//
// ```
// Input: s = ["h","e","l","l","o"]
// Output: ["o","l","l","e","h"]
// ```
//
// **Example 2:**
//
// ```
// Input: s = ["H","a","n","n","a","h"]
// Output: ["h","a","n","n","a","H"]
// ```
//
// **Constraints:**
//
// - `1 <= s.length <= 10^5`
// - `s[i]` is a **printable ascii character**.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

using namespace std;

// Built-in
class Solution {
 public:
  void reverseString(vector<char>& s) { reverse(s.begin(), s.end()); }
};

// Two pointer
class Solution2 {
 public:
  void reverseString(vector<char>& s) {
    int n = s.size();
    auto l = 0, r = n - 1;
    while (l < r) {
      swap(s[l], s[r]);
      ++l, --r;
    }
  }
};
