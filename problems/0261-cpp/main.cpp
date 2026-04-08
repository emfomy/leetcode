// Source: https://leetcode.com/problems/graph-valid-tree
// Title: Graph Valid Tree
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You have a graph of `n` nodes labeled from `0` to `n - 1`. You are given an integer n and a list of `edges` where `edges[i] = [a_i, b_i]` indicates that there is an undirected edge between nodes `a_i` and `b_i` in the graph.
//
// Return `true` if the edges of the given graph make up a valid tree, and `false` otherwise.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/03/12/tree1-graph.jpg
//
// ```
// Input: n = 5, edges = [[0,1],[0,2],[0,3],[1,4]]
// Output: true
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2021/03/12/tree2-graph.jpg
//
// ```
// Input: n = 5, edges = [[0,1],[1,2],[2,3],[1,3],[1,4]]
// Output: false
// ```
//
// **Constraints:**
//
// - `1 <= n <= 2000`
// - `0 <= edges.length <= 5000`
// - `edges[i].length == 2`
// - `0 <= a_i, b_i < n`
// - `a_i != b_i`
// - There are no self-loops or repeated edges.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <numeric>
#include <vector>

using namespace std;

// Kruskal (Union-Find)
//
// A graph is a tree iff. it is connected and E = V-1.
class Solution {
  struct UnionFind {
    mutable vector<int> parents;
    mutable vector<int> ranks;
    int count;  // connected components

    UnionFind(int n) : parents(n), ranks(n, 0), count(n) {  //
      iota(parents.begin(), parents.end(), 0);
    }

    int find(int x) const {
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
      --count;
    }
  };

 public:
  bool validTree(int n, const vector<vector<int>>& edges) {
    const int e = edges.size();
    if (e != n - 1) return false;

    auto uf = UnionFind(n);
    for (const auto& edge : edges) {
      uf.unite(edge[0], edge[1]);
    }

    return uf.count == 1;
  }
};
