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
#include <cstdint>
#include <numbers>
#include <tuple>

using namespace std;

// DP
//
// Let DP[i] be the number of ways to climb to layer i.
// DP[0] = 1.
// DP[1] = 1.
// DP[i+2] = DP[i+1] + DP[i].
class Solution {
 public:
  int climbStairs(int n) {
    int prev = 1, curr = 1;
    for (int i = 2; i <= n; ++i) {
      tie(curr, prev) = tuple(curr + prev, curr);
    }
    return curr;
  }
};

// Math, Matrix Form, Fast Power
//
// Let F(i) be the i-th step
// F(-1) = 0 F(0) = F(1) = 1; F(i) = F(i-1) + F(i-2).
//
// Write in matrix form.
// [F(i)  ] = [1 1] [F(i-1)]
// [F(i-1)]   [1 0] [F(i-2)]
//
// Let V(i) = [F(i)  F(i-1)]^T, A = [[1, 1], [1, 0]]
// V(0) = [1 0]^T
// V(i) = A * V(i-1) = A^i V(0)
//                   = A^i[:, 0] (since V(0) is [1, 0]^T).
// Therefire, F(i) = V(i)[0] = A^i[0, 0].
//
// We can use fast power to compute A^(i-1).
class Solution2 {
  struct Mat {
    int a, b, c;  // [[a, b], [b, c]]
  };

  Mat matmat(const Mat &m1, const Mat &m2) {  //
    return {
        m1.a * m2.a + m1.b * m2.b,  //
        m1.a * m2.b + m1.b * m2.c,  //
        m1.b * m2.b + m1.c * m2.c   //
    };
  }

  Mat matpow(Mat m, int k) {
    Mat ret{1, 0, 1};
    while (k > 0) {
      if (k & 1) ret = matmat(ret, m);
      k >>= 1;
      if (k > 0) m = matmat(m, m);
    }
    return ret;
  }

 public:
  int climbStairs(int n) {  //
    return matpow(Mat{1, 1, 0}, n).a;
  }
};

// Math, Generating Function
//
// Let f(i) be the number of ways to climb to layer i.
// f(0) = f(1) = 1; f(i) = f(i-1) + f(i-2).
//
// The generating function is
// G(x) = sum_[i>=0] f(i)x^i
// G(x) = f(0) + f(1)x + sum_[i>=2] (f(i-1), f(i-2))x^i
//      = 1 + x + sum_[i>=1] f(i)x^(i+1) + sum_[i>=0] f(i)x^(i+2)
//      = 1 + x + (G(x)-G(0))x + G(x)x^2
//      = 1 + G(x)x + G(x)x^2
// G(x) = 1 / (1-x-x^2)
//
// Write 1-x-x^2 = (1-phi x)(1-psi x), we have phi = (1+sqrt(5))/2, psi = (1-sqrt(5))/2
// Therefore G(x) = 1/sqrt(5) * (phi/(1-phi x) - psi/(1-psi x))
//
// Note that 1/(1-rx) = sum(r^ix^i), we can rewrite G(x) as
// G(x) = sum_[i>=0] 1/sqrt(5) * (phi^(i+1) - psi^(i+1)) x^i
// That is, f(i) = (phi^(i+1) - psi^(i+1)) / sqrt(5)
//
// Note that it is actually the (n+1)th Fibonacci number.
//
// Since psi < 1 and f(i) is integer, f(i) = round(phi^(i+1)/sqrt(5))
class Solution3 {
  constexpr static double PHI = numbers::phi;
  constexpr static double INV_SQRT5 = 1.0 / (2.0 * numbers::phi - 1.0);

 public:
  int climbStairs(int n) {  //
    return round(pow(PHI, n + 1) * INV_SQRT5);
  }
};
