// Source: https://leetcode.com/problems/number-of-digit-one
// Title: Number of Digit One
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer `n`, count the total number of digit `1` appearing in all non-negative integers less than or equal to `n`.
//
// **Example 1:**
//
// ```
// Input: n = 13
// Output: 6
// ```
//
// **Example 2:**
//
// ```
// Input: n = 0
// Output: 0
// ```
//
// **Constraints:**
//
// - `0 <= n <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>

using namespace std;

// Recursion
//
// Say n has d digits. let m = 10^(d-1).
// Say the highest digit is k.
// If the k > 1, then all d-digit number with leading 1 exists (i.e. m of them).
// If the k = 1, then there are only n-m+1 numbers with leading 1.
// That is, min(m, n-m+1) of these numbers.
//
// Now focus on the lower digits.
// For each digit, in the first km numbers,
// there are exactly 1/10 of them is 1.
// Therefore the first km numbers has total km(d-1)/10 ones for lower digits.
//
// For the last n-km numbers, we apply above algorithm on n-km.
//
class Solution {
  int numDigits(int n) {
    int d = 0;
    while (n > 0) {
      n /= 10;
      ++d;
    }
    return d;
  }

  int pow10(int d) {
    int tens = 1;
    for (int i = 0; i < d; ++i) {
      tens *= 10;
    }
    return tens;
  }

 public:
  int countDigitOne(int n) {
    if (n == 0) return 0;
    int d = numDigits(n);
    int m = pow10(d - 1);           // m = 10^(d-1)
    int k = n / m;                  // leading digit
    int count = min(m, n - m + 1);  // leading 1s
    count += (m / 10) * k * (d - 1);
    count += countDigitOne(n - k * m);
    return count;
  }
};

// Iteration
class Solution2 {
 public:
  int countDigitOne(int n) {
    // number of digits
    int d = 0;
    for (int tmp = n; tmp > 0; tmp /= 10) ++d;

    // 10^(d-1)
    int m = 1;
    for (int i = 1; i < d; ++i) m *= 10;

    // Loop
    int count = 0;
    while (n > 0) {
      int k = n / m;  // leading digit

      if (k > 0) {
        count += min(m, n - m + 1);  // leading 1s
        count += (m / 10) * k * (d - 1);
      }

      // Next digit
      n -= k * m;
      --d, m /= 10;
    }

    return count;
  }
};
