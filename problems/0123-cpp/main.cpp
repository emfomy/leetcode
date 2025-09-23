// Source: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii
// Title: Best Time to Buy and Sell Stock III
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an array `prices` where `prices[i]` is the price of a given stock on the `i^th` day.
//
// Find the maximum profit you can achieve. You may complete **at most two transactions**.
//
// **Note:** You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).
//
// **Example 1:**
//
// ```
// Input: prices = [3,3,5,0,0,3,1,4]
// Output: 6
// Explanation: Buy on day 4 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
// Then buy on day 7 (price = 1) and sell on day 8 (price = 4), profit = 4-1 = 3.```
//
// **Example 2:**
//
// ```
// Input: prices = [1,2,3,4,5]
// Output: 4
// Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
// Note that you cannot buy on day 1, buy on day 2 and sell them later, as you are engaging multiple transactions at the same time. You must sell before buying again.
// ```
//
// **Example 3:**
//
// ```
// Input: prices = [7,6,4,3,1]
// Output: 0
// Explanation: In this case, no transaction is done, i.e. max profit = 0.
// ```
//
// **Constraints:**
//
// - `1 <= prices.length <= 10^5`
// - `0 <= prices[i] <= 10^5`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <climits>
#include <vector>

using namespace std;

// Use DP
//
// Say we buy and sell on day x1, x2 & y1, y2.
// Note that we may complete **at most** two transactions;
// that is, we can buy & sell at the same day;
// tat is, x1 <= y1 <= x2 <= y2.
//
// The profit is -prices[x1] + prices[y1] - prices[x2] + prices[y2].
// Let a1 =      prices[x1]
// Let b1 = a1 + prices[y1]
// Let a2 = b1 - prices[x2]
// Let b2 = a2 + prices[y2]
//
// We want to maximize a and b
class Solution {
 public:
  int maxProfit(vector<int>& prices) {
    auto a1 = INT_MIN, a2 = INT_MIN, b1 = INT_MIN, b2 = INT_MIN;

    for (auto price : prices) {
      a1 = max(a1, -price);
      b1 = max(b1, a1 + price);
      a2 = max(a2, b1 - price);
      b2 = max(b2, a2 + price);
    }
    return b2;
  }
};
