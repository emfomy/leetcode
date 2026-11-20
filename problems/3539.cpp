// Source: https://leetcode.com/problems/find-sum-of-array-product-of-magical-sequences
// Title: Find Sum of Array Product of Magical Sequences
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given two integers, `m` and `k`, and an integer array `nums`.
// A sequence of integers `seq` is called **magical** if:
//
// - `seq` has a size of `m`.
// - `0 <= seq[i] < nums.length`
// - The **binary representation** of `2^seq[0] + 2^seq[1] + ... + 2^seq[m - 1]` has `k` **set bits**.
//
// The **array product** of this sequence is defined as `prod(seq) = (nums[seq[0]] * nums[seq[1]] * ... * nums[seq[m - 1]])`.
//
// Return the **sum** of the **array products** for all valid **magical** sequences.
//
// Since the answer may be large, return it **modulo** `10^9 + 7`.
//
// A **set bit** refers to a bit in the binary representation of a number that has a value of 1.
//
// **Example 1:**
//
// ```
// Input: m = 5, k = 5, nums = [1,10,100,10000,1000000]
// Output: 991600007
// Explanation:
// All permutations of `[0, 1, 2, 3, 4]` are magical sequences, each with an array product of 10^13.
// ```
//
// **Example 2:**
//
// ```
// Input: m = 2, k = 2, nums = [5,4,3,2,1]
// Output: 170
// Explanation:
// The magical sequences are `[0, 1]`, `[0, 2]`, `[0, 3]`, `[0, 4]`, `[1, 0]`, `[1, 2]`, `[1, 3]`, `[1, 4]`, `[2, 0]`, `[2, 1]`, `[2, 3]`, `[2, 4]`, `[3, 0]`, `[3, 1]`, `[3, 2]`, `[3, 4]`, `[4, 0]`, `[4, 1]`, `[4, 2]`, and `[4, 3]`.
// ```
//
// **Example 3:**
//
// ```
// Input: m = 1, k = 1, nums = [28]
// Output: 28
// Explanation:
// The only magical sequence is `[0]`.
// ```
//
// **Constraints:**
//
// - `1 <= k <= m <= 30`
// - `1 <= nums.length <= 50`
// - `1 <= nums[i] <= 10^8`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <bit>
#include <cstdint>
#include <functional>
#include <vector>

using namespace std;

// Use DFS + Cache
//
// The cache index is (i, j, c, b)
// i: we have processed nums[0:i]
// j: number of items to fill in seq (initalized j = m)
// r: the carry value from lower bits
// p: the number of bits in binary seq
//
// For each step, we try to add some copies of "i" into the seq, and update j, r, p respectively.
// Say we add "c" copies. Note that we now have "c+r" in the "i"-th bit.
// j -= c (filled "c" items)
// p += (c+r) % 2 (keep the odd bit)
// r = (c+r) / 2 (the carry value of current bit)
class Solution {
  constexpr static int modulo = 1e9 + 7;

 private:
  static array<array<int64_t, 31>, 31> getBinom() {
    auto C = array<array<int64_t, 31>, 31>();
    for (auto i = 0; i <= 30; ++i) {
      C[i][0] = C[i][i] = 1;
      for (auto j = 1; j < i; ++j) {
        C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % modulo;
      }
    }
    return C;
  }

 public:
  int magicalSum(int m, int k, vector<int>& nums) {
    auto static binom = getBinom();

    int n = nums.size();

    auto cache = vector(n, vector(m + 1, vector(m + 1, vector(k + 1, int64_t(-1)))));

    // DFS
    function<int64_t(int, int, int, int)> dfs = [&](int i, int j, int r, int p) -> int64_t {
      // If i == n, then end loop
      // Check if j == 0: seq must be filled
      // Check if p + popcount(r) == k: must have total k bits
      if (i == n) return (j == 0 && p + popcount(unsigned(r)) == k);

      if (cache[i][j][r][p] >= 0) return cache[i][j][r][p];

      int64_t ans = 0;
      int64_t numPow = 1;              // = nums[i]^c
      for (auto c = 0; c <= j; ++c) {  // insert "c" copies of "i" into seq
        auto j2 = j - c;
        auto r2 = (c + r) / 2;
        auto p2 = (c + r) % 2 + p;
        if (p2 > k) continue;  // too many bits

        auto ans2 = dfs(i + 1, j2, r2, p2);
        ans2 = (ans2 * numPow) % modulo;
        ans2 = (ans2 * binom[j][c]) % modulo;
        ans = (ans + ans2) % modulo;

        numPow = (numPow * nums[i]) % modulo;
      }

      cache[i][j][r][p] = ans;
      return ans;
    };

    return dfs(0, m, 0, 0);
  }
};
