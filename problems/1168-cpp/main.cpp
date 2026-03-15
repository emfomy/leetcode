// Source: https://leetcode.com/problems/optimize-water-distribution-in-a-village
// Title: Optimize Water Distribution in a Village
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There are `n` houses in a village. We want to supply water for all the houses by building wells and laying pipes.
//
// For each house `i`, we can either build a well inside it directly with cost `wells[i - 1]` (note the `-1` due to **0-indexing**), or pipe in water from another well to it. The costs to lay pipes between houses are given by the array `pipes` where each `pipes[j] = [house1_j, house2_j, cost_j]` represents the cost to connect `house1_j` and `house2_j` together using a pipe. Connections are bidirectional, and there could be multiple valid connections between the same two houses with different costs.
//
// Return the minimum total cost to supply water to all houses.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2019/05/22/1359_ex1.png
//
// ```
// Input: n = 3, wells = [1,2,2], pipes = [[1,2,1],[2,3,1]]
// Output: 3
// Explanation: The image shows the costs of connecting houses using pipes.
// The best strategy is to build a well in the first house with cost 1 and connect the other houses to it with cost 2 so the total cost is 3.
// ```
//
// **Example 2:**
//
// ```
// Input: n = 2, wells = [1,1], pipes = [[1,2,1],[1,2,2]]
// Output: 2
// Explanation: We can supply water with cost two using one of the three options:
// Option 1:
//   - Build a well inside house 1 with cost 1.
//   - Build a well inside house 2 with cost 1.
// The total cost will be 2.
// Option 2:
//   - Build a well inside house 1 with cost 1.
//   - Connect house 2 with house 1 with cost 1.
// The total cost will be 2.
// Option 3:
//   - Build a well inside house 2 with cost 1.
//   - Connect house 1 with house 2 with cost 1.
// The total cost will be 2.
// Note that we can connect houses 1 and 2 with cost 1 or with cost 2 but we will always choose **the cheapest option**.
// ```
//
// **Constraints:**
//
// - `2 <= n <= 10^4`
// - `wells.length == n`
// - `0 <= wells[i] <= 10^5`
// - `1 <= pipes.length <= 10^4`
// - `pipes[j].length == 3`
// - `1 <= house1_j, house2_j <= n`
// - `0 <= cost_j <= 10^5`
// - `house1_j != house2_j`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <numeric>
#include <vector>

using namespace std;

// Kruskal (Union Find + Sort)
//
// We can add a virtual node (water source).
// The cost of each well is the weight of between the each house and the water source.
// The cost of each pipe is the weight of between the houses.
//
// Now the problem becomes the MST of this new graph.
class Solution {
  struct UnionFind {
    mutable vector<int> parents;
    mutable vector<int> ranks;
    int count;  // connected components

   public:
    UnionFind(int n) : parents(n), ranks(n), count(n) {  //
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

      // Ensure ranks(x) >= ranks(y)
      if (ranks[x] <= ranks[y]) swap(x, y);

      // Merge y into x
      if (ranks[x] == ranks[y]) ++ranks[x];
      parents[y] = x;
      --count;
    }
  };

  using Edge = tuple<int, int, int>;  // weight, node, node

 public:
  int minCostToSupplyWater(const int n, const vector<int>& wells, const vector<vector<int>>& pipes) {
    const int m = pipes.size();

    // Build graph
    auto edges = vector<Edge>();
    edges.reserve(n + m);
    for (int u = 0; u < n; ++u) {
      edges.emplace_back(wells[u], 0, u + 1);
    }
    for (const auto& pipe : pipes) {
      int u = pipe[0], v = pipe[1], w = pipe[2];
      edges.emplace_back(w, u, v);
    }

    // Sort edges
    sort(edges.begin(), edges.end());

    // Union Find
    auto uf = UnionFind(n + 1);  // includes the virtual node
    int mstWeight = 0;
    for (const auto [w, u, v] : edges) {
      // Early stop
      if (uf.count == 1) break;

      // Merge
      if (uf.isConnected(u, v)) continue;
      uf.unite(u, v);
      mstWeight += w;
    }

    return mstWeight;
  }
};
