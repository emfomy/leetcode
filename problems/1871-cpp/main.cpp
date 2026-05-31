// Source: https://leetcode.com/problems/jump-game-vii
// Title: Jump Game VII
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a **0-indexed** binary string `s` and two integers `minJump` and `maxJump`. In the beginning, you are standing at index `0`, which is equal to `'0'`. You can move from index `i` to index `j` if the following conditions are fulfilled:
//
// - `i + minJump <= j <= min(i + maxJump, s.length - 1)`, and
// - `s[j] == '0'`.
//
// Return `true`<i> if you can reach index </i>`s.length - 1`<i> in </i>`s`, or `false` otherwise.
//
// **Example 1:**
//
// ```
// Input: s = "011010", minJump = 2, maxJump = 3
// Output: true
// Explanation:
// In the first step, move from index 0 to index 3.
// In the second step, move from index 3 to index 5.
// ```
//
// **Example 2:**
//
// ```
// Input: s = "01101110", minJump = 2, maxJump = 3
// Output: false
// ```
//
// **Constraints:**
//
// - `2 <= s.length <= 10^5`
// - `s[i]` is either `'0'` or `'1'`.
// - `s[0] == '0'`
// - `1 <= minJump <= maxJump < s.length`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <queue>
#include <vector>

using namespace std;

// BFS, TLE
class Solution {
  using Bool = unsigned char;

 public:
  bool canReach(const string &s, int minJump, int maxJump) {
    const int n = s.size();

    auto visited = vector<Bool>(n);
    auto que = queue<int>();
    visited[0] = true;
    que.emplace(0);
    while (!que.empty()) {
      int i = que.front();
      que.pop();

      for (int j = i + minJump; j <= i + maxJump && j < n; ++j) {
        if (visited[j] || s[j] == '1') continue;
        if (j == n - 1) return true;
        visited[j] = true;
        que.push(j);
      }
    }

    return false;
  }
};

// Two Pointer + Difference Array
//
// We first scan the array to find the '0' indices.
// Precompute the jumpable ranges for each index.
//
// We use a difference array for reachability.
// Next loop for each index, use difference array to update a range.
class Solution2 {
 public:
  bool canReach(const string &s, int minJump, int maxJump) {
    const int n = s.size();

    // Trivial
    if (s.front() != '0' || s.back() != '0') return false;

    // Find indices
    auto idxs = vector<int>();
    idxs.reserve(n);
    for (int i = 0; i < n; ++i) {
      if (s[i] == '0') idxs.push_back(i);
    }
    int m = idxs.size();

    // Loop
    auto diffs = vector<int>(m + 1);  // difference of reachability
    ++diffs[0];
    --diffs[1];
    int reachable = 0;
    int l = 0, r = 0;
    for (int x = 0; x < m; ++x) {
      reachable += diffs[x];
      if (reachable == 0) continue;

      // Update range
      while (l < m && idxs[l] < idxs[x] + minJump) ++l;
      while (r < m && idxs[r] <= idxs[x] + maxJump) ++r;
      ++diffs[l];
      --diffs[r];
    }

    return reachable;
  }
};
