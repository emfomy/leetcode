// Source: https://leetcode.com/problems/count-the-number-of-complete-components
// Title: Count the Number of Complete Components
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer `n`. There is an **undirected** graph with `n` vertices, numbered from `0` to `n - 1`. You are given a 2D integer array `edges` where `edges[i] = [a_i, b_i]` denotes that there exists an **undirected** edge connecting vertices `a_i` and `b_i`.
//
// Return the number of **complete connected components** of the graph.
//
// A **connected component** is a subgraph of a graph in which there exists a path between any two vertices, and no vertex of the subgraph shares an edge with a vertex outside of the subgraph.
//
// A connected component is said to be **complete** if there exists an edge between every pair of its vertices.
//
// **Example 1:**
//
// **https://assets.leetcode.com/uploads/2023/04/11/screenshot-from-2023-04-11-23-31-23.png**
//
// ```
// Input: n = 6, edges = [[0,1],[0,2],[1,2],[3,4]]
// Output: 3
// Explanation: From the picture above, one can see that all of the components of this graph are complete.
// ```
//
// **Example 2:**
//
// **https://assets.leetcode.com/uploads/2023/04/11/screenshot-from-2023-04-11-23-32-00.png**
//
// ```
// Input: n = 6, edges = [[0,1],[0,2],[1,2],[3,4],[3,5]]
// Output: 1
// Explanation: The component containing vertices 0, 1, and 2 is complete since there is an edge between every pair of two vertices. On the other hand, the component containing vertices 3, 4, and 5 is not complete since there is no edge between vertices 4 and 5. Thus, the number of complete components in this graph is 1.
// ```
//
// **Constraints:**
//
// - `1 <= n <= 50`
// - `0 <= edges.length <= n * (n - 1) / 2`
// - `edges[i].length == 2`
// - `0 <= a_i, b_i <= n - 1`
// - `a_i != b_i`
// - There are no repeated edges.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <numeric>
#include <vector>

using namespace std;

// Union-Find
//
// Use Union-Find to find the components.
// Count the degree of each node.
//
// Assume all component to be complete.
// For each nodes `x`, find its root `p` and get the component size.
// If the deg(x)+1 != size(p), then this component is not complete.
class Solution {
  struct UnionFind {
    vector<int> parents;
    vector<int> sizes;

    UnionFind(int n) : parents(n), sizes(n, 1) {  //
      iota(parents.begin(), parents.end(), 0);
    }

    bool isRoot(const int x) {  //
      return x == find(x);
    }

    int find(const int x) {
      if (parents[x] != x) {
        parents[x] = find(parents[x]);
      }
      return parents[x];
    }

    void unite(int x, int y) {
      x = find(x);
      y = find(y);
      if (x == y) return;

      // Ensure size(x) >= size(y)
      if (sizes[x] < sizes[y]) swap(x, y);

      // Merge y into x
      sizes[x] += sizes[y];
      parents[y] = x;
    }
  };

 public:
  int countCompleteComponents(const int n, const vector<vector<int>>& edges) {
    // Union-Find & Count degrees
    auto uf = UnionFind(n);
    auto degrees = vector<int>(n);
    for (const auto& edge : edges) {
      int x = edge[0], y = edge[1];
      uf.unite(x, y);
      ++degrees[x];
      ++degrees[y];
    }

    // Check completeness
    auto isComplete = vector<bool>(n, true);
    for (int x = 0; x < n; ++x) {
      int p = uf.find(x);  // find root
      if (degrees[x] + 1 != uf.sizes[p]) {
        isComplete[p] = false;  // x has too less edge
      }
    }

    // Count complete component
    int numComplete = 0;
    for (int p = 0; p < n; ++p) {
      if (uf.isRoot(p) && isComplete[p]) ++numComplete;
    }

    return numComplete;
  }
};
