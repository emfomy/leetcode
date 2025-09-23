// Source: https://leetcode.com/problems/sort-matrix-by-diagonals
// Title: Sort Matrix by Diagonals
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an `n x n` square matrix of integers `grid`. Return the matrix such that:
//
// - The diagonals in the **bottom-left triangle**  (including the middle diagonal) are sorted in **non-increasing order** .
// - The diagonals in the **top-right triangle**  are sorted in **non-decreasing order** .
//
// **Example 1:**
//
// ```
// Input: grid = [[1,7,3],[9,8,2],[4,5,6]]
// Output: [[8,2,3],[9,6,7],[4,5,1]]
// Explanation:
// https://assets.leetcode.com/uploads/2024/12/29/4052example1drawio.png
// The diagonals with a black arrow (bottom-left triangle) should be sorted in non-increasing order:
// - `[1, 8, 6]` becomes `[8, 6, 1]`.
// - `[9, 5]` and `[4]` remain unchanged.
// The diagonals with a blue arrow (top-right triangle) should be sorted in non-decreasing order:
// - `[7, 2]` becomes `[2, 7]`.
// - `[3]` remains unchanged.
// ```
//
// **Example 2:**
//
// ```
// Input: grid = [[0,1],[1,2]]
// Output: [[2,1],[1,0]]
// Explanation:
// https://assets.leetcode.com/uploads/2024/12/29/4052example2adrawio.png
// The diagonals with a black arrow must be non-increasing, so `[0, 2]` is changed to `[2, 0]`. The other diagonals are already in the correct order.
// ```
//
// **Example 3:**
//
// ```
// Input: grid = [[1]]
// Output: [[1]]
// Explanation:
// Diagonals with exactly one element are already in order, so no changes are needed.
// ```
//
// **Constraints:**
//
// - `grid.length == grid[i].length == n`
// - `1 <= n <= 10`
// - `-10^5 <= grid[i][j] <= 10^5`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <functional>
#include <vector>

using namespace std;

// Copy & Sort
class Solution {
 public:
  vector<vector<int>> sortMatrix(vector<vector<int>>& grid) {
    int n = grid.size();
    auto buffer = vector<int>(n);
    auto ans = vector<vector<int>>(n, vector<int>(n));

    // Lower
    for (auto k = 0; k < n; k++) {
      buffer.resize(n - k);
      for (auto j = 0; j < n - k; j++) {
        auto i = k + j;
        buffer[j] = grid[i][j];
      }
      sort(buffer.begin(), buffer.end(), greater<int>());
      for (auto j = 0; j < n - k; j++) {
        auto i = k + j;
        ans[i][j] = buffer[j];
      }
    }

    // Upper
    for (auto k = 1; k < n; k++) {
      buffer.resize(n - k);
      for (auto i = 0; i < n - k; i++) {
        auto j = k + i;
        buffer[i] = grid[i][j];
      }
      sort(buffer.begin(), buffer.end(), less<int>());
      for (auto i = 0; i < n - k; i++) {
        auto j = k + i;
        ans[i][j] = buffer[i];
      }
    }

    return ans;
  }
};

// Sort with Custom Iterator
//
// Note that this is slower due to poorer memory access efficiency.
class Solution2 {
  struct Iterator {
    using iterator_category = random_access_iterator_tag;
    using value_type = int;
    using difference_type = ptrdiff_t;
    using reference = int&;
    using pointer = int*;

    vector<vector<int>>* mat;
    int i, j;

    Iterator(vector<vector<int>>* mat, int i, int j) : mat(mat), i(i), j(j) {}

    reference operator*() const { return (*mat)[i][j]; }

    Iterator& operator++() {
      ++i;
      ++j;
      return *this;
    }
    Iterator operator++(int) {
      auto tmp = *this;
      ++(*this);
      return tmp;
    }
    Iterator& operator--() {
      --i;
      --j;
      return *this;
    }
    Iterator operator--(int) {
      auto tmp = *this;
      --(*this);
      return tmp;
    }

    Iterator& operator+=(difference_type n) {
      i += n;
      j += n;
      return *this;
    }
    Iterator operator+(difference_type n) const {
      auto it = *this;
      it += n;
      return it;
    }
    friend Iterator operator+(difference_type n, Iterator it) { return it + n; }

    Iterator& operator-=(difference_type n) {
      *this += -n;
      return *this;
    }
    Iterator operator-(difference_type n) const { return *this + (-n); }
    difference_type operator-(const Iterator& it) const { return i - it.i; }

    reference operator[](difference_type n) const { return (*mat)[i + n][j + n]; }

    bool operator==(const Iterator& o) const { return i == o.i; }
    bool operator!=(const Iterator& o) const { return !(*this == o); }
    bool operator<(const Iterator& o) const { return i < o.i; }
  };

 public:
  vector<vector<int>> sortMatrix(vector<vector<int>>& grid) {
    int n = grid.size();

    // Lower
    for (auto k = 0; k < n; k++) {
      sort(Iterator(&grid, k, 0), Iterator(&grid, n, n - k), greater<int>());
    }

    // Upper
    for (auto k = 1; k < n; k++) {
      sort(Iterator(&grid, 0, k), Iterator(&grid, n - k, n), less<int>());
    }

    return grid;
  }
};
