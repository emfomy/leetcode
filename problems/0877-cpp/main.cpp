// Source: https://leetcode.com/problems/stone-game
// Title: Stone Game
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Alice and Bob play a game with piles of stones. There are an **even** number of piles arranged in a row, and each pile has a **positive** integer number of stones `piles[i]`.
//
// The objective of the game is to end with the most stones. The **total** number of stones across all the piles is **odd**, so there are no ties.
//
// Alice and Bob take turns, with **Alice starting first**. Each turn, a player takes the entire pile of stones either from the **beginning** or from the **end** of the row. This continues until there are no more piles left, at which point the person with the **most stones wins**.
//
// Assuming Alice and Bob play optimally, return `true` if Alice wins the game, or `false` if Bob wins.
//
// **Example 1:**
//
// ```
// Input: piles = [5,3,4,5]
// Output: true
// Explanation:
// Alice starts first, and can only take the first 5 or the last 5.
// Say she takes the first 5, so that the row becomes [3, 4, 5].
// If Bob takes 3, then the board is [4, 5], and Alice takes 5 to win with 10 points.
// If Bob takes the last 5, then the board is [3, 4], and Alice takes 4 to win with 9 points.
// This demonstrated that taking the first 5 was a winning move for Alice, so we return true.
// ```
//
// **Example 2:**
//
// ```
// Input: piles = [3,7,2,3]
// Output: true
// ```
//
// **Constraints:**
//
// - `2 <= piles.length <= 500`
// - `piles.length` is **even**.
// - `1 <= piles[i] <= 500`
// - `sum(piles[i])` is **odd**.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// DP
//
// DP[k][i] is defined as score(current user) - score(another user) for the range [i, i+k)
// DP[1][i] = nums[i] since Bob can no choice.
// DP[k][i] = max(piles[i] - DP[k-1][i+1], piles[i+k-1] - DP[k-1][i])
//
// Then answer is DP[n][0]
class Solution {
 public:
  bool stoneGame(const vector<int>& piles) {
    const int n = piles.size();

    auto prev = vector<int>(n);
    auto curr = vector<int>(piles.cbegin(), piles.cend());

    for (int k = 2; k <= n; ++k) {
      swap(curr, prev);
      for (int i = 0; i <= n - k; ++i) {
        curr[i] = max(piles[i] - prev[i + 1], piles[i + k - 1] - prev[i]);
      }
    }

    return curr[0] > 0;
  }
};

// We group the piles by the parity of the indices.
// Denoted as A and B group.
//
// Since Alice pick first, the two end of the piles are in the different group.
// Similarly, when Bob pick, the two end of the piles are in the same group.
//
// WLOG, say the A group is larger.
// Alice always pick the pile from the A group,
// and keep both end with B group for Bob.
//
// Hence Alice always win.
class Solution2 {
 public:
  bool stoneGame(const vector<int>& piles) {
    return true;  //
  }
};
