// Source: https://leetcode.com/problems/check-if-digits-are-equal-in-string-after-operations-i
// Title: Check If Digits Are Equal in String After Operations I
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a string `s` consisting of digits. Perform the following operation repeatedly until the string has **exactly** two digits:
//
// - For each pair of consecutive digits in `s`, starting from the first digit, calculate a new digit as the sum of the two digits **modulo** 10.
// - Replace `s` with the sequence of newly calculated digits, maintaining the order in which they are computed.
//
// Return `true` if the final two digits in `s` are the **same**; otherwise, return `false`.
//
// **Example 1:**
//
// ```
// Input: s = "3902"
// Output: true
// Explanation:
// - Initially, `s = "3902"`
// - First operation:
// - `(s[0] + s[1]) % 10 = (3 + 9) % 10 = 2`
// - `(s[1] + s[2]) % 10 = (9 + 0) % 10 = 9`
// - `(s[2] + s[3]) % 10 = (0 + 2) % 10 = 2`
// - `s` becomes `"292"`
// - Second operation:
// - `(s[0] + s[1]) % 10 = (2 + 9) % 10 = 1`
// - `(s[1] + s[2]) % 10 = (9 + 2) % 10 = 1`
// - `s` becomes `"11"`
// - Since the digits in `"11"` are the same, the output is `true`.
// ```
//
// **Example 2:**
//
// ```
// Input: s = "34789"
// Output: false
// Explanation:
// - Initially, `s = "34789"`.
// - After the first operation, `s = "7157"`.
// - After the second operation, `s = "862"`.
// - After the third operation, `s = "48"`.
// - Since `'4' != '8'`, the output is `false`.
// ```
//
// **Constraints:**
//
// - `3 <= s.length <= 100`
// - `s` consists of only digits.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// Simulation
class Solution {
 public:
  bool hasSameDigits(string s) {
    int n = s.size();
    auto data = vector<int>();
    for (auto ch : s) {
      data.push_back(ch - '0');
    }

    for (auto i = n - 1; i > 1; --i) {
      for (auto j = 0; j < i; ++j) {
        data[j] = (data[j] + data[j + 1]) % 10;
      }
    }

    return data[0] == data[1];
  }
};

// Math
//
// Precompute binomial coefficient
class Solution2 {
 public:
  bool hasSameDigits(string s) {
    static auto binom = makeBinom(100);

    int n = s.size();

    auto left = 0, right = 0;
    for (auto i = 0; i < n - 1; ++i) {
      left += binom[n - 2][i] * (s[i] - '0');
      right += binom[n - 2][i] * (s[i + 1] - '0');
    }

    return (left % 10) == (right % 10);
  }

 private:
  vector<vector<int>> makeBinom(int n) {
    auto binom = vector<vector<int>>(n);
    binom[0] = {1};
    for (auto i = 1; i < n; ++i) {
      binom[i].resize(i + 1);
      binom[i][0] = binom[i - 1][0];
      binom[i][i] = binom[i - 1][i - 1];
      for (auto j = 1; j < i; ++j) {
        binom[i][j] = (binom[i - 1][j - 1] + binom[i - 1][j]) % 10;
      }
    }

    return binom;
  }
};

// Math
//
// Using Lucas's theorem
class Solution3 {
 public:
  bool hasSameDigits(string s) {
    int n = s.size();

    auto left = 0, right = 0;
    for (auto i = 0; i < n - 1; ++i) {
      auto coeff = binom10(n - 2, i);
      left += coeff * (s[i] - '0');
      right += coeff * (s[i + 1] - '0');
    }

    return (left % 10) == (right % 10);
  }

 private:
  inline int binom10(int m, int n) {  //
    auto c2 = binom2(m, n), c5 = binom5(m, n);
    return (5 * c2 + 6 * c5) % 10;
  }

  inline int binom2(int m, int n) {  //
    return (~m & n) == 0;
  }

  inline int binom5(int m, int n) {
    static constexpr int C5[5][5] = {{1, 0, 0, 0, 0}, {1, 1, 0, 0, 0}, {1, 2, 1, 0, 0}, {1, 3, 3, 1, 0}, {1, 4, 1, 4, 1}};

    auto res = 1;
    while (res && (m > 0 || n > 0)) {  // also break if res is zero
      auto mi = m % 5, ni = n % 5;
      res = (res * C5[mi][ni]) % 5;
      m /= 5, n /= 5;
    }

    return res;
  }
};
