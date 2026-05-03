// Source: https://leetcode.com/problems/rotated-digits
// Title: Rotated Digits
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// An integer `x` is a **good** if after rotating each digit individually by 180 degrees, we get a valid number that is different from `x`. Each digit must be rotated - we cannot choose to leave it alone.
//
// A number is valid if each digit remains a digit after rotation. For example:
//
// - `0`, `1`, and `8` rotate to themselves,
// - `2` and `5` rotate to each other (in this case they are rotated in a different direction, in other words, `2` or `5` gets mirrored),
// - `6` and `9` rotate to each other, and
// - the rest of the numbers do not rotate to any other number and become invalid.
//
// Given an integer `n`, return the number of **good** integers in the range `[1, n]`.
//
// **Example 1:**
//
// ```
// Input: n = 10
// Output: 4
// Explanation: There are four good numbers in the range [1, 10] : 2, 5, 6, 9.
// Note that 1 and 10 are not good numbers, since they remain unchanged after rotating.
// ```
//
// **Example 2:**
//
// ```
// Input: n = 1
// Output: 0
// ```
//
// **Example 3:**
//
// ```
// Input: n = 2
// Output: 1
// ```
//
// **Constraints:**
//
// - `1 <= n <= 10^4`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace std;

// Brute-Force
//
// There are 3 kind of digits:
// A: 0, 1, 8 rotate to themselves.
// B: 2, 5, 6, 9, rotate to each other.
// C: 3, 4, 7 are bad.
class Solution {
  bool isGood(int x) {
    bool hasB = false;
    while (x > 0) {
      int d = x % 10;  // last digit
      if (d == 3 || d == 4 || d == 7) return false;
      if (d == 2 || d == 5 || d == 6 || d == 9) hasB = true;
      x /= 10;
    }
    return hasB;
  }

 public:
  int rotatedDigits(int n) {
    int count = 0;
    for (int i = 1; i <= n; ++i) {
      count += isGood(i);
    }
    return count;
  }
};

// Recursion
//
// There are 3 kind of digits:
// A: 0, 1, 8 rotate to themselves.
// B: 2, 5, 6, 9, rotate to each other.
// C: 3, 4, 7 are bad.
//
// Denote P(i) be the i-digit-numbers with only A digits.
// Denote Q(i) be the i-digit-numbers with only A & B digits.
// Denote G(i) be the i-digit good numbers.
// P(i) = 3^i, Q(i) = 7^i
// G(i) = Q(i) - P(i).
//
// We loop from the highest digit.
// For example, say n = 54321.
// We increase n by one to make the range closed-open: [0, 54322)
// We first focus on [0, 50000)
// 1XXXX has leading A digit, then XXXX should be good. Total G(i) of them are good.
// 2XXXX has leading B digit, then XXXX can be A or B.  Total Q(i) of them are good.
// Therefore there are 2*G(i) + 1*Q(i) good numbers in [0, 50000). (0, 1 are A; 2 is B, 3, 4 are C).
//
// Now focus on [50000, 54322).
// Since the leading digit is C, all of them are invalid.
//
// If the leading digit is A, say [80000, 84322),
// then the number of good numbers are equal to [0, 4322).
//
// If the leading digit is B, say [20000, 24322),
// then we compute the numbers without C in [0, 4322).
class Solution2 {
  constexpr static int tens[] = {1, 10, 10 * 10, 10 * 10 * 10, 10 * 10 * 10 * 10};
  constexpr static int ps[] = {1, 3, 3 * 3, 3 * 3 * 3, 3 * 3 * 3 * 3};
  constexpr static int qs[] = {1, 7, 7 * 7, 7 * 7 * 7, 7 * 7 * 7 * 7};

  constexpr static bool isA[] = {1, 1, 0, 0, 0, 0, 0, 0, 1, 0};
  constexpr static bool isB[] = {0, 0, 1, 0, 0, 1, 1, 0, 0, 1};
  constexpr static int preA[] = {0, 1, 2, 2, 2, 2, 2, 2, 2, 3};  // prefix count
  constexpr static int preB[] = {0, 0, 0, 1, 1, 1, 2, 3, 3, 3};  // prefix count

 public:
  int rotatedDigits(int n) {
    ++n;  // convert to range [0, n)

    int count = 0;
    bool hasB = false;  // prefix digits already has B.
    for (int i = 4; i >= 0; --i) {
      int ten = tens[i], p = ps[i], q = qs[i];
      if (n < ten) continue;

      int d = n / ten;  // first digit

      if (!hasB) {
        count += preA[d] * (q - p);  // good numbers with first digit A
        count += preB[d] * q;        // good numbers with first digit B
      } else {
        count += (preA[d] + preB[d]) * q;  // we already has B in the prefix
      }

      // Handle trailing digits
      if (!isA[d] && !isB[d]) break;  // leading C
      if (isB[d]) hasB = true;
      n %= ten;
    }

    return count;
  }
};
