// Source: https://leetcode.com/problems/sequential-digits
// Title: Sequential Digits
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// An integer has sequential digits if and only if each digit in the number is one more than the previous digit.
//
// Return a **sorted** list of all the integersin the range `[low, high]`inclusive that have sequential digits.
//
// **Example 1:**
//
// ```
// Input: low = 100, high = 300
// Output: [123,234]
// ```
//
// **Example 2:**
//
// ```
// Input: low = 1000, high = 13000
// Output: [1234,2345,3456,4567,5678,6789,12345]
// ```
//
// **Constraints:**
//
// - `10 <= low <= high <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

using namespace std;

// Binary Search
//
// Pregenerate all the numbers, and use binary search to find the range.
//
// 8 numbers with 2 digits: 12, 23, ..., 89
// 7 numbers with 3 digits: 123, 234, ..., 789
// ...
// 2 numbers with 8 digits: 12345678, 23456789
// 1 number  with 9 digits: 123456789
class Solution {
  static inline const vector<int> nums = {
      12,        23,       34,      45,     56,    67,   78,  89,  //
      123,       234,      345,     456,    567,   678,  789,      //
      1234,      2345,     3456,    4567,   5678,  6789,           //
      12345,     23456,    34567,   45678,  56789,                 //
      123456,    234567,   345678,  456789,                        //
      1234567,   2345678,  3456789,                                //
      12345678,  23456789,                                         //
      123456789,                                                   //
  };

 public:
  vector<int> sequentialDigits(int low, int high) {
    auto lowIt = lower_bound(nums.cbegin(), nums.cend(), low);
    auto highIt = upper_bound(nums.cbegin(), nums.cend(), high);
    return vector<int>(lowIt, highIt);
  }
};
