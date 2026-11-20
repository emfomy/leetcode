// Source: https://leetcode.com/problems/minimum-remove-to-make-valid-parentheses
// Title: Minimum Remove to Make Valid Parentheses
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a string s of `'('` , `')'` and lowercase English characters.
//
// Your task is to remove the minimum number of parentheses ( `'('` or `')'`, in any positions ) so that the resulting parentheses string is valid and return **any** valid string.
//
// Formally, a parentheses string is valid if and only if:
//
// - It is the empty string, contains only lowercase characters, or
// - It can be written as `AB` (`A` concatenated with `B`), where `A` and `B` are valid strings, or
// - It can be written as `(A)`, where `A` is a valid string.
//
// **Example 1:**
//
// ```
// Input: s = "lee(t(c)o)de)"
// Output: "lee(t(c)o)de"
// Explanation: "lee(t(co)de)" , "lee(t(c)ode)" would also be accepted.
// ```
//
// **Example 2:**
//
// ```
// Input: s = "a)b(c)d"
// Output: "ab(c)d"
// ```
//
// **Example 3:**
//
// ```
// Input: s = "))(("
// Output: ""
// Explanation: An empty string is also valid.
// ```
//
// **Constraints:**
//
// - `1 <= s.length <= 10^5`
// - `s[i]` is either`'('` , `')'`, or lowercase English letter.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <numeric>
#include <vector>

using namespace std;

// Union Find
//
// Group the island using union-find.
// Remove islands at edge.
class Solution {
  using Bool = unsigned char;

  struct UnionFind {
    vector<int> parents;
    vector<int> ranks;

    UnionFind(int n) : parents(n), ranks(n, 0) {  //
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
    }
  };

 public:
  int closedIsland(const vector<vector<int>>& grid) {
    const int m = grid.size(), n = grid[0].size();

    // Helper
    const auto idx = [m, n](int i, int j) { return i * n + j; };

    // Union Find
    auto uf = UnionFind(m * n);
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (grid[i][j] == 1) continue;  // skip water

        if (i + 1 < m && grid[i + 1][j] == 0) {
          uf.unite(idx(i, j), idx(i + 1, j));
        }
        if (j + 1 < n && grid[i][j + 1] == 0) {
          uf.unite(idx(i, j), idx(i, j + 1));
        }
      }
    }

    // Count islands
    auto island = vector<Bool>(m * n);
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (grid[i][j] == 0 && uf.parents[idx(i, j)] == idx(i, j)) {
          island[idx(i, j)] = true;
        }
      }
    }

    // Remove edge
    for (int i = 0; i < m; ++i) {
      island[uf.find(idx(i, 0))] = false;
      island[uf.find(idx(i, n - 1))] = false;
    }
    for (int j = 1; j < n - 1; ++j) {
      island[uf.find(idx(0, j))] = false;
      island[uf.find(idx(m - 1, j))] = false;
    }

    return count(island.cbegin(), island.cend(), true);
  }
};
