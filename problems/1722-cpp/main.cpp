// Source: https://leetcode.com/problems/minimize-hamming-distance-after-swap-operations
// Title: Minimize Hamming Distance After Swap Operations
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given two integer arrays, `source` and `target`, both of length `n`. You are also given an array `allowedSwaps` where each `allowedSwaps[i] = [a_i, b_i]` indicates that you are allowed to swap the elements at index `a_i` and index `b_i` **(0-indexed)** of array `source`. Note that you can swap elements at a specific pair of indices **multiple** times and in **any** order.
//
// The **Hamming distance** of two arrays of the same length, `source` and `target`, is the number of positions where the elements are different. Formally, it is the number of indices `i` for `0 <= i <= n-1` where `source[i] != target[i]` **(0-indexed)**.
//
// Return the **minimum Hamming distance** of `source` and `target` after performing **any** amount of swap operations on array `source`.
//
// **Example 1:**
//
// ```
// Input: source = [1,2,3,4], target = [2,1,4,5], allowedSwaps = [[0,1],[2,3]]
// Output: 1
// Explanation: source can be transformed the following way:
// - Swap indices 0 and 1: source = [2,1,3,4]
// - Swap indices 2 and 3: source = [2,1,4,3]
// The Hamming distance of source and target is 1 as they differ in 1 position: index 3.
// ```
//
// **Example 2:**
//
// ```
// Input: source = [1,2,3,4], target = [1,3,2,4], allowedSwaps = []
// Output: 2
// Explanation: There are no allowed swaps.
// The Hamming distance of source and target is 2 as they differ in 2 positions: index 1 and index 2.
// ```
//
// **Example 3:**
//
// ```
// Input: source = [5,1,2,4,3], target = [1,5,4,2,3], allowedSwaps = [[0,4],[4,2],[1,3],[1,4]]
// Output: 0
// ```
//
// **Constraints:**
//
// - `n == source.length == target.length`
// - `1 <= n <= 10^5`
// - `1 <= source[i], target[i] <= 10^5`
// - `0 <= allowedSwaps.length <= 10^5`
// - `allowedSwaps[i].length == 2`
// - `0 <= a_i, b_i <= n - 1`
// - `a_i != b_i`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <numeric>
#include <unordered_map>
#include <vector>

using namespace std;

// Union-Find
//
// Group the swappable indices.
// The minimal distance is the sum of the distance of each group (treat as set).
class Solution {
  struct UnionFind {
    vector<int> parents;
    vector<int> ranks;

    UnionFind(int n) : parents(n), ranks(n, 0) {
      iota(parents.begin(), parents.end(), 0);  //
    }

    int find(int x) {
      if (parents[x] != x) {
        parents[x] = find(parents[x]);
      }
      return parents[x];
    }

    void unite(int x, int y) {
      x = find(x);
      y = find(y);
      if (x == y) return;

      // Ensure rank(x) >= rank(y)
      if (ranks[x] < ranks[y]) swap(x, y);

      // Merge y into x
      if (ranks[x] == ranks[y]) ++ranks[x];
      parents[y] = x;
    }
  };

 public:
  int minimumHammingDistance(                  //
      const vector<int>& source,               //
      const vector<int>& target,               //
      const vector<vector<int>>& allowedSwaps  //
  ) {
    const int n = source.size();

    // Union Find
    auto uf = UnionFind(n);
    for (const auto& allowedSwap : allowedSwaps) {
      uf.unite(allowedSwap[0], allowedSwap[1]);
    }

    // Grouping
    auto groups = vector<vector<int>>(n);
    for (int i = 0; i < n; ++i) {
      groups[uf.find(i)].push_back(i);
    }

    // Distance
    int dist = 0;
    for (int i = 0; i < n; ++i) {
      if (groups[i].empty()) continue;

      unordered_map<int, int> counts;
      for (int j : groups[i]) {
        ++counts[source[j]];
        --counts[target[j]];
      }

      for (auto [_, cnt] : counts) {
        dist += abs(cnt);
      }
    }

    return dist / 2;
  }
};
