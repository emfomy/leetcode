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
// **Input:** n = 1, k = 3
// **Output:** "c"
// **Explanation:** The list ["a", "b", "c"] contains all happy strings of length 1. The third string is "c".
// ```
//
// **Example 2:**
//
// ```
// **Input:** n = 1, k = 4
// **Output:** ""
// **Explanation:** There are only 3 happy strings of length 1.
// ```
//
// **Example 3:**
//
// ```
// **Input:** n = 3, k = 9
// **Output:** "cab"
// **Explanation:** There are 12 different happy string of length 3 ["aba", "abc", "aca", "acb", "bab", "bac", "bca", "bcb", "cab", "cac", "cba", "cbc"]. You will find the 9^th string = "cab"
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

// The first letter has 3 cases. Each of the other letter only has 2 cases.
//
// Here we use 0-based index.
//
// There are 3 * 2^(n-1) happy strings with length n.
// If k < 2^(n-1), then the first letter is a (and so on).
// That is, the first letter must be 'a' + floor(k / (2^n-1)).
// We can use the same idea to find each letter.
class Solution {
 public:
  string getHappyString(int n, int k) {
    int m = (1 << (n - 1));               // 2^(n-1), the number of happy string start with a.
    if (k < 0 || k > (3 * m)) return "";  // invalid

    // Reserve the answer string
    string ans;
    ans.reserve(n);

    --k;  // covert to 0-based index.

    // Check first letter
    ans.push_back(k / m + 'a');
    k %= m;
    m /= 2;

    // Check other letters
    char nextLetterMap[3][2] = {
        {'b', 'c'},  // a
        {'a', 'c'},  // b
        {'a', 'b'},  // c
    };
    for (int i = 1; i < n; ++i) {
      int nextId = k / m;
      char nextChar = nextLetterMap[ans.back() - 'a'][nextId];
      ans.push_back(nextChar);
      k %= m;
      m /= 2;
    }

    return ans;
  }
};
