// Source: https://leetcode.com/problems/ugly-number
// Title: Ugly Number
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// An **ugly number** is a positive integer which does not have a prime factor other than 2, 3, and 5.
//
// Given an integer `n`, return `true` if `n` is an **ugly number**.
//
// **Example 1:**
//
// ```
// Input: n = 6
// Output: true
// Explanation: 6 = 2 × 3
// ```
//
// **Example 2:**
//
// ```
// Input: n = 1
// Output: true
// Explanation: 1 has no prime factors.
// ```
//
// **Example 3:**
//
// ```
// Input: n = 14
// Output: false
// Explanation: 14 is not ugly since it includes the prime factor 7.
// ```
//
// **Constraints:**
//
// - `-2^31 <= n <= 2^31 - 1`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace std;

class Solution {
 public:
  bool isUgly(int n) {
    if (n <= 0) return false;
    while (n > 1 && n % 2 == 0) n /= 2;
    while (n > 1 && n % 3 == 0) n /= 3;
    while (n > 1 && n % 5 == 0) n /= 5;
    return n == 1;
  }
};
