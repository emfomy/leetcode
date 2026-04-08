// Source: https://leetcode.com/problems/remove-k-digits
// Title: Remove K Digits
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given string num representing a non-negative integer `num`, and an integer `k`, return the smallest possible integer after removing `k` digits from `num`.
//
// **Example 1:**
//
// ```
// Input: num = "1432219", k = 3
// Output: "1219"
// Explanation: Remove the three digits 4, 3, and 2 to form the new number 1219 which is the smallest.
// ```
//
// **Example 2:**
//
// ```
// Input: num = "10200", k = 1
// Output: "200"
// Explanation: Remove the leading 1 and the number is 200. Note that the output must not contain leading zeroes.
// ```
//
// **Example 3:**
//
// ```
// Input: num = "10", k = 2
// Output: "0"
// Explanation: Remove all the digits from the number and it is left with nothing which is 0.
// ```
//
// **Constraints:**
//
// - `1 <= k <= num.length <= 10^5`
// - `num` consists of only digits.
// - `num` does not have any leading zeros except for the zero itself.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <deque>
#include <string>

using namespace std;

// Greedy + Monotonic Stack
//
// The output string tends to be increasing.
//
// We loop from left to right, put the digits into a stack.
// For each new digit, pop the larger top digits if we still have quota (k > 0).
// Each pop decrease k by 1.
//
// After processing all digits, if there is quota left (k > 0), pop from the back.
class Solution {
 public:
  string removeKdigits(const string &num, int k) {
    // Loop
    auto st = deque<char>();
    for (char ch : num) {
      // Pop larger digits
      while (k > 0 && !st.empty() && st.back() > ch) {
        st.pop_back();
        --k;
      }

      // Push
      st.push_back(ch);
    }

    // Still have quota
    while (k > 0 && !st.empty()) {
      st.pop_back();
      --k;
    }

    // Remove leading zeros
    while (!st.empty() && st.front() == '0') {
      st.pop_front();
    }

    // Edge case
    if (st.empty()) return "0";

    // Build answer
    return string(st.cbegin(), st.cend());
  }
};
