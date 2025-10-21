// Source: https://leetcode.com/problems/multiply-strings
// Title: Multiply Strings
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given two non-negative integers `num1` and `num2` represented as strings, return the product of `num1` and `num2`, also represented as a string.
//
// **Note:** You must not use any built-in BigInteger library or convert the inputs to integer directly.
//
// **Example 1:**
//
// ```
// Input: num1 = "2", num2 = "3"
// Output: "6"
// ```
//
// **Example 2:**
//
// ```
// Input: num1 = "123", num2 = "456"
// Output: "56088"
// ```
//
// **Constraints:**
//
// - `1 <= num1.length, num2.length <= 200`
// - `num1` and `num2` consist of digits only.
// - Both `num1` and `num2`do not contain any leading zero, except the number `0` itself.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>

using namespace std;

// Multiplication
//
// Say num1 has m digits. num2 has n digits.
// The maximum numbers are (10^m-1) and (10^n-1)
// The product are smaller than 10^m * 10^n = 10^(m+n), which has (m+n) digits.
class Solution {
 public:
  string multiply(string num1, string num2) {
    if (num1 == "0" || num2 == "0") return "0";

    int m = num1.size(), n = num2.size();

    // Multiply
    auto digits = vector<int>(m + n + 1);
    for (auto i = 0; i < m; ++i) {
      int d1 = num1[m - i - 1] - '0';
      for (auto j = 0; j < n; ++j) {
        int d2 = num2[n - j - 1] - '0';
        digits[i + j] += d1 * d2;
      }
    }

    // Shift
    for (auto i = 0; i < m + n; ++i) {
      digits[i + 1] += digits[i] / 10;
      digits[i] %= 10;
    }

    // Remove leading zeros
    while (digits.back() == 0) digits.pop_back();

    // Convert to string
    for (auto &digit : digits) digit += '0';
    return string(digits.crbegin(), digits.crend());
  }
};
