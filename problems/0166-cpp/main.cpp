// Source: https://leetcode.com/problems/fraction-to-recurring-decimal
// Title: Fraction to Recurring Decimal
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given two integers representing the `numerator` and `denominator` of a fraction, return the fraction in string format.
//
// If the fractional part is repeating, enclose the repeating part in parentheses.
//
// If multiple answers are possible, return **any of them**.
//
// It is **guaranteed** that the length of the answer string is less than `10^4` for all the given inputs.
//
// **Example 1:**
//
// ```
// Input: numerator = 1, denominator = 2
// Output: "0.5"
// ```
//
// **Example 2:**
//
// ```
// Input: numerator = 2, denominator = 1
// Output: "2"
// ```
//
// **Example 3:**
//
// ```
// Input: numerator = 4, denominator = 333
// Output: "0.(012)"
// ```
//
// **Constraints:**
//
// - `-2^31 <=numerator, denominator <= 2^31 - 1`
// - `denominator != 0`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <sstream>
#include <unordered_map>

using namespace std;

// Use long division
class Solution {
 public:
  string fractionToDecimal(int64_t numerator, int64_t denominator) {
    ostringstream oss;

    // Ensure denom > 0
    if (denominator < 0) {
      numerator = -numerator;
      denominator = -denominator;
    }

    // Ensure denom > 0
    if (numerator < 0) {
      oss << "-";
      numerator = -numerator;
    }

    // Integer part
    oss << (numerator / denominator);
    numerator %= denominator;

    // Fraction part
    if (numerator != 0) {
      oss << ".";
      auto seen = unordered_map<int64_t, int>();  // seen numerator -> index
      string fraction;
      for (auto index = 0; numerator > 0; ++index) {
        if (seen.count(numerator)) break;
        seen[numerator] = index;
        auto quotient = (10 * numerator) / denominator;
        auto reminder = (10 * numerator) % denominator;
        fraction += ('0' + quotient);
        numerator = reminder;
      }
      if (numerator > 0) {
        auto index = seen[numerator];
        oss << fraction.substr(0, index) << "(" << fraction.substr(index) << ")";
      } else {
        oss << fraction;
      }
    }

    return oss.str();
  }
};
