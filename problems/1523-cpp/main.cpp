// Source: htthttps://leetcode.com/problems/count-odd-numbers-in-an-interval-range
// Title: Count Odd Numbers in an Interval Range
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given two non-negative integers `low` and `high`. Return the count of odd numbers between `low` and `high`(inclusive).
//
// **Example 1:**
//
// ```
// Input: low = 3, high = 7
// Output: 3
// Explanation: The odd numbers between 3 and 7 are [3,5,7].
// ```
//
// **Example 2:**
//
// ```
// Input: low = 8, high = 10
// Output: 1
// Explanation: The odd numbers between 8 and 10 are [9].
// ```
//
// **Constraints:**
//
// - `0 <= low <= high<= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace std;

// Low odd  & high odd,  ans = (high - low)/2 + 1
// Low odd  & high even, ans = (high - low)/2 + 1
// Low even & high odd,  ans = (high - low)/2 + 1
// Low even & even even, ans = (high - low)/2
class Solution {
 public:
  int countOdds(int low, int high) {  //
    return (high - low) / 2 + ((low % 2) || (high % 2));
  }
};
