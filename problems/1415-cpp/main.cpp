// Source: https://leetcode.com/problems/the-k-th-lexicographical-string-of-all-happy-strings-of-length-n
// Title: The k-th Lexicographical String of All Happy Strings of Length n
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// A **happy string** is a string that:
//
// - consists only of letters of the set `['a', 'b', 'c']`.
// - `s[i] != s[i + 1]` for all values of `i` from `1` to `s.length - 1` (string is 1-indexed).
//
// For example, strings **"abc", "ac", "b"** and **"abcbabcbcb"** are all happy strings and strings **"aa", "baa"** and **"ababbc"** are not happy strings.
//
// Given two integers `n` and `k`, consider a list of all happy strings of length `n` sorted in lexicographical order.
//
// Return the kth string of this list or return an **empty string** if there are less than `k` happy strings of length `n`.
//
// **Example 1:**
//
// ```
// Input: n = 1, k = 3
// Output: "c"
// Explanation: The list ["a", "b", "c"] contains all happy strings of length 1. The third string is "c".
// ```
//
// **Example 2:**
//
// ```
// Input: n = 1, k = 4
// Output: ""
// Explanation: There are only 3 happy strings of length 1.
// ```
//
// **Example 3:**
//
// ```
// Input: n = 3, k = 9
// Output: "cab"
// Explanation: There are 12 different happy string of length 3 ["aba", "abc", "aca", "acb", "bab", "bac", "bca", "bcb", "cab", "cac", "cba", "cbc"]. You will find the 9^th string = "cab"
// ```
//
// **Constraints:**
//
// - `1 <= n <= 10`
// - `1 <= k <= 100`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <string>

using namespace std;

// There are total 3*2^(n-1) happy string with length n.
// First 1/3 starts with a, middle 1/3 starts with b, last 1/3 starts with c.
// We can use the same idea to find each letter.
class Solution {
  // char map
  constexpr static char nextCharMap[3][2] = {
      {'b', 'c'},  // a
      {'a', 'c'},  // b
      {'a', 'b'},  // c
  };

 public:
  string getHappyString(int n, int k) {
    int m = 1 << (n - 1);

    --k;  // convert to zero-based index
    if (k < 0 || k >= 3 * m) return "";

    // Prepare answer
    string ans;
    ans.reserve(n);

    // First letter
    ans.push_back('a' + k / m);
    k %= m;
    m /= 2;

    // Other letters
    for (int i = 1; i < n; ++i) {
      ans.push_back(nextCharMap[ans.back() - 'a'][k / m]);
      k %= m;
      m /= 2;
    }

    return ans;
  }
};
