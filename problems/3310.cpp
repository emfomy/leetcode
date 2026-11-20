// Source: https://leetcode.com/problems/remove-methods-from-project
// Title: Remove Methods From Project
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are maintaining a project that has `n` methods numbered from `0` to `n - 1`.
//
// You are given two integers `n` and `k`, and a 2D integer array `invocations`, where `invocations[i] = [a_i, b_i]` indicates that method `a_i` invokes method `b_i`.
//
// There is a known bug in method `k`. Method `k`, along with any method invoked by it, either **directly** or **indirectly**, are considered **suspicious** and we aim to remove them.
//
// A group of methods can only be removed if no method **outside** the group invokes any methods **within** it.
//
// Return an array containing all the remaining methods after removing all the **suspicious** methods. You may return the answer in any order. If it is not possible to remove **all** the suspicious methods, **none** should be removed.
//
// **Example 1:**
//
// ```
// Input: n = 4, k = 1, invocations = [[1,2],[0,1],[3,2]]
// Output: [0,1,2,3]
// Explanation:
// https://assets.leetcode.com/uploads/2024/07/18/graph-2.png
// Method 2 and method 1 are suspicious, but they are directly invoked by methods 3 and 0, which are not suspicious. We return all elements without removing anything.
// ```
//
// **Example 2:**
//
// ```
// Input: n = 5, k = 0, invocations = [[1,2],[0,2],[0,1],[3,4]]
// Output: [3,4]
// Explanation:
// https://assets.leetcode.com/uploads/2024/07/18/graph-3.png
// Methods 0, 1, and 2 are suspicious and they are not directly invoked by any other method. We can remove them.
// ```
//
// **Example 3:**
//
// ```
// Input: n = 3, k = 2, invocations = [[1,2],[0,1],[2,0]]
// Output: []
// Explanation:
// https://assets.leetcode.com/uploads/2024/07/20/graph.png
// All methods are suspicious. We can remove them.
// ```
//
// **Constraints:**
//
// - `1 <= n <= 10^5`
// - `0 <= k <= n - 1`
// - `0 <= invocations.length <= 2 * 10^5`
// - `invocations[i] == [a_i, b_i]`
// - `0 <= a_i, b_i <= n - 1`
// - `a_i != b_i`
// - `invocations[i] != invocations[j]`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <numeric>
#include <queue>
#include <vector>

using namespace std;

// BFS + Union-Find
//
// Use BFS to mark suspicious nodes.
// Use Union-Find to group the nodes.
//
// Remove the group with all nodes suspicious.
class Solution {
  using Bool = unsigned char;

  class UnionFind {
    vector<int> parents;
    vector<int> ranks;

   public:
    UnionFind(int n) : parents(n), ranks(n, 0) {  //
      iota(parents.begin(), parents.end(), 0);
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
  vector<int> remainingMethods(int n, int k, const vector<vector<int>>& invocations) {
    // Build graph + Union Find
    auto graph = vector<vector<int>>(n);
    auto uf = UnionFind(n);
    for (const auto& edge : invocations) {
      int a = edge[0], b = edge[1];
      graph[a].push_back(b);
      uf.unite(a, b);
    }

    // BFS
    auto sus = vector<Bool>(n);
    auto que = queue<int>();
    sus[k] = true;
    que.push(k);
    while (!que.empty()) {
      int node = que.front();
      que.pop();

      for (int next : graph[node]) {
        if (sus[next]) continue;
        sus[next] = true;
        que.push(next);
      }
    }

    // Find keep groups
    auto keep = vector<Bool>(n);
    for (int i = 0; i < n; ++i) {
      if (!sus[i]) {
        int p = uf.find(i);  // group root
        keep[p] = true;
      }
    }

    // Answer
    auto ans = vector<int>();
    ans.reserve(n);
    for (int i = 0; i < n; ++i) {
      int p = uf.find(i);
      if (keep[p]) ans.push_back(i);
    }

    return ans;
  }
};

// BFS + Hash Set
//
// We don't need union find.
// There will only one group with suspicious nodes.
//
// We use in-degree.
// On BFS, we also remove all out-bound edge of each suspicious node.
// Note that we only update the in-degree (not actually remove the edge).
//
// After BFS, check if all suspicious node has zero in-degree.
// If so, remove all suspicious node. Otherwise, keep all.
class Solution2 {
  using Bool = unsigned char;

 public:
  vector<int> remainingMethods(int n, int k, const vector<vector<int>>& invocations) {
    // Build graph
    auto graph = vector<vector<int>>(n);
    auto inDeg = vector<int>(n);
    for (const auto& edge : invocations) {
      int a = edge[0], b = edge[1];
      graph[a].push_back(b);
      ++inDeg[b];
    }

    // BFS
    auto sus = vector<Bool>(n);
    auto que = queue<int>();
    sus[k] = true;
    que.push(k);
    while (!que.empty()) {
      int node = que.front();
      que.pop();

      for (int next : graph[node]) {
        --inDeg[next];
        if (sus[next]) continue;
        sus[next] = true;
        que.push(next);
      }
    }

    // Check in-degree
    bool allZero = true;
    for (int i = 0; i < n; ++i) {
      if (sus[i] && inDeg[i] > 0) {
        allZero = false;
        break;
      }
    }

    // Answer
    auto ans = vector<int>();
    ans.reserve(n);
    for (int i = 0; i < n; ++i) {
      if (allZero && sus[i]) continue;
      ans.push_back(i);
    }

    return ans;
  }
};
