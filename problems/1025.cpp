// Source: https://leetcode.com/problems/divisor-game
// Title: Divisor Game
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Alice and Bob take turns playing a game, with Alice starting first.
//
// Initially, there is a number `n` on the chalkboard. On each player's turn, that player makes a move consisting of:
//
// - Choosing any integer `x` with `0 < x < n` and `n % x == 0`.
// - Replacing the number `n` on the chalkboard with `n - x`.
//
// Also, if a player cannot make a move, they lose the game.
//
// Return `true` if and only if Alice wins the game, assuming both players play optimally.
//
// **Example 1:**
//
// ```
// Input: n = 2
// Output: true
// Explanation: Alice chooses 1, and Bob has no more moves.
// ```
//
// **Example 2:**
//
// ```
// Input: n = 3
// Output: false
// Explanation: Alice chooses 1, Bob chooses 1, and Alice has no more moves.
// ```
//
// **Constraints:**
//
// - `1 <= n <= 1000`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace std;

// Math
//
// Claim: the player wins iff. n is even.
//
// Prove by induction.
//
// If n is 1, then the player loses.
// If n is 2, then the player wins.
//
// If n is even, choose x = 1. Therefore n-x = n-1 is odd, and the other player loses.
// If n is odd, then x is always odd. Therefore n-x is even, and the other player wins.
class Solution {
 public:
  bool divisorGame(int n) { return n % 2 == 0; }
};
