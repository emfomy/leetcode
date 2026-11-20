// Source: https://leetcode.com/problems/gcd-of-odd-and-even-sums
// Title: GCD of Odd and Even Sums
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer `n`. Your task is to compute the **GCD** (greatest common divisor) of two values:
//
// - `sumOdd`: the sum of the smallest`n`positive odd numbers.
// - `sumEven`: the sum of the smallest`n`positive even numbers.
//
// Return the GCD of `sumOdd` and `sumEven`.
//
// **Example 1:**
//
// ```
// Input: n = 4
// Output: 4
// Explanation:
// - Sum of the first 4 odd numbers `sumOdd = 1 + 3 + 5 + 7 = 16`
// - Sum of the first 4 even numbers `sumEven = 2 + 4 + 6 + 8 = 20`
// Hence, `GCD(sumOdd, sumEven) = GCD(16, 20) = 4`.
// ```
//
// **Example 2:**
//
// ```
// Input: n = 5
// Output: 5
// Explanation:
// - Sum of the first 5 odd numbers `sumOdd = 1 + 3 + 5 + 7 + 9 = 25`
// - Sum of the first 5 even numbers `sumEven = 2 + 4 + 6 + 8 + 10 = 30`
// Hence, `GCD(sumOdd, sumEven) = GCD(25, 30) = 5`.
// ```
//
// **Constraints:**
//
// - `1 <= n <= 1000`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace std;

// Sum of the first n odd numbers are n^2.
// Sum of the first n even numbers are n(n+1).
// GCD(n^2, n(n+1)) = n * GCD(n, n+1) = n.
class Solution {
 public:
  int gcdOfOddEvenSums(int n) { return n; }
};
