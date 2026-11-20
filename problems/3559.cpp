// Source: https://leetcode.com/problems/number-of-ways-to-assign-edge-weights-ii
// Title: Number of Ways to Assign Edge Weights II
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There is an undirected tree with `n` nodes labeled from 1 to `n`, rooted at node 1. The tree is represented by a 2D integer array `edges` of length `n - 1`, where `edges[i] = [u_i, v_i]` indicates that there is an edge between nodes `u_i` and `v_i`.
//
// Initially, all edges have a weight of 0. You must assign each edge a weight of either **1** or **2**.
//
// The **cost** of a path between any two nodes `u` and `v` is the total weight of all edges in the path connecting them.
//
// You are given a 2D integer array `queries`. For each `queries[i] = [u_i, v_i]`, determine the number of ways to assign weights to edges **in the path** such that the cost of the path between `u_i` and `v_i` is **odd**.
//
// Return an array `answer`, where `answer[i]` is the number of valid assignments for `queries[i]`.
//
// Since the answer may be large, apply **modulo** `10^9 + 7` to each `answer[i]`.
//
// **Note:** For each query, disregard all edges **not** in the path between node `u_i` and `v_i`.
//
// **Example 1:**
//
// https://assets.leetcode.com/uploads/2025/03/23/screenshot-2025-03-24-at-060006.png
//
// ```
// Input: edges = [[1,2]], queries = [[1,1],[1,2]]
// Output: [0,1]
// Explanation:
// - Query `[1,1]`: The path from Node 1 to itself consists of no edges, so the cost is 0. Thus, the number of valid assignments is 0.
// - Query `[1,2]`: The path from Node 1 to Node 2 consists of one edge (`1 → 2`). Assigning weight 1 makes the cost odd, while 2 makes it even. Thus, the number of valid assignments is 1.
// ```
//
// **Example 2:**
//
// https://assets.leetcode.com/uploads/2025/03/23/screenshot-2025-03-24-at-055820.png
//
// ```
// Input: edges = [[1,2],[1,3],[3,4],[3,5]], queries = [[1,4],[3,4],[2,5]]
// Output: [2,1,4]
// Explanation:
// - Query `[1,4]`: The path from Node 1 to Node 4 consists of two edges (`1 → 3` and `3 → 4`). Assigning weights (1,2) or (2,1) results in an odd cost. Thus, the number of valid assignments is 2.
// - Query `[3,4]`: The path from Node 3 to Node 4 consists of one edge (`3 → 4`). Assigning weight 1 makes the cost odd, while 2 makes it even. Thus, the number of valid assignments is 1.
// - Query `[2,5]`: The path from Node 2 to Node 5 consists of three edges (`2 → 1, 1 → 3`, and `3 → 5`). Assigning (1,2,2), (2,1,2), (2,2,1), or (1,1,1) makes the cost odd. Thus, the number of valid assignments is 4.
// ```
//
// **Constraints:**
//
// - `2 <= n <= 10^5`
// - `edges.length == n - 1`
// - `edges[i] == [u_i, v_i]`
// - `1 <= queries.length <= 10^5`
// - `queries[i] == [u_i, v_i]`
// - `1 <= u_i, v_i <= n`
// - `edges` represents a valid tree.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <optional>
#include <vector>

using namespace std;

// DFS, TLE
//
// For each query pair, use DFS to find the path length.
//
// Say the length is l.
// The first l-1 edges can be choose randomly.
// The last edge has only one choice since the sum must be odd.
class Solution {
  constexpr static int64_t modulo = 1e9 + 7;

  using Bool = unsigned char;

  inline int64_t mod(int64_t x) {  //
    return ((x % modulo) + modulo) % modulo;
  }

  inline int64_t fastPow(int64_t x, int n) {  //
    int64_t res = 1;
    while (n > 0) {
      if (n % 2) res = mod(res * x);
      x = mod(x * x);
      n /= 2;
    }
    return res;
  }

  optional<int> dfs(int curr, int from, int dst, const vector<vector<int>>& graph) {
    for (int next : graph[curr]) {
      if (next == from) continue;
      if (next == dst) return 1;
      auto len = dfs(next, curr, dst, graph);
      if (len.has_value()) return *len + 1;
    }
    return nullopt;
  }

 public:
  vector<int> assignEdgeWeights(const vector<vector<int>>& edges, const vector<vector<int>>& queries) {
    const int n = edges.size() + 1;

    // Build graph
    auto graph = vector<vector<int>>(n);
    for (const auto& edge : edges) {
      int u = edge[0] - 1, v = edge[1] - 1;
      graph[u].push_back(v);
      graph[v].push_back(u);
    }

    // DFS
    auto ans = vector<int>();
    ans.reserve(queries.size());
    for (auto& query : queries) {
      const int u = query[0] - 1, v = query[1] - 1;
      int length = *dfs(u, -1, v, graph);
      ans.push_back(length == 0 ? 0 : fastPow(2, length - 1));
    }

    // Answer
    return ans;
  }
};

// LCA
//
// Init LCA for the tree.
// For each query pair, use LCA to find the path length.
//
// Say the length is l.
// The first l-1 edges can be choose randomly.
// The last edge has only one choice since the sum must be odd.
class Solution2 {
  constexpr static int root = 0;
  constexpr static int64_t modulo = 1e9 + 7;

  using Bool = unsigned char;

  inline int64_t mod(int64_t x) {  //
    return ((x % modulo) + modulo) % modulo;
  }

  inline int64_t fastPow(int64_t x, int n) {  //
    int64_t res = 1;
    while (n > 0) {
      if (n % 2) res = mod(res * x);
      x = mod(x * x);
      n /= 2;
    }
    return res;
  }

  class LCA {
    int n;
    int logn;
    vector<vector<int>> up;  // up[u][k] = 2^k level ancestor of u
    vector<int> depth;

   private:
    void dfs(int u, int parent, int d, const vector<vector<int>>& graph) {
      up[u][0] = parent;
      depth[u] = d;

      for (int k = 1; k < logn; ++k) {
        up[u][k] = up[up[u][k - 1]][k - 1];
      }

      for (int v : graph[u]) {
        if (v == parent) continue;
        dfs(v, u, d + 1, graph);
      }
    }

   public:
    // Build: O(NlogN)
    LCA(const vector<vector<int>>& graph) {
      n = graph.size();
      logn = bit_width(size_t(n));  // = floor(log2(n))+1
      up.assign(n, vector<int>(logn, root));
      depth.resize(n);

      dfs(root, root, 0, graph);
    }

    // Find: O(logN)
    int length(int u, int v) const {
      int length = depth[u] + depth[v];

      // Ensure depth(u) >= depth(v)
      if (depth[u] <= depth[v]) swap(u, v);

      // Lift u to the same depth of v
      int diff = depth[u] - depth[v];
      for (int k = 0; k < logn; ++k) {
        if ((diff >> k) & 1) u = up[u][k];
      }

      // Early exit
      if (u == v) return length - 2 * depth[u];

      // Jump up together
      for (int k = logn - 1; k >= 0; --k) {
        if (up[u][k] != up[v][k]) {
          u = up[u][k];
          v = up[v][k];
        }
      }

      return length - 2 * depth[up[u][0]];
    }
  };

 public:
  vector<int> assignEdgeWeights(const vector<vector<int>>& edges, const vector<vector<int>>& queries) {
    const int n = edges.size() + 1;

    // Build graph
    auto graph = vector<vector<int>>(n);
    for (const auto& edge : edges) {
      int u = edge[0] - 1, v = edge[1] - 1;
      graph[u].push_back(v);
      graph[v].push_back(u);
    }

    // Init LCA
    auto lca = LCA(graph);

    // Query
    auto ans = vector<int>();
    ans.reserve(queries.size());
    for (auto& query : queries) {
      const int u = query[0] - 1, v = query[1] - 1;
      int length = lca.length(u, v);
      ans.push_back(length == 0 ? 0 : fastPow(2, length - 1));
    }

    // Answer
    return ans;
  }
};

// Euler Tour + Sparse Table
//
// Traverse the tree using Euler tour,
// tracking the inward & outward for each node and its depth.
// Also track the first occurring index for each node.
//
// For each query pair (u, v), LCA is the first node with the minimal depth in the range [first(u), first(v)].
// We use sparse table to store the minimal depth.
class Solution3 {
  constexpr static int root = 0;
  constexpr static int64_t modulo = 1e9 + 7;

  using Bool = unsigned char;

  inline int64_t mod(int64_t x) {  //
    return ((x % modulo) + modulo) % modulo;
  }

  inline int64_t fastPow(int64_t x, int n) {  //
    int64_t res = 1;
    while (n > 0) {
      if (n % 2) res = mod(res * x);
      x = mod(x * x);
      n /= 2;
    }
    return res;
  }

  // Stores the minimal
  class SparseTable {
    int n;
    vector<vector<int>> table;  // table[i][j] = min of [i, i+2^j)
    vector<int> logs;           // precompute logs

   public:
    // Build, O(NlogN)
    SparseTable(const vector<int>& nums) {
      n = nums.size();
      int logn = bit_width(size_t(n));  // floor(log(n)) + 1

      table.assign(n, vector<int>(logn));
      logs.assign(n + 1, 0);

      // Precompute logs (floor value)
      for (int i = 2; i <= n; ++i) {
        logs[i] = logs[i / 2] + 1;
      }

      // Initialize table layer 0
      for (int i = 0; i < n; ++i) {
        table[i][0] = nums[i];
      }

      // Fill the table
      for (int j = 1; j < logn; ++j) {
        for (int i = 0; i + (1 << j) <= n; ++i) {
          table[i][j] = min(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
        }
      }
    }

    // Query: O(1); Min in [l, r)
    int query(int l, int r) const {
      int j = logs[r - l];
      return min(table[l][j], table[r - (1 << j)][j]);
    }
  };

  struct EulerTour {
    int n;
    vector<int> euler;  // nodes on euler tour
    vector<int> depth;  // depths on euler tour
    vector<int> first;  // first occurring index

    void dfs(int u, int parent, int d, const vector<vector<int>>& graph) {
      if (first[u] == -1) first[u] = euler.size();
      euler.push_back(u);
      depth.push_back(d);
      for (int v : graph[u]) {
        if (v == parent) continue;
        dfs(v, u, d + 1, graph);
        euler.push_back(u);
        depth.push_back(d);
      }
    }

    EulerTour(const vector<vector<int>>& graph) : n(graph.size()), euler(), depth(), first(n, -1) {
      euler.reserve(2 * n - 1);
      depth.reserve(2 * n - 1);
      dfs(root, root, 0, graph);
    }
  };

 public:
  vector<int> assignEdgeWeights(const vector<vector<int>>& edges, const vector<vector<int>>& queries) {
    const int n = edges.size() + 1;

    // Build graph
    auto graph = vector<vector<int>>(n);
    for (const auto& edge : edges) {
      int u = edge[0] - 1, v = edge[1] - 1;
      graph[u].push_back(v);
      graph[v].push_back(u);
    }

    // Init data structure
    auto tour = EulerTour(graph);
    auto st = SparseTable(tour.depth);

    // Query
    auto ans = vector<int>();
    ans.reserve(queries.size());
    for (auto& query : queries) {
      const int u = query[0] - 1, v = query[1] - 1;

      int iu = tour.first[u], iv = tour.first[v];
      if (iu > iv) swap(iu, iv);  // Ensure u is before v

      int lcaDepth = st.query(iu, iv + 1);
      int length = tour.depth[iu] + tour.depth[iv] - 2 * lcaDepth;
      ans.push_back(length == 0 ? 0 : fastPow(2, length - 1));
    }

    // Answer
    return ans;
  }
};
