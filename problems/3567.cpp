// Source: https://leetcode.com/problems/minimum-absolute-difference-in-sliding-submatrix
// Title: Minimum Absolute Difference in Sliding Submatrix
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an `m x n` integer matrix `grid` and an integer `k`.
//
// For every contiguous `k x k` **submatrix** of `grid`, compute the **minimum absolute** difference between any two **distinct** values within that **submatrix**.
//
// Return a 2D array `ans` of size `(m - k + 1) x (n - k + 1)`, where `ans[i][j]` is the minimum absolute difference in the submatrix whose top-left corner is `(i, j)` in `grid`.
//
// **Note**: If all elements in the submatrix have the same value, the answer will be 0.
// A submatrix `(x1, y1, x2, y2)` is a matrix that is formed by choosing all cells `matrix[x][y]` where `x1 <= x <= x2` and `y1 <= y <= y2`.
//
// **Example 1:**
//
// ```
// Input: grid = [[1,8],[3,-2]], k = 2
// Output: [[2]]
// Explanation:
// - There is only one possible `k x k` submatrix: `[[1, 8], [3, -2]]`.
// - Distinct values in the submatrix are `[1, 8, 3, -2]`.
// - The minimum absolute difference in the submatrix is `|1 - 3| = 2`. Thus, the answer is `[[2]]`.
// ```
//
// **Example 2:**
//
// ```
// Input: grid = [[3,-1]], k = 1
// Output: [[0,0]]
// Explanation:
// - Both `k x k` submatrix has only one distinct element.
// - Thus, the answer is `[[0, 0]]`.
// ```
//
// **Example 3:**
//
// ```
// Input: grid = [[1,-2,3],[2,3,5]], k = 2
// Output: [[1,2]]
// Explanation:
// - There are two possible `k × k` submatrix:
//   - Starting at `(0, 0)`: `[[1, -2], [2, 3]]`.
//     - Distinct values in the submatrix are `[1, -2, 2, 3]`.
//     - The minimum absolute difference in the submatrix is `|1 - 2| = 1`.
//   - Starting at `(0, 1)`: `[[-2, 3], [3, 5]]`.
//     - Distinct values in the submatrix are `[-2, 3, 5]`.
//     - The minimum absolute difference in the submatrix is `|3 - 5| = 2`.
// - Thus, the answer is `[[1, 2]]`.
// ```
//
// **Constraints:**
//
// - `1 <= m == grid.length <= 30`
// - `1 <= n == grid[i].length <= 30`
// - `-10^5 <= grid[i][j] <= 10^5`
// - `1 <= k <= min(m, n)`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <climits>
#include <map>
#include <set>
#include <vector>

using namespace std;

// Brute Force + Tree Set
class Solution {
 public:
  vector<vector<int>> minAbsDiff(const vector<vector<int>>& grid, int k) {
    const int m = grid.size(), n = grid[0].size();
    if (k > m || k > n) return {};

    // Helper
    const auto minDiff = [&grid, k](int i0, int j0) {
      set<int> vals;
      for (int i = i0; i < i0 + k; ++i) {
        for (int j = j0; j < j0 + k; ++j) {
          vals.insert(grid[i][j]);
        }
      }

      if (vals.size() <= 1) return 0;

      int diff = INT_MAX;
      auto it = vals.begin();
      int prev = *it;
      for (++it; it != vals.end(); ++it) {
        diff = min(diff, *it - prev);
        prev = *it;
      }
      return diff;
    };

    // Loop
    auto ans = vector<vector<int>>(m - k + 1, vector<int>(n - k + 1));
    for (int i0 = 0; i0 <= m - k; ++i0) {
      for (int j0 = 0; j0 <= n - k; ++j0) {
        ans[i0][j0] = minDiff(i0, j0);
      }
    }

    return ans;
  }
};

// Brute Force + Tree Map + Sliding Window
//
// Reuse tree set: use a tree map as counter instead.
// We loop the slide column-wise, and update the rows each time.
class Solution2 {
 public:
  vector<vector<int>> minAbsDiff(const vector<vector<int>>& grid, int k) {
    const int m = grid.size(), n = grid[0].size();
    if (k > m || k > n) return {};

    // Helper
    const auto minDiff = [](const map<int, int>& cnts) {
      if (cnts.size() <= 1) return 0;

      int diff = INT_MAX;
      auto it = cnts.begin();
      int prev = it->first;
      for (++it; it != cnts.end(); ++it) {
        diff = min(diff, it->first - prev);
        prev = it->first;
      }
      return diff;
    };

    // Loop
    auto ans = vector<vector<int>>(m - k + 1, vector<int>(n - k + 1));
    for (int j0 = 0; j0 <= n - k; ++j0) {
      map<int, int> cnts;

      // i0 = 0
      for (int i = 0; i < k; ++i) {
        for (int j = j0; j < j0 + k; ++j) {
          ++cnts[grid[i][j]];
        }
      }
      ans[0][j0] = minDiff(cnts);

      // i0 > 0
      for (int i0 = 1; i0 <= m - k; ++i0) {
        for (int j = j0; j < j0 + k; ++j) {
          if (--cnts[grid[i0 - 1][j]] == 0) cnts.erase(grid[i0 - 1][j]);
        }
        for (int j = j0; j < j0 + k; ++j) {
          ++cnts[grid[i0 + k - 1][j]];
        }
        ans[i0][j0] = minDiff(cnts);
      }
    }

    return ans;
  }
};

// Brute Force + Tree Map + Zig Zag Sliding Window
//
// Reuse tree set: use a tree map as counter instead.
// We loop the slide column-wise, and update the rows each time.
// We loop in zig-zag.
class Solution3 {
 public:
  vector<vector<int>> minAbsDiff(const vector<vector<int>>& grid, int k) {
    const int m = grid.size(), n = grid[0].size();
    if (k > m || k > n) return {};

    // Helper
    const auto minDiff = [](const map<int, int>& cnts) {
      if (cnts.size() <= 1) return 0;

      int diff = INT_MAX;
      auto it = cnts.begin();
      int prev = it->first;
      for (++it; it != cnts.end(); ++it) {
        diff = min(diff, it->first - prev);
        prev = it->first;
      }
      return diff;
    };

    // Init
    map<int, int> cnts;
    for (int i = 0; i < k; ++i) {
      for (int j = 0; j < k; ++j) {
        ++cnts[grid[i][j]];
      }
    }

    // Loop
    auto ans = vector<vector<int>>(m - k + 1, vector<int>(n - k + 1));
    for (int j0 = 0; j0 <= n - k; ++j0) {
      if (j0 % 2 == 0) {  // go down

        // i0 = 0
        if (j0 != 0) {
          // Slide right
          for (int i = 0; i < k; ++i) {
            if (--cnts[grid[i][j0 - 1]] == 0) cnts.erase(grid[i][j0 - 1]);
            ++cnts[grid[i][j0 + k - 1]];
          }
        }
        ans[0][j0] = minDiff(cnts);

        // i0 > 0
        for (int i0 = 1; i0 <= m - k; ++i0) {
          // Slide down
          for (int j = j0; j < j0 + k; ++j) {
            if (--cnts[grid[i0 - 1][j]] == 0) cnts.erase(grid[i0 - 1][j]);
          }
          for (int j = j0; j < j0 + k; ++j) {
            ++cnts[grid[i0 + k - 1][j]];
          }
          ans[i0][j0] = minDiff(cnts);
        }
      } else {  // go up

        // i0 = m-k, Slide right
        for (int i = m - k; i < m; ++i) {
          if (--cnts[grid[i][j0 - 1]] == 0) cnts.erase(grid[i][j0 - 1]);
          ++cnts[grid[i][j0 + k - 1]];
        }
        ans[m - k][j0] = minDiff(cnts);

        // i0 < m-k
        for (int i0 = m - k - 1; i0 >= 0; --i0) {
          // Slide up
          for (int j = j0; j < j0 + k; ++j) {
            if (--cnts[grid[i0 + k][j]] == 0) cnts.erase(grid[i0 + k][j]);
          }
          for (int j = j0; j < j0 + k; ++j) {
            ++cnts[grid[i0][j]];
          }
          ans[i0][j0] = minDiff(cnts);
        }
      }
    }

    return ans;
  }
};

// Brute Force + Sort
//
// Vector with sort is much faster than tree set.
class Solution4 {
 public:
  vector<vector<int>> minAbsDiff(const vector<vector<int>>& grid, int k) {
    const int m = grid.size(), n = grid[0].size();
    if (k > m || k > n) return {};

    // Helper
    vector<int> vals;
    vals.reserve(k * k);
    const auto minDiff = [&grid, k, &vals](int i0, int j0) {
      vals.clear();
      for (int i = i0; i < i0 + k; ++i) {
        for (int j = j0; j < j0 + k; ++j) {
          vals.push_back(grid[i][j]);
        }
      }

      sort(vals.begin(), vals.end());
      int diff = INT_MAX;
      for (int x = 1; x < k * k; ++x) {
        if (vals[x] != vals[x - 1]) diff = min(diff, vals[x] - vals[x - 1]);
      }
      return diff == INT_MAX ? 0 : diff;
    };

    // Loop
    auto ans = vector<vector<int>>(m - k + 1, vector<int>(n - k + 1));
    for (int i0 = 0; i0 <= m - k; ++i0) {
      for (int j0 = 0; j0 <= n - k; ++j0) {
        ans[i0][j0] = minDiff(i0, j0);
      }
    }

    return ans;
  }
};
