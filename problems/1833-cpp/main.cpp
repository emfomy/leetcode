// Source: https://leetcode.com/problems/maximum-ice-cream-bars
// Title: Maximum Ice Cream Bars
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// It is a sweltering summer day, and a boy wants to buy some ice cream bars.
//
// At the store, there are `n` ice cream bars. You are given an array `costs` of length `n`, where `costs[i]` is the price of the `i^th` ice cream bar in coins. The boy initially has `coins` coins to spend, and he wants to buy as many ice cream bars as possible.
//
// **Note:** The boy can buy the ice cream bars in any order.
//
// Return the **maximum** number of ice cream bars the boy can buy with `coins` coins.
//
// You must solve the problem by counting sort.
//
// **Example 1:**
//
// ```
// Input: costs = [1,3,2,4,1], coins = 7
// Output: 4
// Explanation: The boy can buy ice cream bars at indices 0,1,2,4 for a total price of 1 + 3 + 2 + 1 = 7.
// ```
//
// **Example 2:**
//
// ```
// Input: costs = [10,6,8,7,7,8], coins = 5
// Output: 0
// Explanation: The boy cannot afford any of the ice cream bars.
// ```
//
// **Example 3:**
//
// ```
// Input: costs = [1,6,3,1,2,5], coins = 20
// Output: 6
// Explanation: The boy can buy all the ice cream bars for a total price of 1 + 6 + 3 + 1 + 2 + 5 = 18.
// ```
//
// **Constraints:**
//
// - `costs.length == n`
// - `1 <= n <= 10^5`
// - `1 <= costs[i] <= 10^5`
// - `1 <= coins <= 10^8`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// Sort
class Solution {
 public:
  int maxIceCream(vector<int>& costs, int coins) {
    sort(costs.begin(), costs.end());

    int bars = 0;  // ice cream bars
    for (int cost : costs) {
      if (coins >= cost) {
        coins -= cost;
        ++bars;
      } else {
        break;
      }
    }

    return bars;
  }
};

// Counting Sort
class Solution2 {
  constexpr static int maxCost = 1e5;

 public:
  int maxIceCream(const vector<int>& costs, int coins) {
    auto freqs = vector<int>(maxCost + 1);
    for (int cost : costs) {
      ++freqs[cost];
    }

    int bars = 0;  // ice cream bars
    for (int cost = 1; cost <= maxCost; ++cost) {
      if (freqs[cost] == 0) continue;
      int canBuy = min(freqs[cost], coins / cost);
      bars += canBuy;
      coins -= canBuy * cost;
      if (coins <= cost) break;  // can't buy next
    }

    return bars;
  }
};
