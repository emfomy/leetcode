// Source: https://leetcode.com/problems/stone-game-v
// Title: Stone Game V
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There are several stones **arranged in a row**, and each stone has an associated value which is an integer given in the array `stoneValue`.
//
// In each round of the game, Alice divides the row into **two non-empty rows** (i.e. left row and right row), then Bob calculates the value of each row which is the sum of the values of all the stones in this row. Bob throws away the row which has the maximum value, and Alice's score increases by the value of the remaining row. If the value of the two rows are equal, Bob lets Alice decide which row will be thrown away. The next round starts with the remaining row.
//
// The game ends when there is only **one stone remaining**. Alice's score is initially **zero**.
//
// Return <i>the maximum score that Alice can obtain</i>.
//
// **Example 1:**
//
// ```
// Input: stoneValue = [6,2,3,4,5,5]
// Output: 18
// Explanation: In the first round, Alice divides the row to [6,2,3], [4,5,5]. The left row has the value 11 and the right row has value 14. Bob throws away the right row and Alice's score is now 11.
// In the second round Alice divides the row to [6], [2,3]. This time Bob throws away the left row and Alice's score becomes 16 (11 + 5).
// The last round Alice has only one choice to divide the row which is [2], [3]. Bob throws away the right row and Alice's score is now 18 (16 + 2). The game ends because only one stone is remaining in the row.
// ```
//
// **Example 2:**
//
// ```
// Input: stoneValue = [7,7,7,7,7,7,7]
// Output: 28
// ```
//
// **Example 3:**
//
// ```
// Input: stoneValue = [4]
// Output: 0
// ```
//
// **Constraints:**
//
// - `1 <= stoneValue.length <= 500`
// - `1 <= stoneValue[i] <= 10^6`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

// Prefix Sum + DPS + Cache
class Solution {
  struct DFS {
    vector<int> pre;
    vector<vector<int>> memo;

    DFS(const vector<int>& arr) {
      const int n = arr.size();
      pre.resize(n + 1);
      for (int i = 0; i < n; ++i) {
        pre[i + 1] = pre[i] + arr[i];
      }

      memo.assign(n, vector<int>(n + 1));
    }

    int run(int i, int j) {
      // End of DFS
      if (j - i <= 1) return 0;

      // Cache read
      int& score = memo[i][j];
      if (score > 0) return score;

      // DFS
      for (int k = i + 1; k < j; ++k) {
        int left = pre[k] - pre[i];
        int right = pre[j] - pre[k];
        if (left < right) {
          score = max(score, left + run(i, k));
        } else if (left > right) {
          score = max(score, right + run(k, j));
        } else {
          score = max(score, left + max(run(i, k), run(k, j)));
        }
      }

      return score;
    }
  };

 public:
  int stoneGameV(const vector<int>& stoneValue) {
    const int n = stoneValue.size();

    return DFS(stoneValue).run(0, n);
  }
};

// Prefix Sum + DP
//
// Compute the problem for each range.
// We compute it from bottom-up: computing the smaller ranges first.
// For each range, try all possible split.
// Total complexity is O(n^3).
//
// More specifically:
// Denote dp[i][j] as the max score for range [i, j).
// Let k be the cut; i < k < j.
// If sum[i, k) < sum[k, j), then the score is sum[i, k) + dp[i][k].
// If sum[i, k) > sum[k, j), then the score is sum[k, j) + dp[k][j].
// If sum[i, k) = sum[k, j), then the score is sum[i, k) + max(dp[i][k], dp[k][j]).
// dp[i][j] is the max within above scores.
class Solution2 {
 public:
  int stoneGameV(const vector<int>& stoneValue) {
    const int n = stoneValue.size();

    // Prefix Sum
    auto pre = vector<int>(n + 1);
    for (int i = 0; i < n; ++i) {
      pre[i + 1] = pre[i] + stoneValue[i];
    }

    // [i, j) ranges
    auto dp = vector<vector<int>>(n, vector<int>(n + 1));
    for (int s = 2; s <= n; ++s) {  // range size
      for (int i = 0; i <= n - s; ++i) {
        int j = i + s;
        int& score = dp[i][j];
        for (int k = i + 1; k < j; ++k) {
          int left = pre[k] - pre[i];
          int right = pre[j] - pre[k];
          if (left < right) {
            score = max(score, left + dp[i][k]);
          } else if (left > right) {
            score = max(score, right + dp[k][j]);
          } else {
            score = max(score, left + max(dp[i][k], dp[k][j]));
          }
        }
      }
    }

    return dp[0][n];
  }
};
