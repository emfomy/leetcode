// Source: https://leetcode.com/problems/x-of-a-kind-in-a-deck-of-cards
// Title: X of a Kind in a Deck of Cards
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `deck` where `deck[i]` represents the number written on the `i^th` card.
//
// Partition the cards into **one or more groups** such that:
//
// - Each group has **exactly** `x` cards where `x > 1`, and
// - All the cards in one group have the same integer written on them.
//
// Return `true` if such partition is possible, or `false` otherwise.
//
// **Example 1:**
//
// ```
// Input: deck = [1,2,3,4,4,3,2,1]
// Output: true
// Explanation: Possible partition [1,1],[2,2],[3,3],[4,4].
// ```
//
// **Example 2:**
//
// ```
// Input: deck = [1,1,1,2,2,2,3,3]
// Output: false
// Explanation: No possible partition.
// ```
//
// **Constraints:**
//
// - `1 <= deck.length <= 10^4`
// - `0 <= deck[i] < 10^4`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <numeric>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  bool hasGroupsSizeX(const vector<int>& deck) {
    const int n = deck.size();
    if (n == 0) return true;

    // Count the card in deck
    auto counter = unordered_map<int, int>();
    counter.reserve(n);
    for (int card : deck) {
      ++counter[card];
    }

    // Computer the GCD of card counts
    // gcd(0, x) = x
    int x = 0;
    for (const auto [_, count] : counter) {
      x = gcd(x, count);
      if (x == 1) return false;
    }

    return true;
  }
};
