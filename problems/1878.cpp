// Source: https://leetcode.com/problems/get-biggest-three-rhombus-sums-in-a-grid
// Title: Get Biggest Three Rhombus Sums in a Grid
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an `m x n` integer matrix `grid`.
//
// A **rhombus sum** is the sum of the elements that form **the** **border** of a regular rhombus shape in `grid`. The rhombus must have the shape of a square rotated 45 degrees with each of the corners centered in a grid cell. Below is an image of four valid rhombus shapes with the corresponding colored cells that should be included in each **rhombus sum**:
// https://assets.leetcode.com/uploads/2021/04/23/pc73-q4-desc-2.png
// Note that the rhombus can have an area of 0, which is depicted by the purple rhombus in the bottom right corner.
//
// Return the biggest three **distinct rhombus sums** in the `grid` in **descending order**. If there are less than three distinct values, return all of them.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/04/23/pc73-q4-ex1.png
//
// ```
// Input: grid = [[3,4,5,1,3],[3,3,4,2,3],[20,30,200,40,10],[1,5,5,4,1],[4,3,2,2,5]]
// Output: [228,216,211]
// Explanation: The rhombus shapes for the three biggest distinct rhombus sums are depicted above.
// - Blue: 20 + 3 + 200 + 5 = 228
// - Red: 200 + 2 + 10 + 4 = 216
// - Green: 5 + 200 + 4 + 2 = 211
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2021/04/23/pc73-q4-ex2.png
//
// ```
// Input: grid = [[1,2,3],[4,5,6],[7,8,9]]
// Output: [20,9,8]
// Explanation: The rhombus shapes for the three biggest distinct rhombus sums are depicted above.
// - Blue: 4 + 2 + 6 + 8 = 20
// - Red: 9 (area 0 rhombus in the bottom right corner)
// - Green: 8 (area 0 rhombus in the bottom middle)
// ```
//
// **Example 3:**
//
// ```
// Input: grid = [[7,7,7]]
// Output: [7]
// Explanation: All three possible rhombus sums are the same, so return [7].
// ```
//
// **Constraints:**
//
// - `m == grid.length`
// - `n == grid[i].length`
// - `1 <= m, n <= 50`
// - `1 <= grid[i][j] <= 10^5`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <array>
#include <functional>
#include <set>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

// Prefix Sum + Tree Set
//
// We compute the prefix sum of each diagonal and anti-diagonals.
// Diag[i+1, j+1] is the sum of a diagonal,      start at top left and end at (i, j) (including)
// Anti[i+1, j  ] is the sum of a anti-diagonal, start at top right and end at (i, j) (including)
// Diag[i+1, j+1] = Diag[i, j  ] + Grid[i, j]
// Anti[i+1, j  ] = Anti[i, j+1] + Grid[i, j]
//
// Now we can compute all rhombuses.
// For an rhombus with top corner (i, ?) and right corner (?, j) and size l.
// Let x0 = i-l, x1 = i, x2 = i+l;
// Let y0 = j-l, y1 = j, y2 = j+l.
// The four corners are (x0, y1), (x1, y2), (x2, y1), (x1, y0).
// The top-right    edge is [ (x0, y1), (x1, y2) )
// The bottom-right edge is [ (x1, y2), (x2, y1) )
// The bottom-left  edge is ( (x1, y0), (x2, y1) ]
// The top-left     edge is ( (x0, y1), (x1, y0) ]
class Solution {
 public:
  vector<int> getBiggestThree(const vector<vector<int>>& grid) {
    const int m = grid.size(), n = grid[0].size();
    const int mn = min(m, n);

    // Prefix Sum
    auto diag = vector<vector<int>>(m + 1, vector<int>(n + 1));
    auto anti = vector<vector<int>>(m + 1, vector<int>(n + 1));
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        diag[i + 1][j + 1] = diag[i][j] + grid[i][j];
      }
      for (int j = n - 1; j >= 0; --j) {
        anti[i + 1][j] = anti[i][j + 1] + grid[i][j];
      }
    }

    // Loop for l=0
    set<int> sums;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        sums.insert(grid[i][j]);
        while (sums.size() > 3) sums.erase(sums.cbegin());
      }
    }

    // Loop for l>0
    for (int l = 1; l <= mn / 2; ++l) {
      for (int i = l; i < m - l; ++i) {
        for (int j = l; j < n - l; ++j) {
          int x0 = i - l, x1 = i, x2 = i + l;
          int y0 = j - l, y1 = j, y2 = j + l;
          int sum = diag[x1 + 0][y2 + 0] - diag[x0 + 0][y1 + 0] +  // top right
                    anti[x2 + 0][y1 + 1] - anti[x1 + 0][y2 + 1] +  // bottom right
                    diag[x2 + 1][y1 + 1] - diag[x1 + 1][y0 + 1] +  // bottom left
                    anti[x1 + 1][y0 + 0] - anti[x0 + 1][y1 + 0];   // top left
          sums.insert(sum);
          while (sums.size() > 3) sums.erase(sums.cbegin());
        }
      }
    }

    // Answer
    return vector<int>(sums.crbegin(), sums.crend());
  }
};

// Prefix Sum + Vector
//
// Use an vector of size 3 instead of tree set.
class Solution2 {
  struct Set {
    vector<int> data;
    int n;

    Set(int n) : n(n) { data.reserve(n); }

    void insert(int x) {
      // Duplicated
      if (find(data.cbegin(), data.cend(), x) != data.cend()) return;

      // Insert
      auto it = lower_bound(data.cbegin(), data.cend(), x, greater());
      data.insert(it, x);

      // Trim
      while (data.size() > n) data.pop_back();
    }
  };

 public:
  vector<int> getBiggestThree(const vector<vector<int>>& grid) {
    const int m = grid.size(), n = grid[0].size();
    const int mn = min(m, n);

    // Prefix Sum
    auto diag = vector<vector<int>>(m + 1, vector<int>(n + 1));
    auto anti = vector<vector<int>>(m + 1, vector<int>(n + 1));
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        diag[i + 1][j + 1] = diag[i][j] + grid[i][j];
      }
      for (int j = n - 1; j >= 0; --j) {
        anti[i + 1][j] = anti[i][j + 1] + grid[i][j];
      }
    }

    // Loop for l=0
    Set sums(3);
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        sums.insert(grid[i][j]);
      }
    }

    // Loop for l>0
    for (int l = 1; l <= mn / 2; ++l) {
      for (int i = l; i < m - l; ++i) {
        for (int j = l; j < n - l; ++j) {
          int x0 = i - l, x1 = i, x2 = i + l;
          int y0 = j - l, y1 = j, y2 = j + l;
          int sum = diag[x1 + 0][y2 + 0] - diag[x0 + 0][y1 + 0] +  // top right
                    anti[x2 + 0][y1 + 1] - anti[x1 + 0][y2 + 1] +  // bottom right
                    diag[x2 + 1][y1 + 1] - diag[x1 + 1][y0 + 1] +  // bottom left
                    anti[x1 + 1][y0 + 0] - anti[x0 + 1][y1 + 0];   // top left
          sums.insert(sum);
        }
      }
    }

    // Answer
    return sums.data;
  }
};

// Prefix Sum + Array
//
// Use an array of size 3 instead of tree set.
class Solution3 {
  struct Set {
    array<int, 3> data = {};

    void insert(int x) {
      if (x == data[0] || x == data[1] || x == data[2]) {
      } else if (x > data[0]) {
        data[2] = data[1];
        data[1] = data[0];
        data[0] = x;
      } else if (x > data[1]) {
        data[2] = data[1];
        data[1] = x;
      } else if (x > data[2]) {
        data[2] = x;
      }
    }

    vector<int> toVec() {
      vector<int> ans;
      ans.reserve(3);
      for (int num : data) {
        if (!num) break;
        ans.push_back(num);
      }
      return ans;
    }
  };

 public:
  vector<int> getBiggestThree(const vector<vector<int>>& grid) {
    const int m = grid.size(), n = grid[0].size();
    const int mn = min(m, n);

    // Prefix Sum
    auto diag = vector<vector<int>>(m + 1, vector<int>(n + 1));
    auto anti = vector<vector<int>>(m + 1, vector<int>(n + 1));
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        diag[i + 1][j + 1] = diag[i][j] + grid[i][j];
      }
      for (int j = n - 1; j >= 0; --j) {
        anti[i + 1][j] = anti[i][j + 1] + grid[i][j];
      }
    }

    // Loop for l=0
    Set sums;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        sums.insert(grid[i][j]);
      }
    }

    // Loop for l>0
    for (int l = 1; l <= mn / 2; ++l) {
      for (int i = l; i < m - l; ++i) {
        for (int j = l; j < n - l; ++j) {
          int x0 = i - l, x1 = i, x2 = i + l;
          int y0 = j - l, y1 = j, y2 = j + l;
          int sum = diag[x1 + 0][y2 + 0] - diag[x0 + 0][y1 + 0] +  // top right
                    anti[x2 + 0][y1 + 1] - anti[x1 + 0][y2 + 1] +  // bottom right
                    diag[x2 + 1][y1 + 1] - diag[x1 + 1][y0 + 1] +  // bottom left
                    anti[x1 + 1][y0 + 0] - anti[x0 + 1][y1 + 0];   // top left
          sums.insert(sum);
        }
      }
    }

    // Answer
    return sums.toVec();
  }
};
