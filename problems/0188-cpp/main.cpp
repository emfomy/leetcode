// Source: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv
// Title: Best Time to Buy and Sell Stock IV
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `prices` where `prices[i]` is the price of a given stock on the `i^th` day, and an integer `k`.
//
// Find the maximum profit you can achieve. You may complete at most `k` transactions: i.e. you may buy at most `k` times and sell at most `k` times.
//
// **Note:** You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).
//
// **Example 1:**
//
// ```
// Input: k = 2, prices = [2,4,1]
// Output: 2
// Explanation: Buy on day 1 (price = 2) and sell on day 2 (price = 4), profit = 4-2 = 2.
// ```
//
// **Example 2:**
//
// ```
// Input: k = 2, prices = [3,2,6,5,0,3]
// Output: 7
// Explanation: Buy on day 2 (price = 2) and sell on day 3 (price = 6), profit = 6-2 = 4. Then buy on day 5 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
// ```
//
// **Constraints:**
//
// - `1 <= k <= 100`
// - `1 <= prices.length <= 1000`
// - `0 <= prices[i] <= 1000`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <climits>
#include <vector>

using namespace std;

// Use DP
//
// Say we buy on day x1, x2, ..., xk; sell on day y1, y2, ..., yk.
// Note that we may complete **at most** k transactions;
// that is, we can buy & sell at the same day;
// tat is, x1 <= y1 <= x2 <= ... <= yk.
//
// The profit is sum_i - prices[xi] + prices[yi].
// Let b0 = 0
// Let a1 = b0 - prices[x1]
// Let b1 = a1 + prices[y1]
// ...
// Let ai = b{i-1} + prices[xi]
// Let bi = ai     + prices[yi]
//
// We want to maximize a and b
class Solution {
 public:
  int maxProfit(int k, vector<int>& prices) {
    auto a = vector(k + 1, INT_MIN);
    auto b = vector(k + 1, INT_MIN);
    b[0] = 0;

    for (auto price : prices) {
      for (auto i = 1; i <= k; ++i) {
        a[i] = max(a[i], b[i - 1] - price);
        b[i] = max(b[i], a[i] + price);
      }
    }
    return b[k];
  }
};
