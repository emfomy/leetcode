// Source: https://leetcode.com/problems/predict-the-winner
// Title: Predict the Winner
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `nums`. Two players are playing a game with this array: player 1 and player 2.
//
// Player 1 and player 2 take turns, with player 1 starting first. Both players start the game with a score of `0`. At each turn, the player takes one of the numbers from either end of the array (i.e., `nums[0]` or `nums[nums.length - 1]`) which reduces the size of the array by `1`. The player adds the chosen number to their score. The game ends when there are no more elements in the array.
//
// Return `true` if Player 1 can win the game. If the scores of both players are equal, then player 1 is still the winner, and you should also return `true`. You may assume that both players are playing optimally.
//
// **Example 1:**
//
// ```
// Input: nums = [1,5,2]
// Output: false
// Explanation: Initially, player 1 can choose between 1 and 2.
// If he chooses 2 (or 1), then player 2 can choose from 1 (or 2) and 5. If player 2 chooses 5, then player 1 will be left with 1 (or 2).
// So, final score of player 1 is 1 + 2 = 3, and player 2 is 5.
// Hence, player 1 will never be the winner and you need to return false.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [1,5,233,7]
// Output: true
// Explanation: Player 1 first chooses 1. Then player 2 has to choose between 5 and 7. No matter which number player 2 choose, player 1 can choose 233.
// Finally, player 1 has more score (234) than player 2 (12), so you need to return True representing player1 can win.
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 20`
// - `0 <= nums[i] <= 10^7`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// DFS + Cache
//
// For each [i, j] range, we compute the score difference (player1 - player2).
class Solution {
  using Bool = unsigned char;

  struct DFS {
    const vector<int>& nums;
    vector<vector<Bool>>& seen;
    vector<vector<int>>& memo;

    int run(int i, int j) {
      // End of game
      if (i == j) return nums[i];

      // Cache read
      if (seen[i][j]) return memo[i][j];

      // Move
      int score = max(nums[i] - run(i + 1, j), nums[j] - run(i, j - 1));

      // Cache write
      seen[i][j] = true;
      memo[i][j] = score;

      return score;
    }
  };

 public:
  bool predictTheWinner(const vector<int>& nums) {
    const int n = nums.size();

    auto seen = vector<vector<Bool>>(n, vector<Bool>(n, 0));
    auto memo = vector<vector<int>>(n, vector<int>(n, 0));
    DFS dfs{nums, seen, memo};

    return dfs.run(0, n - 1) >= 0;
  }
};

// DP
//
// DP[k, i] = score difference (current player - other player) for range [i, i+k]
// DP[0, i] = nums[i] since current player has no choice
// DP[k, i] = max(
//   nums[i]   - DP[k-1, i+1], // pick first number
//   nums[i+k] - DP[k-1, i],   // pick last number
// )
//
// Then answer is DP[n-1][0]
// Note: 0 <= k < n; 0 <= i; i+k < n
class Solution2 {
 public:
  bool predictTheWinner(const vector<int>& nums) {
    const int n = nums.size();

    auto prev = vector<int>(n);
    auto curr = vector<int>(nums.cbegin(), nums.cend());  // DP[0, i]

    for (int k = 1; k < n; ++k) {
      swap(prev, curr);
      for (int i = 0; i < n - k; ++i) {
        curr[i] = max(nums[i] - prev[i + 1], nums[i + k] - prev[i]);
      }
    }

    return curr[0] >= 0;
  }
};

// DFS + Cache
//
// Note that player 1 wins if the array length is even.
// See 877 Stone Game.
class Solution3 {
 public:
  bool predictTheWinner(const vector<int>& nums) {
    const int n = nums.size();

    if (n % 2 == 0) return true;

    auto prev = vector<int>(n);
    auto curr = vector<int>(nums.cbegin(), nums.cend());  // DP[0, i]

    for (int k = 1; k < n; ++k) {
      swap(prev, curr);
      for (int i = 0; i < n - k; ++i) {
        curr[i] = max(nums[i] - prev[i + 1], nums[i + k] - prev[i]);
      }
    }

    return curr[0] >= 0;
  }
};
