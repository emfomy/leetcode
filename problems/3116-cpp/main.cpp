// Source: https://leetcode.com/problems/kth-smallest-amount-with-single-denomination-combination
// Title: Kth Smallest Amount With Single Denomination Combination
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `coins` representing coins of different denominations and an integer `k`.
//
// You have an infinite number of coins of each denomination. However, you are **not allowed** to combine coins of different denominations.
//
// Return the `k^th` **smallest** amount that can be made using these coins.
//
// **Example 1:**
//
// ```
// Input: coins = [3,6,9], k = 3
// Output:  9
// Explanation: The given coins can make the following amounts:
// Coin 3 produces multiples of 3: 3, 6, 9, 12, 15, etc.
// Coin 6 produces multiples of 6: 6, 12, 18, 24, etc.
// Coin 9 produces multiples of 9: 9, 18, 27, 36, etc.
// All of the coins combined produce: 3, 6, **9**, 12, 15, etc.
// ```
//
// **Example 2:**
//
// ```
// Input: coins = [5,2], k = 7
// Output: 12
// Explanation: The given coins can make the following amounts:
// Coin 5 produces multiples of 5: 5, 10, 15, 20, etc.
// Coin 2 produces multiples of 2: 2, 4, 6, 8, 10, 12, etc.
// All of the coins combined produce: 2, 4, 5, 6, 8, 10, **12**, 14, 15, etc.
// ```
//
// **Constraints:**
//
// - `1 <= coins.length <= 15`
// - `1 <= coins[i] <= 25`
// - `1 <= k <= 2 * 10^9`
// - `coins` contains pairwise distinct integers.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <string>

using namespace std;

// Greedy
//
// If there are odd number of ?, then Alice wins since she plays last.
// Now we focus on the case that there are only even number of ?.
//
// Here are the strategies.
// Assume that both side still have ?.
// Alice wants to maximize the difference between both half, and Bob wants to minimize.
// Alice picks the larger part and selects 9, or picks the smaller part and selects 0.
// Bob should select the same number in the other half.
// In this case, then difference won't change.
//
// Now we focus on the case when all ? are in the same half.
// If that half is larger, then Alice wins.
// However, if that half is smaller, Bob has a change to win.
// The only thing Bob can do is to ensure the some of the pair they choose is sum to 9.
// Therefore, if the difference is equal to 9*?/2, then Bob wins.
//
// In summary, Bob wins if and only if:
// - number of ? is even
// - the half with more ? is smaller
// - the difference if equal to 9 / 2 * diff(?)
class Solution {
 public:
  bool sumGame(string num) {
    const int n = num.size();

    // Count
    int quesDiff = 0, digitDiff = 0;
    for (int i = 0; i < n / 2; ++i) {
      if (num[i] == '?') {
        ++quesDiff;
      } else {
        digitDiff += num[i] - '0';
      }
    }
    for (int i = n / 2; i < n; ++i) {
      if (num[i] == '?') {
        --quesDiff;
      } else {
        digitDiff -= num[i] - '0';
      }
    }

    // ? is odd
    if (quesDiff % 2 != 0) return true;

    return digitDiff != -quesDiff / 2 * 9;
  }
};
