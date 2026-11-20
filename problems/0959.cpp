// Source: https://leetcode.com/problems/regions-cut-by-slashes
// Title: Regions Cut By Slashes
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// An `n x n` grid is composed of `1 x 1` squares where each `1 x 1` square consists of a `'/'`, `'\'`, or blank space `' '`. These characters divide the square into contiguous regions.
//
// Given the grid `grid` represented as a string array, return the number of regions.
//
// Note that backslash characters are escaped, so a `'\'` is represented as `'\'`.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2018/12/15/1.png
//
// ```
// Input: grid = [" /","/ "]
// Output: 2
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2018/12/15/2.png
//
// ```
// Input: grid = [" /","  "]
// Output: 1
// ```
//
// **Example 3:**
// https://assets.leetcode.com/uploads/2018/12/15/4.png
//
// ```
// Input: grid = ["/\","\/"]
// Output: 5
// Explanation: Recall that because \ characters are escaped, "\/" refers to \/, and "/\" refers to /\.
// ```
//
// **Constraints:**
//
// - `n == grid.length == grid[i].length`
// - `1 <= n <= 30`
// - `grid[i][j]` is either `'/'`, `'\'`, or `' '`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <numeric>
#include <string>
#include <vector>

using namespace std;

// Union-Find
//
// Treat vertical and horizontal edge of the grid cells as graph node.
// Loop through all grid cells and use union-find to unite them.
//
// Total 2n(n+1) nodes. We use row-major IDs.
// The first half IDs for verticals, and the last half IDs for horizontals.
class Solution {
  struct UnionFind {
    vector<int> parents;
    vector<int> ranks;
    int count;

    UnionFind(int n) : parents(n), ranks(n, 0), count(n) {  //
      iota(parents.begin(), parents.end(), 0);
    }

    int find(int x) {
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
      if (ranks[x] < ranks[y]) swap(x, y);

      // Merge y into x
      if (ranks[x] == ranks[y]) ++ranks[x];
      parents[y] = x;
      --count;
    }
  };

 public:
  int regionsBySlashes(vector<string>& grid) {
    const int n = grid.size();
    const int totalNodes = 2 * n * (n + 1);
    const int halfTotalNodes = n * (n + 1);

    // Helper of IDs
    auto verticalID = [n](int r, int c) -> int { return r * (n + 1) + c; };
    auto horizontalID = [n, halfTotalNodes](int r, int c) -> int { return r * n + c + halfTotalNodes; };

    // Union Find
    auto uf = UnionFind(totalNodes);
    for (int r = 0; r < n; ++r) {
      for (int c = 0; c < n; ++c) {
        const char cell = grid[r][c];

        const int topID = horizontalID(r, c);
        const int bottomID = horizontalID(r + 1, c);
        const int leftID = verticalID(r, c);
        const int rightID = verticalID(r, c + 1);

        if (cell == ' ' || cell == '/') {  // merge top+left, bottom+right
          uf.unite(topID, leftID);
          uf.unite(bottomID, rightID);
        }
        if (cell == ' ' || cell == '\\') {  // merge top+right, bottom+left
          uf.unite(topID, rightID);
          uf.unite(bottomID, leftID);
        }
      }
    }

    return uf.count;
  }
};
