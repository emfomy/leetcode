// Source: https://leetcode.com/problems/minimum-score-of-a-path-between-two-cities
// Title: Minimum Score of a Path Between Two Cities
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a positive integer `n` representing `n` cities numbered from `1` to `n`. You are also given a **2D** array `roads` where `roads[i] = [a_i, b_i, distance_i]` indicates that there is a **bidirectional **road between cities `a_i` and `b_i` with a distance equal to `distance_i`. The cities graph is not necessarily connected.
//
// The **score** of a path between two cities is defined as the **minimum **distance of a road in this path.
//
// Return the **minimum **possible score of a path between cities `1` and `n`.
//
// **Note**:
//
// - A path is a sequence of roads between two cities.
// - It is allowed for a path to contain the same road **multiple** times, and you can visit cities `1` and `n` multiple times along the path.
// - The test cases are generated such that there is **at least** one path between `1` and `n`.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2022/10/12/graph11.png
//
// ```
// Input: n = 4, roads = [[1,2,9],[2,3,6],[2,4,5],[1,4,7]]
// Output: 5
// Explanation: The path from city 1 to 4 with the minimum score is: 1 -> 2 -> 4. The score of this path is min(9,5) = 5.
// It can be shown that no other path has less score.
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2022/10/12/graph22.png
//
// ```
// Input: n = 4, roads = [[1,2,2],[1,3,4],[3,4,7]]
// Output: 2
// Explanation: The path from city 1 to 4 with the minimum score is: 1 -> 2 -> 1 -> 3 -> 4. The score of this path is min(2,2,4,7) = 2.
// ```
//
// **Constraints:**
//
// - `2 <= n <= 10^5`
// - `1 <= roads.length <= 10^5`
// - `roads[i].length == 3`
// - `1 <= a_i, b_i <= n`
// - `a_i != b_i`
// - `1 <= distance_i <= 10^4`
// - There are no repeated edges.
// - There is at least one path between `1` and `n`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <climits>
#include <numeric>
#include <vector>

using namespace std;

// Union-Find
//
// Since we are allowed to visit a path multiple time,
// the minimal score is equal to the shortest road which is connected to the city 1.
//
// We use union-find to remove the disconnected roads.
class Solution {
  struct UnionFind {
    vector<int> parents;
    vector<int> sizes;

    UnionFind(int n) : parents(n), sizes(n, 0) {  //
      iota(parents.begin(), parents.end(), 0);
    }

    bool isConnected(int x, int y) {  //
      return find(x) == find(y);
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

      // Ensure rank(x) >= rank(y)
      if (sizes[x] < sizes[y]) swap(x, y);

      // Merge y into x
      if (sizes[x] == sizes[y]) ++sizes[x];
      parents[y] = x;
    }
  };

 public:
  int minScore(const int n, const vector<vector<int>>& roads) {
    // Union-Find
    auto uf = UnionFind(n);
    for (const auto& road : roads) {
      int x = road[0] - 1, y = road[1] - 1;  // convert to 0-indexed
      uf.unite(x, y);
    }

    // Find shortest road
    int minCost = INT_MAX;
    for (const auto& road : roads) {
      int x = road[0] - 1, y = road[1] - 1, dist = road[2];  // convert to 0-indexed
      if (uf.isConnected(0, x)) {
        minCost = min(minCost, dist);
      }
    }

    return minCost;
  }
};
