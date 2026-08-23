// Source: https://leetcode.com/problems/stone-game-ix
// Title: Stone Game IX
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Alice and Bob continue their games with stones. There is a row of n stones, and each stone has an associated value. You are given an integer array `stones`, where `stones[i]` is the **value** of the `i^th` stone.
//
// Alice and Bob take turns, with **Alice** starting first. On each turn, the player may remove any stone from `stones`. The player who removes a stone **loses** if the **sum** of the values of **all removed stones** is divisible by `3`. Bob will win automatically if there are no remaining stones (even if it is Alice's turn).
//
// Assuming both players play **optimally**, return `true` if Alice wins and `false` if Bob wins.
//
// **Example 1:**
//
// ```
// Input: stones = [2,1]
// Output: true
// Explanation:The game will be played as follows:
// - Turn 1: Alice can remove either stone.
// - Turn 2: Bob removes the remaining stone.
// The sum of the removed stones is 1 + 2 = 3 and is divisible by 3. Therefore, Bob loses and Alice wins the game.
// ```
//
// **Example 2:**
//
// ```
// Input: stones = [2]
// Output: false
// Explanation:Alice will remove the only stone, and the sum of the values on the removed stones is 2.
// Since all the stones are removed and the sum of values is not divisible by 3, Bob wins the game.
// ```
//
// **Example 3:**
//
// ```
// Input: stones = [5,1,2,4,3]
// Output: false
// Explanation: Bob will always win. One possible way for Bob to win is shown below:
// - Turn 1: Alice can remove the second stone with value 1. Sum of removed stones = 1.
// - Turn 2: Bob removes the fifth stone with value 3. Sum of removed stones = 1 + 3 = 4.
// - Turn 3: Alices removes the fourth stone with value 4. Sum of removed stones = 1 + 3 + 4 = 8.
// - Turn 4: Bob removes the third stone with value 2. Sum of removed stones = 1 + 3 + 4 + 2 = 10.
// - Turn 5: Alice removes the first stone with value 5. Sum of removed stones = 1 + 3 + 4 + 2 + 5 = 15.
// Alice loses the game because the sum of the removed stones (15) is divisible by 3. Bob wins the game.
// ```
//
// **Constraints:**
//
// - `1 <= stones.length <= 10^5`
// - `1 <= stones[i] <= 10^4`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <array>
#include <cstdlib>
#include <vector>

using namespace std;

// We group the stones by their residue (divided by 3).
// Denote the group by g0, g1, g2, and the numbers are s0, s1, s2.
//
// First, we focus on s0.
// If s0 is even, then the result is equal to s0 = 0.
// If s1 is odd, then  the result is equal to s0 = 1.
//
// ----
//
// Now focus on s0 = 0. The game must be in either pattern
// 1-1-2-1-2-1-... or 2-2-1-2-1-2-...
//
// We focus on the first pattern first.
// Bob is forced to pick g1, and Alice is forced to pick g2 (after her first pick).
//
// 1(12)*  (no more g1 and g2): Bob wins   (s1 = s2+1)
// 1(12)*  (no more g1):        Alice wins (s1 < s2+1 i.e. s1 <= s2)
// 1(12)*1 (no more g2 and g2): Bob wins   (s1 = s2+2)
// 1(12)*1 (no more g2):        Bob wins   (s1 > s2+2)
// In summary, Alice wins iff. s2 >= s1 > 0 (s1 > 0 since Alice need pick the first stone)
//
// Similarly, Alice wins for s1 >= s2 > 0 when she choose the second pattern.
// In summary, is s0 is even, Alice wins if s1 > 0 and s2 > 0.
//
// ----
//
// Now focus on s0 = 1.
// Note that g0 can be place anywhere. For simplicity, we place it at front.
//
// 10(12)*  (no more g1 and g2): Bob wins   (s1 = s2+1)
// 10(12)*  (no more g1):        Bob wins   (s1 < s2+1)
// 10(12)*1 (no more g2 and g2): Bob wins   (s1 = s2+2)
// 10(12)*1 (no more g2):        Alice wins (s1 > s2+2)
// In summary, Alice wins iff. s1 > s2+2.
// Similarly, Alice wins for s2 > s1+2 when she choose the second pattern..
// In summary, is s0 is even, Alice wins if abs(s1-s2) > 2.
class Solution {
 public:
  bool stoneGameIX(const vector<int>& stones) {
    int groups[3] = {};
    for (int stone : stones) {
      ++groups[stone % 3];
    }

    if (groups[0] % 2 == 0) {
      return groups[1] > 0 && groups[2] > 0;
    } else {
      return abs(groups[1] - groups[2]) > 2;
    }
  }
};
