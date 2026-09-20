// Source: https://leetcode.com/problems/count-commas-in-range
// Title: Count Commas in Range
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer `n`.
//
// Return the **total** number of commas used when writing all integers from `[1, n]` (inclusive) in **standard** number formatting.
//
// In **standard** formatting:
//
// - A comma is inserted after **every three** digits from the right.
// - Numbers with **fewer** than 4 digits contain no commas.
//
// **Example 1:**
//
// ```
// Input: n = 1002
// Output: 3
// Explanation:
// The numbers `"1,000"`, `"1,001"`, and `"1,002"` each contain one comma, giving a total of 3.
// ```
//
// **Example 2:**
//
// ```
// Input: n = 998
// Output: 0
// Explanation:
// All numbers from 1 to 998 have fewer than four digits. Therefore, no commas are used.
// ```
//
// **Constraints:**
//
// - `1 <= n <= 10^5`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>

using namespace std;

// Since n < 1e5, there will be at most 1 comma in each number.
class Solution {
 public:
  int countCommas(int n) {  //
    return max(n - 999, 0);
  }
};
