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
// **Input:** n = 3, k = 1
// **Output:** "0"
// **Explanation:** S_3 is "**0**111001".
// The 1^st bit is "0".
// ```
//
// **Example 2:**
//
// ```
// **Input:** n = 4, k = 11
// **Output:** "1"
// **Explanation:** S_4 is "0111001101**1**0001".
// The 11^th bit is "1".
// ```
//
// **Constraints:**
//
// - `1 <= n <= 20`
// - `1 <= k <= 2^n - 1`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace std;

// Recursion
//
// Denote B(n, k) be the bit we want. (k is 1-indexed).
//
// The length of Sn is 2^n-1. Let m = 2^(n-1)
// If k == m (middle), then B(n, k) = 1.
// If k < m, then B(n, k) = B(n-1, k).
// If k > m, then B(n, k) = !B(n-1, 2m-k).
class Solution {
 public:
  char findKthBit(int n, int k) {
    if (n == 1) return '0';

    int mid = (1 << (n - 1));
    if (k == mid) return '1';                             // middle
    if (k < mid) return findKthBit(n - 1, k);             // left half
    return ('1' + '0') - findKthBit(n - 1, 2 * mid - k);  // right half
  }
};
