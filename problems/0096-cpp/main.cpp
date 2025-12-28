// Source: https://leetcode.com/problems/unique-binary-search-trees
// Title: Unique Binary Search Trees
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer `n`, return the number of structurally unique **BST'**s (binary search trees) which has exactly `n` nodes of unique values from `1` to `n`.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/01/18/uniquebstn3.jpg
//
// ```
// Input: n = 3
// Output: 5
// ```
//
// **Example 2:**
//
// ```
// Input: n = 1
// Output: 1
// ```
//
// **Constraints:**
//
// - `1 <= n <= 19`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// DP
//
// Pick any number as root.
// The number of trees are the product of left and right subtrees.
class Solution {
 public:
  int numTrees(int n) {
    auto dp = vector<int>(n + 1);
    dp[0] = 1;

    for (auto m = 1; m <= n; ++m) {
      for (auto i = 0; i < m; ++i) {
        dp[m] += dp[i] * dp[m - i - 1];
      }
    }
    return dp[n];
  }
};

// Catalan number
//
// C_n = 1/(n+1) binom(2n, n) = (2n)!/(n+1)!n!
// C_0 = 1, C_n = 2(2n-1)/(n+1) C_[n-1]
class Solution2 {
 public:
  int numTrees(int n) {
    auto c = 1ll;
    for (auto i = 1; i <= n; ++i) {
      c = c * 2 * (2 * i - 1) / (i + 1);
    }
    return c;
  }
};

// Catalan number
class Solution3 {
  constexpr static int a000170[] = {
      1,       1,        2,         5,         14,          //
      42,      132,      429,       1430,      4862,        //
      16796,   58786,    208012,    742900,    2674440,     //
      9694845, 35357670, 129644790, 477638700, 1767263190,  //
  };

 public:
  int numTrees(int n) {  //
    return a000170[n];
  }
};
