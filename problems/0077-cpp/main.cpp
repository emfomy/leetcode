// Source: https://leetcode.com/problems/combinations
// Title: Combinations
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given two integers `n` and `k`, return all possible combinations of `k` numbers chosen from the range `[1, n]`.
//
// You may return the answer in **any order**.
//
// **Example 1:**
//
// ```
// **Input:** n = 4, k = 2
// **Output:** [[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]
// **Explanation:** There are 4 choose 2 = 6 total combinations.
// Note that combinations are unordered, i.e., [1,2] and [2,1] are considered to be the same combination.
// ```
//
// **Example 2:**
//
// ```
// **Input:** n = 1, k = 1
// **Output:** [[1]]
// **Explanation:** There is 1 choose 1 = 1 total combination.
// ```
//
// **Constraints:**
//
// - `1 <= n <= 20`
// - `1 <= k <= n`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <numeric>
#include <vector>

using namespace std;

// First fill the state with largest k numbers.
//
// For each step, increase the last number.
// If the last number reach to top (e.g. 125 -> 126; n=5), increase the second last one instead,
// and set the last number to the number above the second last one (e.g. 125 -> 134; n=5).
//
// If above operation is invalid (e.g. 1256 -> 1267; n = 6), then choose third last number (and so on),
// and fill the number right of the chosen number contiguous increasing (e.g. 1256 -> 1345; n=6).
class Solution {
 public:
  vector<vector<int>> combine(int n, int k) {
    if (k < 0 || k > n) return {};  // invalid
    if (k == 0) return {{}};        // edge case

    // Init state
    auto state = vector<int>(k);
    iota(state.begin(), state.end(), 1);  // [1, 2, ..., k]

    // Loop
    auto ans = vector<vector<int>>();  // we can reserve the array if we know binom(n, k)
    while (true) {
      ans.push_back(state);

      // Find the rightmost increasable index
      // Index i can be increased if state[i] < n - (k-1-i)
      int i = k - 1;
      while (i >= 0 && state[i] == n - k + i + 1) {
        --i;
      }

      // End of loop
      if (i < 0) break;

      // Increate
      ++state[i];

      // fill the right numbers
      iota(state.begin() + i + 1, state.end(), state[i] + 1);
    }

    return ans;
  }
};
