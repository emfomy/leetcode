// Source: https://leetcode.com/problems/number-of-unique-xor-triplets-i
// Title: Number of Unique XOR Triplets I
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `nums` of length `n`, where `nums` is a **permutation** of the numbers in the range `[1, n]`.
//
// A **XOR triplet** is defined as the XOR of three elements `nums[i] XOR nums[j] XOR nums[k]` where `i <= j <= k`.
//
// Return the number of **unique** XOR triplet values from all possible triplets `(i, j, k)`.
//
// **Example 1:**
//
// ```
// Input: nums = [1,2]
// Output: 2
// Explanation:
// The possible XOR triplet values are:
// - `(0, 0, 0) → 1 XOR 1 XOR 1 = 1`
// - `(0, 0, 1) → 1 XOR 1 XOR 2 = 2`
// - `(0, 1, 1) → 1 XOR 2 XOR 2 = 1`
// - `(1, 1, 1) → 2 XOR 2 XOR 2 = 2`
// The unique XOR values are `{1, 2}`, so the output is 2.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [3,1,2]
// Output: 4
// Explanation:
// The possible XOR triplet values include:
// - `(0, 0, 0) → 3 XOR 3 XOR 3 = 3`
// - `(0, 0, 1) → 3 XOR 3 XOR 1 = 1`
// - `(0, 0, 2) → 3 XOR 3 XOR 2 = 2`
// - `(0, 1, 2) → 3 XOR 1 XOR 2 = 0`
// The unique XOR values are `{0, 1, 2, 3}`, so the output is 4.
// ```
//
// **Constraints:**
//
// - `1 <= n == nums.length <= 10^5`
// - `1 <= nums[i] <= n`
// - `nums` is a permutation of integers from `1` to `n`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <bit>
#include <unordered_set>
#include <vector>

using namespace std;

// DP, TLE
//
// The order is invariant to XOR.
// Therefore, we can treat nums as [1, 2, ..., n].
class Solution {
 public:
  int uniqueXorTriplets(const vector<int>& nums) {
    const int n = nums.size();

    auto state2 = unordered_set<int>();
    state2.reserve(n);
    for (int i = 1; i <= n; ++i) {
      for (int j = i; j <= n; ++j) {
        state2.insert(i ^ j);
      }
    }

    auto state3 = unordered_set<int>();
    state2.reserve(n);
    for (int ij : state2) {
      for (int k = 1; k <= n; ++k) {
        state3.insert(ij ^ k);
      }
    }

    return state3.size();
  }
};

// Math
//
// If n = 1, then ans = 1.
// If n = 2, then ans = 2.
// If n > 2, then ans is the next power of 2.
//
// More precisely, then unique values are:
// n = 1: {1}
// n = 2: {1, 2}
// n > 2: {0, 1, ..., k}, where k is the next power of 2 minus 1.
//
// For n <= 2, just brute force all triplets.
//
// For n > 2, pick m=2^d be an power of 2 (m >= 4).
// We want to prove that for any n in [m, 2m), then result is {0, ..., 2m-1}.
//
// We first observe that all the n in the range has the same leading bit.
// Since XOR can't product higher bit, then the output must be less than 2m.
// Now we only need to prove that n=m can produce {0, ..., 2m-1},
// since adding more numbers won't get less results.
//
// Let x be the output number.
// For x = 0, we have 0 = 1 ^ 2 ^ 3.
// For 0 < x <= m, we have x = 1 ^ 1 ^ x.
// For m < x < 2m, let y = x-m in [1, m). We have x = y ^ m.
// We want to find a pair with y = a ^ b and a, b in [1, m).
// If y != 1, just pick a = 1 and b = (1^y).
// Since y != 1 and y < m, we have b != 0 and b < m.
// If y = 1, then pick a = 2 and b = 3. (valid since m >= 4).
class Solution2 {
 public:
  int uniqueXorTriplets(const vector<int>& nums) {
    const int n = nums.size();
    if (n == 1) return 1;
    if (n == 2) return 2;
    return std::bit_ceil(unsigned(n + 1));
  }
};
