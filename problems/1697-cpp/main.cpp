// Source: https://leetcode.com/problems/checking-existence-of-edge-length-limited-paths
// Title: Checking Existence of Edge Length Limited Paths
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// An undirected graph of `n` nodes is defined by `edgeList`, where `edgeList[i] = [u_i, v_i, dis_i]` denotes an edge between nodes `u_i` and `v_i` with distance `dis_i`. Note that there may be **multiple** edges between two nodes.
//
// Given an array `queries`, where `queries[j] = [p_j, q_j, limit_j]`, your task is to determine for each `queries[j]` whether there is a path between `p_j` and `q_j`_ such that each edge on the path has a distance **strictly less than** `limit_j` .
//
// Return a **boolean array** `answer`, where `answer.length == queries.length` and the `j^th` value of `answer` is `true` if there is a path for `queries[j]` is `true`, and `false` otherwise.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2020/12/08/h.png
//
// ```
// Input: n = 3, edgeList = [[0,1,2],[1,2,4],[2,0,8],[1,0,16]], queries = [[0,1,2],[0,2,5]]
// Output: [false,true]
// Explanation: The above figure shows the given graph. Note that there are two overlapping edges between 0 and 1 with distances 2 and 16.
// For the first query, between 0 and 1 there is no path where each distance is less than 2, thus we return false for this query.
// For the second query, there is a path (0 -> 1 -> 2) of two edges with distances less than 5, thus we return true for this query.
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2020/12/08/q.png
//
// ```
// Input: n = 5, edgeList = [[0,1,10],[1,2,5],[2,3,9],[3,4,13]], queries = [[0,4,14],[1,4,13]]
// Output: [true,false]
// Explanation: The above figure shows the given graph.
// ```
//
// **Constraints:**
//
// - `2 <= n <= 10^5`
// - `1 <= edgeList.length, queries.length <= 10^5`
// - `edgeList[i].length == 3`
// - `queries[j].length == 3`
// - `0 <= u_i, v_i, p_j, q_j <= n - 1`
// - `u_i != v_i`
// - `p_j != q_j`
// - `1 <= dis_i, limit_j <= 10^9`
// - There may be **multiple** edges between two nodes.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <numeric>
#include <vector>

using namespace std;

// Union-Find + Sort
//
// First the edges and queries by its weight and limit.
// Next loop for each query,
// add all edges with weight less than limit into the graph,
// update connectivity using union find,
// and check the query result.
class Solution {
  struct UnionFind {
    mutable vector<int> parents;
    mutable vector<int> ranks;

    UnionFind(int n) : parents(n), ranks(n) {  //
      iota(parents.begin(), parents.end(), 0);
    }

    int find(int x) const {
      if (parents[x] != x) {
        parents[x] = find(parents[x]);
      }
      return parents[x];
    }

    bool isConnected(int x, int y) const {  //
      return find(x) == find(y);
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

  // Shared data structure for edge and query
  // Edge:  (dist, INF, from,   to)
  // Query: (dist, id,  source, target)
  using Data = tuple<int, int, int, int>;

 public:
  vector<bool> distanceLimitedPathsExist(  //
      const int n,                         //
      vector<vector<int>>& edges,          //
      const vector<vector<int>>& queries   //
  ) {
    const int m = edges.size();
    const int q = queries.size();

    // Prepare answer
    auto ans = vector<bool>(q);

    // Prepare data
    auto data = vector<Data>();
    data.reserve(m + q);
    for (int i = 0; i < m; ++i) {
      int u = edges[i][0], v = edges[i][1], dist = edges[i][2];
      data.emplace_back(dist, INT_MAX, u, v);
    }
    for (int i = 0; i < q; ++i) {
      int u = queries[i][0], v = queries[i][1], limit = queries[i][2];
      data.emplace_back(limit, i, u, v);
    }

    // Sort data
    sort(data.begin(), data.end());

    // Loop data
    UnionFind uf(n);
    for (auto [_, id, u, v] : data) {
      if (id == INT_MAX) {  // edge
        uf.unite(u, v);
      } else {  // query
        ans[id] = uf.isConnected(u, v);
      }
    }

    return ans;
  }
};
