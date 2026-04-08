// Source: https://leetcode.com/problems/min-cost-to-connect-all-points
// Title: Min Cost to Connect All Points
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an array `points` representing integer coordinates of some points on a 2D-plane, where `points[i] = [x_i, y_i]`.
//
// The cost of connecting two points `[x_i, y_i]` and `[x_j, y_j]` is the **manhattan distance** between them: `|x_i - x_j| + |y_i - y_j|`, where `|val|` denotes the absolute value of `val`.
//
// Return the minimum cost to make all points connected. All points are connected if there is **exactly one** simple path between any two points.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2020/08/26/d.png
//
// ```
// Input: points = [[0,0],[2,2],[3,10],[5,2],[7,0]]
// Output: 20
// Explanation:
// https://assets.leetcode.com/uploads/2020/08/26/c.png
// We can connect the points as shown above to get the minimum cost of 20.
// Notice that there is a unique path between every pair of points.
// ```
//
// **Example 2:**
//
// ```
// Input: points = [[3,12],[-2,5],[-4,1]]
// Output: 18
// ```
//
// **Constraints:**
//
// - `1 <= points.length <= 1000`
// - `-10^6 <= x_i, y_i <= 10^6`
// - All pairs `(x_i, y_i)` are distinct.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <climits>
#include <vector>

using namespace std;

// Dense Prim's algorithm
//
// Use Prim's algorithm to find the MST.
class Solution {
  using Bool = unsigned char;

  int getDist(const vector<int>& u, const vector<int>& v) {  //
    return abs(u[0] - v[0]) + abs(u[1] - v[1]);
  }

 public:
  int minCostConnectPoints(const vector<vector<int>>& points) {
    const int n = points.size();

    // Prepare
    auto visited = vector<Bool>(n);
    auto dists = vector<int>(n, INT_MAX);
    dists[0] = 0;

    // Loop
    int mstWeight = 0;
    for (int iter = 0; iter < n; ++iter) {
      // Find nearest point
      int u = min_element(dists.cbegin(), dists.cend()) - dists.cbegin();

      // Add into graph
      mstWeight += dists[u];
      visited[u] = true;
      dists[u] = INT_MAX;  // remove from target set

      // Update neighbor
      for (int v = 0; v < n; ++v) {
        if (visited[v]) continue;
        dists[v] = min(dists[v], getDist(points[u], points[v]));
      }
    }

    return mstWeight;
  }
};
