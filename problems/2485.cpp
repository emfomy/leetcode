// Source: https://leetcode.com/problems/find-the-pivot-integer
// Title: Find the Pivot Integer
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a positive integer `n`, find the **pivot integer** `x` such that:
//
// - The sum of all elements between `1` and `x` inclusively equals the sum of all elements between `x` and `n` inclusively.
//
// Return the pivot integer `x`. If no such integer exists, return `-1`. It is guaranteed that there will be at most one pivot index for the given input.
//
// **Example 1:**
//
// ```
// Input: n = 8
// Output: 6
// Explanation: 6 is the pivot integer since: 1 + 2 + 3 + 4 + 5 + 6 = 6 + 7 + 8 = 21.
// ```
//
// **Example 2:**
//
// ```
// Input: n = 1
// Output: 1
// Explanation: 1 is the pivot integer since: 1 = 1.
// ```
//
// **Example 3:**
//
// ```
// Input: n = 4
// Output: -1
// Explanation: It can be proved that no such integer exist.
// ```
//
// **Constraints:**
//
// - `1 <= n <= 1000`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cmath>
using namespace std;

// Math
//
// sum([1, x]) = sum([x, n])
// x(x+1)/2 = (n-x+1)(x+n)/2
// x^2+x = -x^2 + x + n(n+1)
// x^2 = n(n+1)/2
class Solution {
 public:
  int pivotInteger(int n) {
    int m = n * (n + 1) / 2;
    int x = static_cast<int>(sqrt(static_cast<double>(m)));

    if (x * x == m) return x;  // check
    if ((x - 1) * (x - 1) == m) return x - 1;
    if ((x + 1) * (x + 1) == m) return x + 1;

    return -1;
  }
};

// Math, Pell's equation
//
// Pell's equation: X^2-NY^2 = 1
// The trivial solution is (X0, Y0) = (1, 0).
// We can generate solutions (Xi, Yi) as
// X{i+1} = X1 Xi + N Y1 Yi
// Y{i+1} = X1 Yi + y1 Xi
//
// In this problem, we have x^2 = n(n+1)/2
// Let X = 2n+1, Y^2 = x^2 = n(n+1)/2
// X^2 - 8Y^2 = 1 (N=8)
//
// The solutions are:
// (X, Y) =    1,    0; (n, x) =    0,    0
// (X, Y) =    3,    1; (n, x) =    1,    1
// (X, Y) =   17,    6; (n, x) =    8,    6
// (X, Y) =   99,   35; (n, x) =   49,   35
// (X, Y) =  577,  204; (n, x) =  288,  204
// (X, Y) = 3363, 1156; (n, x) = 1681, 1156 // out of range
//
//
class Solution2 {
 public:
  int pivotInteger(int n) {
    switch (n) {
      case 1:
        return 1;
      case 8:
        return 6;
      case 49:
        return 35;
      case 288:
        return 204;
      default:
        return -1;
    }
  }
};
