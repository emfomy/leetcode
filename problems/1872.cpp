// Source: https://leetcode.com/problems/stone-game-viii
// Title: Stone Game VIII
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Alice and Bob take turns playing a game, with **Alice starting first**.
//
// There are `n` stones arranged in a row. On each player's turn, while the number of stones is **more than one**, they will do the following:
//
// - Choose an integer `x > 1`, and **remove** the leftmost `x` stones from the row.
// - Add the **sum** of the **removed** stones' values to the player's score.
// - Place a **new stone**, whose value is equal to that sum, on the left side of the row.
//
// The game stops when **only** **one** stone is left in the row.
//
// The **score difference** between Alice and Bob is `(Alice's score - Bob's score)`. Alice's goal is to **maximize** the score difference, and Bob's goal is the **minimize** the score difference.
//
// Given an integer array `stones` of length `n` where `stones[i]` represents the value of the `i^th` stone **from the left**, return the **score difference** between Alice and Bob if they both play **optimally**.
//
// **Example 1:**
//
// ```
// Input: stones = [-1,2,-3,4,-5]
// Output: 5
// Explanation:
// - Alice removes the first 4 stones, adds (-1) + 2 + (-3) + 4 = 2 to her score, and places a stone of
//   value 2 on the left. stones = [2,-5].
// - Bob removes the first 2 stones, adds 2 + (-5) = -3 to his score, and places a stone of value -3 on
//   the left. stones = [-3].
// The difference between their scores is 2 - (-3) = 5.
// ```
//
// **Example 2:**
//
// ```
// Input: stones = [7,-6,5,10,5,-2,-6]
// Output: 13
// Explanation:
// - Alice removes all stones, adds 7 + (-6) + 5 + 10 + 5 + (-2) + (-6) = 13 to her score, and places a
//   stone of value 13 on the left. stones = [13].
// The difference between their scores is 13 - 0 = 13.
// ```
//
// **Example 3:**
//
// ```
// Input: stones = [-10,-12]
// Output: -22
// Explanation:
// - Alice can only make one move, which is to remove both stones. She adds (-10) + (-12) = -22 to her
//   score and places a stone of value -22 on the left. stones = [-22].
// The difference between their scores is (-22) - 0 = -22.
// ```
//
// **Constraints:**
//
// - `n == stones.length`
// - `2 <= n <= 10^5`
// - `-10^4 <= stones[i] <= 10^4`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <climits>
#include <numeric>
#include <vector>

using namespace std;

// Minimax, O(n^2) TLE
//
// First compute the prefix sum of the stones.
// No matter what the play goes,
// the new stone placed at index i is always the sum of [0, i].
//
// Let V[i] be the max diff after player place a new stone at index i.
class Solution {
  using Bool = unsigned char;

  struct DFS {
    const int n;
    vector<int> pre;   // sum of [0, i]
    vector<int> memo;  // V[i]
    vector<Bool> seen;

    DFS(const vector<int>& stones) : n(stones.size()), pre(n), memo(n - 1), seen(n - 1) {
      partial_sum(stones.cbegin(), stones.cend(), pre.begin());
    }

    int run(int i) {
      // End
      if (i == n - 1) return 0;

      // Cache hit
      int& cache = memo[i];
      if (seen[i]) return cache;

      // Traverse
      seen[i] = true;
      cache = INT_MIN;
      for (int j = i + 1; j < n; ++j) {
        cache = max(cache, pre[j] - run(j));
      }

      return cache;
    }
  };

 public:
  int stoneGameVIII(const vector<int>& stones) {
    auto dfs = DFS(stones);

    return dfs.run(0);
  }
};

// DP, O(n)
//
// Note that in above Minimax, the transition only depend on j.
// We can compute V[i] from back to front.
//
// V[i] = max(Pre[j] - V[j]), j > i
//      = max(Pre[i+1] - V[i+1], max(Pre[j] - V[j])), j > i+1
//      = max(Pre[i+1] - V[i+1], V[i+1])
class Solution2 {
 public:
  int stoneGameVIII(const vector<int>& stones) {
    const int n = stones.size();

    // Prefix Sum
    auto pre = vector<int>(n);  // sum[0, i]
    partial_sum(stones.cbegin(), stones.cend(), pre.begin());

    // DP
    auto dp = vector<int>(n - 1);
    dp[n - 2] = pre[n - 1];
    for (int i = n - 3; i >= 0; --i) {
      dp[i] = max(pre[i + 1] - dp[i + 1], dp[i + 1]);
    }

    return dp[0];
  }
};

// DP, O(n)
//
// We don't need old DP values.
// We also compute the prefix sum in-place.
class Solution3 {
 public:
  int stoneGameVIII(vector<int>& stones) {
    const int n = stones.size();

    // Prefix Sum
    partial_sum(stones.cbegin(), stones.cend(), stones.begin());

    // DP
    int dp = stones[n - 1];
    for (int i = n - 2; i >= 1; --i) {
      dp = max(stones[i] - dp, dp);
    }

    return dp;
  }
};
