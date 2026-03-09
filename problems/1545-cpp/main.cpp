// Source: https://leetcode.com/problems/find-kth-bit-in-nth-binary-string
// Title: Find Kth Bit in Nth Binary String
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given two positive integers `n` and `k`, the binary string `S_n` is formed as follows:
//
// - `S_1 = "0"`
// - `S_i = S_i - 1 + "1" + reverse(invert(S_i - 1))` for `i > 1`
//
// Where `+` denotes the concatenation operation, `reverse(x)` returns the reversed string `x`, and `invert(x)` inverts all the bits in `x` (`0` changes to `1` and `1` changes to `0`).
//
// For example, the first four strings in the above sequence are:
//
// - `S_1 = "0"`
// - `S_2 = "0**1**1"`
// - `S_3 = "011**1**001"`
// - `S_4 = "0111001**1**0110001"`
//
// Return the `k^th` bit in `S_n`. It is guaranteed that `k` is valid for the given `n`.
//
// **Example 1:**
//
// ```
// Input: n = 3, k = 1
// Output: "0"
// Explanation: S_3 is "**0**111001".
// The 1^st bit is "0".
// ```
//
// **Example 2:**
//
// ```
// Input: n = 4, k = 11
// Output: "1"
// Explanation: S_4 is "0111001101**1**0001".
// The 11^th bit is "1".
// ```
//
// **Constraints:**
//
// - `1 <= n <= 20`
// - `1 <= k <= 2^n - 1`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <bit>
using namespace std;

// Recursion
//
// Denote B(n, k) be the kth bit in S_n. (k is 1-indexed).
//
// Let m = 2^(n-1). Length of S_n is 2m-1.
// If k = m (middle),    then B(n, k) = 1.
// If k < m (left half), then B(n, k) = B(n-1, k).
// If k > m (right half), then B(n, k) = !B(n-1, 2m-k).
class Solution {
 public:
  char findKthBit(int n, int k) {
    if (n == 1) return '0';

    const int m = 1 << (n - 1);
    if (k == m) return '1';
    if (k < m) return findKthBit(n - 1, k);
    return findKthBit(n - 1, 2 * m - k) ^ '0' ^ '1';  // flip 0 and 1
  }
};

// Iteration
//
// Denote B(n, k) be the kth bit in S_n. (k is 1-indexed).
//
// Let m = 2^(n-1). Length of S_n is 2m-1.
// If k = m (middle),    then B(n, k) = 1.
// If k < m (left half), then B(n, k) = B(n-1, k).
// If k > m (right half), then B(n, k) = !B(n-1, 2m-k).
//
// Note that we don't need n in the loop, we can simply use m as terminate condition.
class Solution2 {
 public:
  char findKthBit(int n, int k) {
    bool flip = false;

    for (int m = 1 << (n - 1); m > 1; m >>= 1) {
      if (k == m) return flip ? '0' : '1';

      if (k > m) {
        flip = !flip;
        k = 2 * m - k;
      }
    }

    return flip ? '1' : '0';
  }
};

// Bit Manipulation
//
// Denote B(n, k) be the kth bit in S_n. (k is 1-indexed).
//
// Denote $ as reversion operator, ! as inversion operator, @ = $!.
// @(x + y) = $!(x + y) = $(!x + !y) = $!y + $!x = @y + @x.
// @@x = x.
//
// S_n = S_(n-1)               + 1 + @S_(n-1)
//     = S_(n-2) + 1 + @S_(n-2)+ 1 + @(S_(n-2) + 1 + @S_(n-2))
//     = S_(n-2) + 1 + @S_(n-2)+ 1 + @@S_(n-2) + 1 + @S_(n-2)
//     = S_(n-2) + 1 + @S_(n-2)+ 1 + S_(n-2) + 0 + @S_(n-2)
//     = S  1  @S  1   S  0  @S  1   S  1  @S  0    S  0  @S
// We found that the left and right part of S_n are similar (except the center part).
//
// We claim that above series is always in the following pattern:
// S_n = S 1 @S ? S 0 @S ? S 1 @S ? S 0 @S ? ...
// The even position are always S, and is alternative between S and @S.
// The odd position are always 0 or 1,
// and is alternative between 1 and 0 with skipping a item.
//
// Now thats prove above claim.
// S_n =   S    1   @S   ?   S    0   @S   ?   S    1   @S   ?   S    0   @S   ? ...
//     = S 1 @S ? S 0 @S ? S 1 @S ? S 0 @S ? S 1 @S ? S 0 @S ? S 1 @S ? S 0 @S ? ...
// We discovers that the pattern repeats.
// Note that the indices of these alternative 1 and 0 are p, 3p, 5p, 7p, ...,
// where p is a power of 2.
//
// Therefore we only need to find the series for k.
// We know that p is the largest power of 2 that divides k.
// If p > 1, then the index of k in the series is (n-1)/2p (i.e. floor(n/2p)).
// However, if p = 1, then k is in the series of S @S S @S ..., where S = S_1.
// Here the series is 0 1 0 1 (is different from other series).
class Solution3 {
 public:
  char findKthBit(int n, int k) {
    int t = countr_zero(unsigned(k));  // p = 2^t
    bool bit1 = (k >> (t + 1)) & 1;    // parity of (n-1)/2p
    bool bit2 = t > 0;                 // parity of p
    return '0' + (bit1 ^ bit2);
  }
};
