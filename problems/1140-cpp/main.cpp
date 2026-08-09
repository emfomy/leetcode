// Source: https://leetcode.com/problems/stone-game-ii
// Title: Stone Game II
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Alice and Bob continue their games with piles of stones. There are a number of piles **arranged in a row**, and each pile has a positive integer number of stones `piles[i]`. The objective of the game is to end with the most stones.
//
// Alice and Bob take turns, with Alice starting first.
//
// On each player's turn, that player can take **all the stones** in the **first** `X` remaining piles, where `1 <= X <= 2M`. Then, we set `M = max(M, X)`. Initially, M = 1.
//
// The game continues until all the stones have been taken.
//
// Assuming Alice and Bob play optimally, return the maximum number of stones Alice can get.
//
// **Example 1:**
//
// ```
// Input: piles = [2,7,9,4,4]
// Output: 10
// Explanation:
// - If Alice takes one pile at the beginning, Bob takes two piles, then Alice takes 2 piles again. Alice can get `2 + 4 + 4 = 10` stones in total.
// - If Alice takes two piles at the beginning, then Bob can take all three piles left. In this case, Alice get `2 + 7 = 9` stones in total.
// So we return 10 since it's larger.
// ```
//
// **Example 2:**
//
// ```
// Input: piles = [1,2,3,4,5,100]
// Output: 104
// ```
//
// **Constraints:**
//
// - `1 <= piles.length <= 100`
// - `1 <= piles[i]<= 10^4`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <climits>
#include <numeric>
#include <vector>

using namespace std;

// DFS + Cache
//
// DP[i, m] = score difference (current player - other player) for range [i, n)
// DP[i, m] = sum piles[>=i] if i + m >= n (since you can get all)
//
// Say optional difference is D, and the total sum is S.
// Alice - Bob = D; Alice + Bob = S.
// Alice = (S+D)/2.
class Solution {
  using Bool = unsigned char;

  struct DFS {
    vector<int> prefix;  // prefix sum for piles
    vector<vector<Bool>> seen;
    vector<vector<int>> memo;  // [i, m]
    int n;

    DFS(const vector<int>& piles) {
      n = piles.size();

      prefix.resize(n + 1);
      prefix[0] = 0;
      for (int i = 0; i < n; ++i) {
        prefix[i + 1] = prefix[i] + piles[i];
      }

      seen.assign(n, vector<Bool>(n, false));
      memo.assign(n, vector<int>(n, 0));
    }

    int run(int i, int m) {
      // Select all remaining
      if (i + 2 * m >= n) return prefix[n] - prefix[i];

      // Cache Read
      if (seen[i][m]) return memo[i][m];

      // Run
      int best = INT_MIN;
      for (int x = 1; x <= min(2 * m, n - i); ++x) {
        best = max(best, prefix[i + x] - prefix[i] - run(i + x, max(m, x)));
      }

      // Cache Write
      seen[i][m] = true;
      memo[i][m] = best;
      return best;
    }
  };

 public:
  int stoneGameII(const vector<int>& piles) {
    int total = accumulate(piles.cbegin(), piles.cend(), 0);

    auto dfs = DFS(piles);
    int diff = dfs.run(0, 1);

    return (total + diff) / 2;
  }
};

// DP
//
// DP states only depends on larger i.
// Therefore, instead of DFS, we can compute DP from larger i.
class Solution2 {
 public:
  int stoneGameII(const vector<int>& piles) {
    const int n = piles.size();

    // Total
    int total = accumulate(piles.cbegin(), piles.cend(), 0);

    // Prefix sum
    auto prefix = vector<int>(n + 1);
    prefix[0] = 0;
    for (int i = 0; i < n; ++i) {
      prefix[i + 1] = prefix[i] + piles[i];
    }

    // DP
    auto dp = vector<vector<int>>(n + 1, vector<int>(n + 1));
    for (int i = n - 1; i >= 0; --i) {
      for (int m = 1; m <= n; ++m) {
        if (i + 2 * m >= n) {
          dp[i][m] = prefix[n] - prefix[i];
          continue;
        }

        // Run
        int best = INT_MIN;
        for (int x = 1; x <= min(2 * m, n - i); ++x) {
          best = max(best, prefix[i + x] - prefix[i] - dp[i + x][min(max(m, x), n)]);
        }
        dp[i][m] = best;
      }
    }

    return (total + dp[0][1]) / 2;
  }
};
