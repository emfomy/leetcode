// Source: https://leetcode.com/problems/concatenation-of-consecutive-binary-numbers
// Title: Concatenation of Consecutive Binary Numbers
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer `n`, return the **decimal value** of the binary string formed by concatenating the binary representations of `1` to `n` in order, **modulo **`10^9 + 7`.
//
// **Example 1:**
//
// ```
// Input: n = 1
// Output: 1
// Explanation: "1" in binary corresponds to the decimal value 1.
// ```
//
// **Example 2:**
//
// ```
// Input: n = 3
// Output: 27
// Explanation: In binary, 1, 2, and 3 corresponds to "1", "10", and "11".
// After concatenating them, we have "11011", which corresponds to the decimal value 27.
// ```
//
// **Example 3:**
//
// ```
// Input: n = 12
// Output: 505379714
// Explanation
// : The concatenation results in "1101110010111011110001001101010111100".
// The decimal value of that is 118505380540.
// After modulo 10^9 + 7, the result is 505379714.
// ```
//
// **Constraints:**
//
// - `1 <= n <= 10^5`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <bit>
#include <cstdint>

using namespace std;

// Say we concatenate two numbers A and B to get C.
// Say B has d bits. Then C = A * 2^d + B.
// Now lets check the modulo. Let mod(X) be the modulo result of X.
// mod(C) = mod(A * 2^d + B) = mod(mod(A) * mod(2^d) + mod(B))
//
// With above property, we can compute the result step by step,
// and apply modulo in each step.
class Solution {
  constexpr static uint64_t M = 1e9 + 7;

 public:
  int concatenatedBinary(int n) {
    uint64_t res = 0;
    for (uint32_t x = 1; x <= n; ++x) {
      res = ((res << bit_width(x)) | x) % M;
    }

    return res;
  }
};

// Instead of using bit_width,
// we can store the width into an extra variable,
// and increase this variable when x is a power of 2.
class Solution2 {
  constexpr static uint64_t M = 1e9 + 7;

  inline bool isPow2(uint32_t x) { return (x & (x - 1)) == 0; }

 public:
  int concatenatedBinary(int n) {
    uint64_t res = 0;
    int len = 0;
    for (uint32_t x = 1; x <= n; ++x) {
      len += isPow2(x);
      res = ((res << len) | x) % M;
    }

    return res;
  }
};

// Group by bit width
class Solution3 {
  constexpr static uint64_t M = 1e9 + 7;

 public:
  int concatenatedBinary(uint32_t n) {
    uint64_t res = 0;

    for (int len = 1; len <= 31; ++len) {
      uint32_t start = 1u << (len - 1);
      uint32_t end = min(1u << len, n + 1);

      for (uint32_t x = start; x < end; ++x) {
        res = ((res << len) | x) % M;
      }
    }

    return res;
  }
};

// Group by bit width
//
// We first derive the partial sum of Arithmetic-Geometric Series:
// S_k      = sum_{i=0 ~ k-1} (A + iD)R^i
//          = A  + (A+D)R   + (A+2D)R^2 + ... + (A+(k-1)D)R^(k-1)
// RS_k     = AR + (A+D)R^2 + (A+2D)R^3 + ... + (A+(k-1)D)R^k
// S_k(1-R) = A + DR + DR^2 + ... + DR^(k-1) - (A+(k-1)D)R^k
//          = A + DR(1-R^(k-1))/(1-R) - (A+(k-1)D)R^k
// S_k = (A - (A+(k-1)D)R^k)/(1-R) + D(R-R^k))/(1-R)^2
//
// Now back to the problem.
// For each width `w`, say the range is `[x, y].
// Let k = y-x+1, r = 2^w.
// The sum of this range is
// S = x r^(k-1) + (x-1) r^(k-2) + ... + y
//   = y + (y-1) r + (y-2) r^2 + ... + (y-k+1) r^(k-1).
// Pick A = y, D = -1, R = r = 2^w, we have
// S = (y - xr^k) / (1-r) - (r - r^k) / (1-r)^2
//
// Note that since r > 1, we flip can signs:
// S = (xr^k - y) / (r-1) + (r^k - r) / (r-1)^2
//
// By Fermat's Little Theorem, we have
// (r-1)^(-1) = (r-1)^(M-2) mod M
class Solution4 {
  constexpr static uint64_t M = 1e9 + 7;
  constexpr static uint64_t one = 1;

  inline uint64_t mod(uint64_t x) { return x % M; }

  inline uint64_t fastPow(uint64_t x, uint64_t k) {
    uint64_t res = 1;
    while (k > 0) {
      if (k & 1) res = mod(res * x);
      k >>= 1;
      x = mod(x * x);
    }
    return res;
  }

 public:
  int concatenatedBinary(const int n) {
    const uint64_t un = static_cast<uint64_t>(n);
    uint64_t res = 0;

    for (int w = 1; w <= 31; ++w) {
      uint64_t xReal = one << (w - 1);
      uint64_t yReal = min((one << w) - 1, un);

      uint64_t k = (yReal - xReal + 1);
      uint64_t x = mod(xReal);
      uint64_t y = mod(yReal);
      uint64_t r = fastPow(2, w);         // 2^w
      uint64_t rk = fastPow(r, k);        // r^k
      uint64_t s = mod(r + M - 1);        // r-1
      uint64_t sInv = fastPow(s, M - 2);  // 1/(r-1)
      uint64_t sInv2 = mod(sInv * sInv);  // 1/(r-1)^2

      uint64_t term0 = mod(res * rk);                    // shift current result
      uint64_t term1 = mod(mod(x * rk + M - y) * sInv);  // (xr^k - y) / (r-1)
      uint64_t term2 = mod(mod(rk + M - r) * sInv2);     // (r^k - r) / (r-1)^2
      res = mod(term0 + term1 + term2);

      if (y == n) break;
    }

    return res;
  }
};
