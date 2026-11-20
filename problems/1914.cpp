// Source: https://leetcode.com/problems/cyclically-rotating-a-grid
// Title: Cyclically Rotating a Grid
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an `m x n` integer matrix `grid`, where `m` and `n` are both **even** integers, and an integer `k`.
//
// The matrix is composed of several layers, which is shown in the below image, where each color is its own layer:
//
// https://assets.leetcode.com/uploads/2021/06/10/ringofgrid.png
//
// A cyclic rotation of the matrix is done by cyclically rotating **each layer** in the matrix. To cyclically rotate a layer once, each element in the layer will take the place of the adjacent element in the **counter-clockwise** direction. An example rotation is shown below:
// https://assets.leetcode.com/uploads/2021/06/22/explanation_grid.jpg
// Return the matrix after applying `k` cyclic rotations to it.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/06/19/rod2.png
//
// ```
// Input: grid = [[40,10],[30,20]], k = 1
// Output: [[10,20],[40,30]]
// Explanation: The figures above represent the grid at every state.
// ```
//
// **Example 2:**
// **https://assets.leetcode.com/uploads/2021/06/10/ringofgrid5.png** **https://assets.leetcode.com/uploads/2021/06/10/ringofgrid6.png** **https://assets.leetcode.com/uploads/2021/06/10/ringofgrid7.png**
//
// ```
// Input: grid = [[1,2,3,4],[5,6,7,8],[9,10,11,12],[13,14,15,16]], k = 2
// Output: [[3,4,8,12],[2,11,10,16],[1,7,6,15],[5,9,13,14]]
// Explanation: The figures above represent the grid at every state.
// ```
//
// **Constraints:**
//
// - `m == grid.length`
// - `n == grid[i].length`
// - `2 <= m, n <= 50`
// - Both `m` and `n` are **even** integers.
// - `1 <= grid[i][j] <=^ 5000`
// - `1 <= k <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// In-Place
//
// For each layer, we modulo k by the layer length.
// Next since the layer length is small, we simply run the rotation k times.
class Solution {
 public:
  vector<vector<int>> rotateGrid(vector<vector<int>>& grid, int k) {
    const int m = grid.size(), n = grid[0].size();
    const int mn2 = min(m / 2, n / 2);

    int perimeter = 2 * (m + n) - 4;
    for (int l = 0; l < mn2; ++l) {
      int kl = k % (perimeter - 8 * l);

      for (int t = 0; t < kl; ++t) {
        const int i0 = l, i1 = m - l - 1;
        const int j0 = l, j1 = n - l - 1;

        int tmp = grid[i0][j0];

        // Top
        for (int j = j0; j < j1; ++j) {
          grid[i0][j] = grid[i0][j + 1];
        }

        // Right
        for (int i = i0; i < i1; ++i) {
          grid[i][j1] = grid[i + 1][j1];
        }

        // Bottom
        for (int j = j1; j > j0; --j) {
          grid[i1][j] = grid[i1][j - 1];
        }

        // Left
        for (int i = i1; i > i0; --i) {
          grid[i][j0] = grid[i - 1][j0];
        }

        grid[i0 + 1][j0] = tmp;
      }
    }

    return grid;
  }
};

// Auxiliary space
//
// Copy the layer to an auxiliary vector, and write back.
class Solution2 {
 public:
  vector<vector<int>> rotateGrid(vector<vector<int>>& grid, int k) {
    const int m = grid.size(), n = grid[0].size();
    const int mn2 = min(m / 2, n / 2);

    int perimeter = 2 * (m + n) - 4;
    auto temp = vector<int>(perimeter);

    for (int l = 0; l < mn2; ++l) {
      const int p = perimeter - 8 * l;
      const int i0 = l, i1 = m - l - 1;
      const int j0 = l, j1 = n - l - 1;

      // Read to temp
      int idx = 0;
      for (int j = j0; j < j1; ++j, ++idx) temp[idx] = grid[i0][j];
      for (int i = i0; i < i1; ++i, ++idx) temp[idx] = grid[i][j1];
      for (int j = j1; j > j0; --j, ++idx) temp[idx] = grid[i1][j];
      for (int i = i1; i > i0; --i, ++idx) temp[idx] = grid[i][j0];

      // Write from temp
      idx = k % p;
      for (int j = j0; j < j1; ++j, ++idx) grid[i0][j] = temp[idx % p];
      for (int i = i0; i < i1; ++i, ++idx) grid[i][j1] = temp[idx % p];
      for (int j = j1; j > j0; --j, ++idx) grid[i1][j] = temp[idx % p];
      for (int i = i1; i > i0; --i, ++idx) grid[i][j0] = temp[idx % p];
    }

    return grid;
  }
};
