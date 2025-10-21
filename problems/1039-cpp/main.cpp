// Source: https://leetcode.com/problems/minimum-score-triangulation-of-polygon
// Title: Minimum Score Triangulation of Polygon
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You have a convex `n`-sided polygon where each vertex has an integer value. You are given an integer array `values` where `values[i]` is the value of the `i^th` vertex in **clockwise order**.
//
// **Polygon triangulation** is a process where you divide a polygon into a set of triangles and the vertices of each triangle must also be vertices of the original polygon. Note that no other shapes other than triangles are allowed in the division. This process will result in `n - 2` triangles.
//
// You will **triangulate** the polygon. For each triangle, the weight of that triangle is the product of the values at its vertices. The total score of the triangulation is the sum of these weights over all `n - 2` triangles.
//
// Return the minimum possible score that you can achieve with some **triangulation** of the polygon.
//
// **Example 1:**
//
// http://127.0.0.1:49174/shape1.jpg
//
// ```
// Input: values = [1,2,3]
// Output: 6
// Explanation: The polygon is already triangulated, and the score of the only triangle is 6.
// ```
//
// **Example 2:**
//
// http://127.0.0.1:49174/shape2.jpg
//
// ```
// Input: values = [3,7,4,5]
// Output: 144
// Explanation: There are two triangulations, with possible scores: 3*7*5 + 4*5*7 = 245, or 3*4*5 + 3*4*7 = 144.
// The minimum score is 144.
// ```
//
// **Example 3:**
//
// http://127.0.0.1:49174/shape3.jpg
//
// ```
// Input: values = [1,3,1,4,1,5]
// Output: 13
// Explanation: The minimum score triangulation is 1*1*3 + 1*1*4 + 1*1*5 + 1*1*1 = 13.
// ```
//
// **Constraints:**
//
// - `n == values.length`
// - `3 <= n <= 50`
// - `1 <= values[i] <= 100`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <climits>
#include <functional>
#include <unordered_map>
#include <vector>

using namespace std;

// Divide and Conquer + Memo
//
// Let DP[i, j] be the minimal score of vertices [i, ..., j]
//
// We know that edge (i, j) must be an edge of an triangle.
// We loop though k = i+1, ..., j-1, and form (i, j, k) as an triangle.
// We divide the problem into two subproblems DP[i, k] & DP[k, j]
class Solution {
 public:
  int minScoreTriangulation(vector<int>& values) {
    int n = values.size();

    auto memo = unordered_map<int, int>();

    function<int(int, int)> dp = [&](int i, int j) {
      // Impossible
      if (i + 2 > j) return 0;

      // Already triangle
      if (i + 2 == j) return values[i] * values[i + 1] * values[i + 2];

      // Read memo
      int key = i * n + j;
      if (memo.count(key)) return memo[key];

      // Loop
      auto score = INT_MAX;
      for (auto k = i + 1; k < j; ++k) {
        score = min(score, values[i] * values[j] * values[k] + dp(i, k) + dp(k, j));
      }

      // Write memo
      memo[key] = score;

      return score;
    };

    return dp(0, n - 1);
  }
};
