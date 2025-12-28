// Source: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-using-strategy
// Title: Best Time to Buy and Sell Stock using Strategy
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given two integer arrays `prices` and `strategy`, where:
//
// - `prices[i]` is the price of a given stock on the `i^th` day.
// - `strategy[i]` represents a trading action on the `i^th` day, where:
//
// - `-1` indicates buying one unit of the stock.
// - `0` indicates holding the stock.
// - `1` indicates selling one unit of the stock.
//
// You are also given an **even** integer `k`, and may perform **at most one** modification to `strategy`. A modification consists of:
//
// - Selecting exactly `k` **consecutive** elements in `strategy`.
// - Set the **first** `k / 2` elements to `0` (hold).
// - Set the **last** `k / 2` elements to `1` (sell).
//
// The **profit** is defined as the **sum** of `strategy[i] * prices[i]` across all days.
//
// Return the **maximum** possible profit you can achieve.
//
// **Note:** There are no constraints on budget or stock ownership, so all buy and sell operations are feasible regardless of past actions.
//
// **Example 1:**
//
// ```
// Input: prices = [4,2,8], strategy = [-1,0,1], k = 2
// Output: 10
// Explanation:
//
// Modification   | Strategy    | Profit Calculation                        | Profit
// Original       | [-1, 0, 1]  | (-1 × 4) + (0 × 2) + (1 × 8) = -4 + 0 + 8 | 4
// Modify [0, 1]  | [0, 1, 1]   | (0 × 4) + (1 × 2) + (1 × 8) = 0 + 2 + 8   | 10
// Modify [1, 2]  | [-1, 0, 1]  | (-1 × 4) + (0 × 2) + (1 × 8) = -4 + 0 + 8 | 4
//
// <table style="border: 1px solid black;"><thead><tr><th style="border: 1px solid black;">Modification</th><th style="border: 1px solid black;">Strategy</th><th style="border: 1px solid black;">Profit Calculation</th><th style="border: 1px solid black;">Profit</th></tr></thead><tbody><tr><td style="border: 1px solid black;">Original</td><td style="border: 1px solid black;">[-1, 0, 1]</td><td style="border: 1px solid black;">(-1 × 4) + (0 × 2) + (1 × 8) = -4 + 0 + 8</td><td style="border: 1px solid black;">4</td></tr><tr><td style="border: 1px solid black;">Modify [0, 1]</td><td style="border: 1px solid black;">[0, 1, 1]</td><td style="border: 1px solid black;">(0 × 4) + (1 × 2) + (1 × 8) = 0 + 2 + 8</td><td style="border: 1px solid black;">10</td></tr><tr><td style="border: 1px solid black;">Modify [1, 2]</td><td style="border: 1px solid black;">[-1, 0, 1]</td><td style="border: 1px solid black;">(-1 × 4) + (0 × 2) + (1 × 8) = -4 + 0 + 8</td><td style="border: 1px solid black;">4</td></tr></tbody></table>
// Thus, the maximum possible profit is 10, which is achieved by modifying the subarray `[0, 1]`​​​​​​​.
// ```
//
// **Example 2:**
//
// ```
// Input: prices = [5,4,3], strategy = [1,1,0], k = 2
// Output: 9
// Explanation:
//
// Modification   | Strategy  | Profit Calculation                      | Profit
// Original       | [1, 1, 0] | (1 × 5) + (1 × 4) + (0 × 3) = 5 + 4 + 0 | 9
// Modify [0, 1]  | [0, 1, 0] | (0 × 5) + (1 × 4) + (0 × 3) = 0 + 4 + 0 | 4
// Modify [1, 2]  | [1, 0, 1] | (1 × 5) + (0 × 4) + (1 × 3) = 5 + 0 + 3 | 8
//
// Thus, the maximum possible profit is 9, which is achieved without any modification.
// ```
//
// **Constraints:**
//
// - `2 <= prices.length == strategy.length <= 10^5`
// - `1 <= prices[i] <= 10^5`
// - `-1 <= strategy[i] <= 1`
// - `2 <= k <= prices.length`
// - `k` is even
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <numeric>
#include <vector>

using namespace std;

// Prefix Sum
//
// We first use sliding window to compute the sum of each k/2-window.
// Let S[i] = P[i] + P[i+1] + ... P[i+k/2-1].
//
// Next compute the prefix profit and suffix profit of each day.
// Let Prefix[i] = profit of [0, i), Suffix[i] = profit of [i, end)
// Now for each k-window staring at i, the profit is
// Prefix[i] + S[i+k/2] + Suffix[i+k]
class Solution {
 public:
  int64_t maxProfit(vector<int>& prices, vector<int>& strategy, int k) {
    int n = prices.size();

    // Window sums
    auto sums = vector<int64_t>(n);
    for (auto i = 0; i < k / 2; ++i) sums[0] += prices[i];
    for (auto i = 1; i + k / 2 - 1 < n; ++i) {
      sums[i] = sums[i - 1] - prices[i - 1] + prices[i + k / 2 - 1];
    }

    // Prefixs
    auto prefixs = vector<int64_t>(n + 1);
    prefixs[0] = 0;
    for (auto i = 0; i < n; ++i) {
      prefixs[i + 1] = prefixs[i] + prices[i] * strategy[i];
    }

    // Suffixs
    auto suffixs = vector<int64_t>(n + 1);
    suffixs[n] = 0;
    for (auto i = n - 1; i >= 0; --i) {
      suffixs[i] = suffixs[i + 1] + prices[i] * strategy[i];
    }

    // Answer
    auto ans = prefixs[n];               // original
    for (auto i = 0; i + k <= n; ++i) {  // modify [i, i+k)
      ans = max(ans, prefixs[i] + sums[i + k / 2] + suffixs[i + k]);
    }

    return ans;
  }
};

// Sliding window
//
// First compute the original profit.
// Next slide i from i to n-k-1.
// Profit[i] = Profit[i-1]
//           + price[i-1]*strategy[i-1] - price[i+k]*strategy[i+k]
//           - price[i+k]
class Solution2 {
 public:
  int64_t maxProfit(vector<int>& prices, vector<int>& strategy, int k) {
    int n = prices.size();

    // Original profit
    auto ans = inner_product(prices.cbegin(), prices.cend(), strategy.cbegin(), 0LL);

    // Slice
    auto profit = inner_product(prices.cbegin() + k, prices.cend(), strategy.cbegin() + k, 0LL) +
                  accumulate(prices.cbegin() + k / 2, prices.cbegin() + k, 0LL);
    auto l = 0, m = k / 2, r = k;
    ans = max(ans, profit);
    while (r < n) {
      profit = profit                     //
               + prices[l] * strategy[l]  //
               - prices[r] * strategy[r]  //
               - prices[m] + prices[r];   //
      ans = max(ans, profit);
      ++l, ++m, ++r;
    }

    return ans;
  }
};
