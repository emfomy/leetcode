// Source: https://leetcode.com/problems/find-the-maximum-number-of-elements-in-subset
// Title: Find the Maximum Number of Elements in Subset
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an array of **positive** integers `nums`.
//
// You need to select a <button>subset</button> of `nums` which satisfies the following condition:
//
// - You can place the selected elements in a **0-indexed** array such that it follows the pattern: `[x, x^2, x^4, ..., x^k/2, x^k, x^k/2, ..., x^4, x^2, x]` (**Note** that `k` can be be any **non-negative** power of `2`). For example, `[2, 4, 16, 4, 2]` and `[3, 9, 3]` follow the pattern while `[2, 4, 8, 4, 2]` does not.
//
// Return the **maximum** number of elements in a subset that satisfies these conditions.
//
// **Example 1:**
//
// ```
// Input: nums = [5,4,1,2,2]
// Output: 3
// Explanation: We can select the subset {4,2,2}, which can be placed in the array as [2,4,2] which follows the pattern and 2^2 == 4. Hence the answer is 3.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [1,3,2,4]
// Output: 1
// Explanation: We can select the subset {1}, which can be placed in the array as [1] which follows the pattern. Hence the answer is 1. Note that we could have also selected the subsets {2}, {3}, or {4}, there may be multiple subsets which provide the same answer.
// ```
//
// **Constraints:**
//
// - `2 <= nums.length <= 10^5`
// - `1 <= nums[i] <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <map>
#include <vector>

using namespace std;

// Hash Map + DP
//
// First count and sort the numbers.
// DP[i]+1 is max length of [x, x^2, ..., x^k] with x^k = i.
//
// Therefore, we loop for the number from the smallest,
// For each y, if y occurs twice and y^2 exists, set DP[y^2] = DP[y]+1.
// Otherwise, DP[y] = 0.
//
// Note that 1 is edge case. 1 is and power of itself.
// A set with all 1 also satisfy the pattern.
// However, the set should have odd size.
class Solution {
 public:
  int maximumLength(const vector<int>& nums) {
    // Count frequencies
    auto freqs = unordered_map<int64_t, int>();
    for (int num : nums) {
      ++freqs[num];
    }

    // Edge case
    int freq1 = freqs.contains(1) ? freqs[1] : 0;
    int size1 = freq1 % 2 ? (freq1 - 1) : freq1;  // allow only odd
    freqs.erase(1);                               // remove edge case

    // Sort numbers
    auto keys = vector<int64_t>();
    keys.reserve(freqs.size());
    for (auto [num, _] : freqs) {
      keys.push_back(num);
    }
    sort(keys.begin(), keys.end());

    // DP
    auto dp = unordered_map<int64_t, int>();
    dp.reserve(freqs.size());
    int count = 0;
    for (int64_t x : keys) {
      count = max(count, dp[x]);
      if (freqs[x] > 1 && freqs.contains(x * x)) {
        dp[x * x] = dp[x] + 1;
      }
    }

    return max(2 * count + 1, size1);
  }
};

// Hash Map + DP
//
// We can cache computed sequence length.
//
// Let DP[i] be the sequence length staring at i.
// When finding a sequence and encounter a non-zero DP[x^t],
// just add DP[x^t] to current sequence length.
class Solution2 {
 public:
  int maximumLength(const vector<int>& nums) {
    // Count frequencies
    auto freqs = unordered_map<int64_t, int>();
    for (int num : nums) {
      ++freqs[num];
    }

    // Edge case
    int freq1 = freqs.contains(1) ? freqs[1] : 0;
    int size1 = freq1 % 2 ? freq1 : (freq1 - 1);  // allow only odd
    freqs.erase(1);                               // remove edge case

    // Helper
    auto dp = unordered_map<int64_t, int>();
    auto getLen = [&](auto& self, int64_t x) -> int {
      if (!freqs.contains(x)) return 0;
      if (dp[x] > 0) return dp[x];
      if (freqs.at(x) == 1) return dp[x] = 1;
      return dp[x] = self(self, x * x) + 1;
    };

    // Loop
    dp.reserve(freqs.size());
    int maxCount = 0;
    for (auto [x, _] : freqs) {
      maxCount = max(maxCount, getLen(getLen, x));
    }

    return max(2 * maxCount - 1, size1);
  }
};

// Hash Map
//
// Denote M=10^9 be the maximum number.
//
// Assume this is the maximum sequence [x, x^2, x^(2^2), ..., x^(2^p)].
// since x^(2^p) <= M, we have p <= loglogM.
//
// Since loglogM is usually smaller than logN,
// instead of sorting the array with O(NlogN),
// we can loop all possible sequence with O(NloglogM).
class Solution3 {
 public:
  int maximumLength(const vector<int>& nums) {
    // Count frequencies
    auto freqs = unordered_map<int64_t, int>();
    for (int num : nums) {
      ++freqs[num];
    }

    // Edge case
    int freq1 = freqs.contains(1) ? freqs[1] : 0;
    int size1 = freq1 % 2 ? freq1 : (freq1 - 1);  // allow only odd
    freqs.erase(1);                               // remove edge case

    // Loop
    int maxCount = 0;
    for (auto [x, _] : freqs) {
      int count = 0;
      int64_t y = x;
      do {
        ++count;
        if (freqs[y] == 1) break;
        y *= y;
      } while (freqs.contains(y));
      maxCount = max(maxCount, count);
    }

    return max(2 * maxCount - 1, size1);
  }
};
