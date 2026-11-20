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

#include <algorithm>
#include <climits>
#include <vector>

using namespace std;

// DP
//
// Flat0[i] = 0
// Hold1[i] be the maximum profit with holding the first stock
// Flat1[i] be the maximum profit after selling the first stock.
// Hold2[i] be the maximum profit with holding the second stock
// Flat2[i] be the maximum profit after selling the second stock.
class Solution {
 public:
  int maxProfit(const vector<int>& prices) {
    int flat0 = 0, flat1 = 0, flat2 = 0;
    int hold1 = INT_MIN, hold2 = INT_MIN;

    for (int price : prices) {
      flat2 = max(flat2, hold2 + price);
      hold2 = max(hold2, flat1 - price);
      flat1 = max(flat1, hold1 + price);
      hold1 = max(hold1, flat0 - price);
    }

    return flat2;
  }
};
