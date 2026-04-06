// Source: https://leetcode.com/problems/projection-area-of-3d-shapes
// Title: Projection Area of 3D Shapes
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an `n x n` `grid` where we place some `1 x 1 x 1` cubes that are axis-aligned with the `x`, `y`, and `z` axes.
//
// Each value `v = grid[i][j]` represents a tower of `v` cubes placed on top of the cell `(i, j)`.
//
// We view the projection of these cubes onto the `xy`, `yz`, and `zx` planes.
//
// A **projection** is like a shadow, that maps our **3-dimensional** figure to a **2-dimensional** plane. We are viewing the "shadow" when looking at the cubes from the top, the front, and the side.
//
// Return the total area of all three projections.
//
// **Example 1:**
// https://s3-lc-upload.s3.amazonaws.com/uploads/2018/08/02/shadow.png
//
// ```
// Input: grid = [[1,2],[3,4]]
// Output: 17
// Explanation: Here are the three projections ("shadows") of the shape made with each axis-aligned plane.
// ```
//
// **Example 2:**
//
// ```
// Input: grid = [[2]]
// Output: 5
// ```
//
// **Example 3:**
//
// ```
// Input: grid = [[1,0],[0,2]]
// Output: 8
// ```
//
// **Constraints:**
//
// - `n == grid.length == grid[i].length`
// - `1 <= n <= 50`
// - `0 <= grid[i][j] <= 50`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

class Solution {
 public:
  int projectionArea(const vector<vector<int>>& grid) {
    const int n = grid.size();
    int ans = 0;

    // xy-plane
    for (int x = 0; x < n; ++x) {
      for (int y = 0; y < n; ++y) {
        ans += int(grid[x][y] > 0);
      }
    }

    // xz-plane
    for (int x = 0; x < n; ++x) {
      int xMax = 0;
      for (int y = 0; y < n; ++y) {
        xMax = max(xMax, grid[x][y]);
      }
      ans += xMax;
    }

    // yz-plane
    for (int y = 0; y < n; ++y) {
      int yMax = 0;
      for (int x = 0; x < n; ++x) {
        yMax = max(yMax, grid[x][y]);
      }
      ans += yMax;
    }

    return ans;
  }
};
