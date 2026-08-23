// Source: https://leetcode.com/problems/stone-game-iv
// Title: Stone Game IV
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Alice and Bob take turns playing a game, with Alice starting first.
//
// Initially, there are `n` stones in a pile. On each player's turn, that player makes a move consisting of removing **any** non-zero **square number** of stones in the pile.
//
// Also, if a player cannot make a move, he/she loses the game.
//
// Given a positive integer `n`, return `true` if and only if Alice wins the game otherwise return `false`, assuming both players play optimally.
//
// **Example 1:**
//
// ```
// Input: n = 1
// Output: true
// Explanation: Alice can remove 1 stone winning the game because Bob doesn't have any moves.```
//
// **Example 2:**
//
// ```
// Input: n = 2
// Output: false
// Explanation: Alice can only remove 1 stone, after that Bob removes the last one winning the game (2 -> 1 -> 0).
// ```
//
// **Example 3:**
//
// ```
// Input: n = 4
// Output: true
// Explanation: n is already a perfect square, Alice can win with one move, removing 4 stones (4 -> 0).
// ```
//
// **Constraints:**
//
// - `1 <= n <= 10^5`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <vector>

using namespace std;

// DP
//
// DP[i] = Win means players wins when n = i.
//
// DP[0] = Lose
// If DP[i] = Lose, then DP[i+t^2] = Win for all t.
//
// We initialize DP to be all Lose (since if we can't ensure to win, then you lose)
class Solution {
  using Bool = unsigned char;

 public:
  bool winnerSquareGame(int n) {
    auto dp = vector<Bool>(n + 1);

    for (int64_t i = 0; i <= n; ++i) {
      if (dp[i]) continue;
      for (int64_t j = 1; i + j * j <= n; ++j) {
        dp[i + j * j] = true;
      }
    }

    return dp[n];
  }
};
