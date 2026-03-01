// Source: https://leetcode.com/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance
// Title: Find the City With the Smallest Number of Neighbors at a Threshold Distance
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There are `n` cities numbered from `0` to `n-1`. Given the array `edges` where `edges[i] = [from_i, to_i, weight_i]` represents a bidirectional and weighted edge between cities `from_i` and `to_i`, and given the integer `distanceThreshold`.
//
// Return the city with the smallest number of cities that are reachable through some path and whose distance is **at most** `distanceThreshold`, If there are multiple such cities, return the city with the greatest number.
//
// Notice that the distance of a path connecting cities **i** and **j** is equal to the sum of the edges' weights along that path.
//
// **Example 1:**
//
// https://assets.leetcode.com/uploads/2024/08/23/problem1334example1.png
//
// ```
// Input: n = 4, edges = [[0,1,3],[1,2,1],[1,3,4],[2,3,1]], distanceThreshold = 4
// Output: 3
// Explanation: The figure above describes the graph.
// The neighboring cities at a distanceThreshold = 4 for each city are:
// City 0 -> [City 1, City 2]
// City 1 -> [City 0, City 2, City 3]
// City 2 -> [City 0, City 1, City 3]
// City 3 -> [City 1, City 2]
// Cities 0 and 3 have 2 neighboring cities at a distanceThreshold = 4, but we have to return city 3 since it has the greatest number.
// ```
//
// **Example 2:**
//
// https://assets.leetcode.com/uploads/2024/08/23/problem1334example0.png
//
// ```
// Input: n = 5, edges = [[0,1,2],[0,4,8],[1,2,3],[1,4,2],[2,3,1],[3,4,1]], distanceThreshold = 2
// Output: 0
// Explanation: The figure above describes the graph.
// The neighboring cities at a distanceThreshold = 2 for each city are:
// City 0 -> [City 1]
// City 1 -> [City 0, City 4]
// City 2 -> [City 3, City 4]
// City 3 -> [City 2, City 4]
// City 4 -> [City 1, City 2, City 3]
// The city 0 has 1 neighboring city at a distanceThreshold = 2.
// ```
//
// **Constraints:**
//
// - `2 <= n <= 100`
// - `1 <= edges.length <= n * (n - 1) / 2`
// - `edges[i].length == 3`
// - `0 <= from_i < to_i < n`
// - `1 <= weight_i,distanceThreshold <= 10^4`
// - All pairs `(from_i, to_i)` are distinct.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <climits>
#include <vector>

using namespace std;

// Floyd-Warshall, O(N^3)
class Solution {
  constexpr static int kInf = INT_MAX / 2;

 public:
  int findTheCity(int n, const vector<vector<int>>& edges, int distanceThreshold) {
    // Guard
    if (n < 0) return 0;

    // Init graph
    auto dists = vector<vector<int>>(n, vector<int>(n, kInf));
    for (int i = 0; i < n; ++i) dists[i][i] = 0;
    for (const auto& edge : edges) {
      int u = edge[0], v = edge[1], w = edge[2];
      dists[u][v] = min(dists[u][v], w);
      dists[v][u] = min(dists[v][u], w);
    }

    // Floyd-Warshall
    for (int k = 0; k < n; ++k) {
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          dists[i][j] = min(dists[i][j], dists[i][k] + dists[k][j]);
        }
      }
    }

    // Count threshold
    int minNode = -1;
    int minCount = n;
    auto cond = [distanceThreshold](int dist) { return dist <= distanceThreshold; };
    for (int i = 0; i < n; ++i) {
      // Here we also count self node (doesn't change the result)
      int count = count_if(dists[i].cbegin(), dists[i].cend(), cond);
      if (minCount >= count) {  // use equal sign since we want the largest node ID
        minCount = count;
        minNode = i;
      }
    }

    return minNode;
  }
};
