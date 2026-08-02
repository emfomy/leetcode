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

#include <algorithm>
#include <unordered_set>
#include <vector>

using namespace std;

// DP + Hash Set
//
// The order is invariant to XOR.
class Solution {
 public:
  int uniqueXorTriplets(const vector<int>& nums) {
    const int n = nums.size();

    auto state2 = unordered_set<int>();
    state2.reserve(n);
    for (int i = 0; i < n; ++i) {
      for (int j = i; j < n; ++j) {
        state2.insert(nums[i] ^ nums[j]);
      }
    }

    auto state3 = unordered_set<int>();
    state2.reserve(n);
    for (int num : state2) {
      for (int k = 0; k < n; ++k) {
        state3.insert(num ^ nums[k]);
      }
    }

    return state3.size();
  }
};

// DP + Array
//
// Use boolean array instead of hash set.
class Solution2 {
  static constexpr int MX = 2048;  // next power of 2 after 1500
  using Bool = unsigned char;

 public:
  int uniqueXorTriplets(const vector<int>& nums) {
    const int n = nums.size();

    auto state2 = vector<bool>(MX);
    for (int i = 0; i < n; ++i) {
      for (int j = i; j < n; ++j) {
        state2[nums[i] ^ nums[j]] = true;
      }
    }

    auto state3 = vector<bool>(MX);
    for (int num = 0; num < MX; ++num) {
      if (!state2[num]) continue;
      for (int k = 0; k < n; ++k) {
        state3[num ^ nums[k]] = true;
      }
    }

    return count(state3.cbegin(), state3.cend(), true);
  }
};
