// Source: https://leetcode.com/problems/coin-change
// Title: Coin Change
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `coins` representing coins of different denominations and an integer `amount` representing a total amount of money.
//
// Return the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return `-1`.
//
// You may assume that you have an infinite number of each kind of coin.
//
// **Example 1:**
//
// ```
// Input: coins = [1,2,5], amount = 11
// Output: 3
// Explanation: 11 = 5 + 5 + 1
// ```
//
// **Example 2:**
//
// ```
// Input: coins = [2], amount = 3
// Output: -1
// ```
//
// **Example 3:**
//
// ```
// Input: coins = [1], amount = 0
// Output: 0
// ```
//
// **Constraints:**
//
// - `1 <= coins.length <= 12`
// - `1 <= coins[i] <= 2^31 - 1`
// - `0 <= amount <= 10^4`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <climits>
#include <queue>
#include <vector>

using namespace std;

// DP, O(amount * len(coins))
class Solution {
 public:
  int coinChange(vector<int>& coins, int amount) {
    auto dp = vector(amount + 1, INT_MAX);
    dp[amount] = 0;

    for (auto i = amount; i > 0; --i) {
      if (dp[i] == INT_MAX) continue;
      for (auto coin : coins) {
        auto j = i - coin;
        if (j < 0) continue;
        dp[j] = min(dp[j], dp[i] + 1);
      }
    }

    return dp[0] == INT_MAX ? -1 : dp[0];
  }
};

// DP, O(amount * len(coins))
class Solution2 {
 public:
  int coinChange(vector<int>& coins, int amount) {
    auto dp = vector(amount + 1, INT_MAX);
    dp[0] = 0;

    for (auto i = 0; i < amount; ++i) {
      if (dp[i] == INT_MAX) continue;
      for (auto coin : coins) {
        auto j = uint32_t(i) + coin;
        if (j > amount) continue;
        dp[j] = min(dp[j], dp[i] + 1);
      }
    }

    return dp[amount] == INT_MAX ? -1 : dp[amount];
  }
};

// DP + Heap, O(amount * len(coins))
class Solution3 {
 public:
  int coinChange(vector<int>& coins, int amount) {
    auto dp = vector(amount + 1, -1);
    auto pq = priority_queue(greater(), vector<int>());  // min-heap
    dp[0] = 0;
    pq.push(0);
    while (!pq.empty()) {
      auto i = pq.top();
      pq.pop();

      for (auto coin : coins) {
        auto j = uint32_t(i) + coin;
        if (j > amount) continue;
        if (dp[j] < 0) {
          pq.push(j);
          dp[j] = dp[i] + 1;
        } else {
          dp[j] = min(dp[j], dp[i] + 1);
        }
      }
    }

    return dp[amount];
  }
};
