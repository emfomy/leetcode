// Source: https://leetcode.com/problems/climbing-stairs
// Title: Climbing Stairs
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are climbing a staircase. It takes `n` steps to reach the top.
//
// Each time you can either climb `1` or `2` steps. In how many distinct ways can you climb to the top?
//
// **Example 1:**
//
// ```
// Input: n = 2
// Output: 2
// Explanation: There are two ways to climb to the top.
// 1. 1 step + 1 step
// 2. 2 steps
// ```
//
// **Example 2:**
//
// ```
// Input: n = 3
// Output: 3
// Explanation: There are three ways to climb to the top.
// 1. 1 step + 1 step + 1 step
// 2. 1 step + 2 steps
// 3. 2 steps + 1 step
// ```
//
// **Constraints:**
//
// - `1 <= n <= 45`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cmath>
#include <numbers>

using namespace std;

// Let S(n) be the number of the ways
// S(1) = 1, S(2) = 2
// For step n, we may
// - Do an 1 step, and then have S(n-1) ways to reach the target;
// - Do a two steps, and then have S(n-2) ways to reach the target.
// Therefore, S(n) = S(n-1) + S(n-2), i.e. the (n+1)th Fibonacci number
class Solution {
 public:
  int climbStairs(int n) {
    auto invSqrt5 = sqrt(0.2);
    auto ans = pow(numbers::phi, n + 1) * invSqrt5;
    return static_cast<int>(round(ans));
  }
};
