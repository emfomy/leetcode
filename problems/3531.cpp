// Source: https://leetcode.com/problems/count-covered-buildings
// Title: Count Covered Buildings
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a positive integer `n`, representing an `n x n` city. You are also given a 2D grid `buildings`, where `buildings[i] = [x, y]` denotes a **unique** building located at coordinates `[x, y]`.
//
// A building is **covered** if there is at least one building in all **four** directions: left, right, above, and below.
//
// Return the number of **covered** buildings.
//
// **Example 1:**
//
// https://assets.leetcode.com/uploads/2025/03/04/telegram-cloud-photo-size-5-6212982906394101085-m.jpg
//
// ```
// Input: n = 3, buildings = [[1,2],[2,2],[3,2],[2,1],[2,3]]
// Output: 1
// Explanation:
// - Only building `[2,2]` is covered as it has at least one building:
//   - above (`[1,2]`)
//   - below (`[3,2]`)
//   - left (`[2,1]`)
//   - right (`[2,3]`)
// - Thus, the count of covered buildings is 1.
// ```
//
// **Example 2:**
//
// https://assets.leetcode.com/uploads/2025/03/04/telegram-cloud-photo-size-5-6212982906394101086-m.jpg
//
// ```
// Input: n = 3, buildings = [[1,1],[1,2],[2,1],[2,2]]
// Output: 0
// Explanation:
// - No building has at least one building in all four directions.
// ```
//
// **Example 3:**
//
// https://assets.leetcode.com/uploads/2025/03/16/telegram-cloud-photo-size-5-6248862251436067566-x.jpg
//
// Input: n = 5, buildings = [[1,3],[3,2],[3,3],[3,5],[5,3]]
// Output: 1
// Explanation:
// - Only building `[3,3]` is covered as it has at least one building:
//   - above (`[1,3]`)
//   - below (`[5,3]`)
//   - left (`[3,2]`)
//   - right (`[3,5]`)
// - Thus, the count of covered buildings is 1.
// ```
//
// **Constraints:**
//
// - `2 <= n <= 10^5`
// - `1 <= buildings.length <= 10^5 `
// - `buildings[i] = [x, y]`
// - `1 <= x, y <= n`
// - All coordinates of `buildings` are **unique**.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

// O(n^2)
class Solution {
 public:
  int countCoveredBuildings(int n, vector<vector<int>>& buildings) {
    // Prepare
    auto grid = vector(n, vector(n, 0));  // 0: empty, 1: building, (i+1): covered by i buildings
    for (auto& building : buildings) {
      auto x = building[0] - 1, y = building[1] - 1;
      grid[x][y] = 1;
    }

    // x
    for (auto x = 0; x < n; ++x) {
      auto covered = false;
      for (auto y = 0; y < n; ++y) {
        if (grid[x][y] > 0) {
          if (covered) ++grid[x][y];
          covered = true;
        }
      }

      covered = false;
      for (auto y = n - 1; y >= 0; --y) {
        if (grid[x][y] > 0) {
          if (covered) ++grid[x][y];
          covered = true;
        }
      }
    }

    // y
    for (auto y = 0; y < n; ++y) {
      auto covered = false;
      for (auto x = 0; x < n; ++x) {
        if (grid[x][y] > 0) {
          if (covered) ++grid[x][y];
          covered = true;
        }
      }

      covered = false;
      for (auto x = n - 1; x >= 0; --x) {
        if (grid[x][y] > 0) {
          if (covered) ++grid[x][y];
          covered = true;
        }
      }
    }

    // answer
    auto ans = 0;
    for (auto& row : grid) {
      for (auto cell : row) {
        ans += (cell == 5);
      }
    }

    return ans;
  }
};

// Sort, O(mlogm)
class Solution2 {
 public:
  int countCoveredBuildings(int n, vector<vector<int>>& buildings) {
    int m = buildings.size();

    // Prepare
    auto covers = vector<int>(m);
    auto idxs = vector<int>(m);
    iota(idxs.begin(), idxs.end(), 0);

    // Sort by x
    sort(idxs.begin(), idxs.end(), [&](int i, int j) -> bool {
      return make_pair(buildings[i][0], buildings[i][1]) < make_pair(buildings[j][0], buildings[j][1]);
    });

    {
      auto prevX = 0;
      for (auto i = 0; i < m; ++i) {
        auto idx = idxs[i];
        auto x = buildings[idx][0];
        if (x == prevX) ++covers[idx];
        prevX = x;
      }
      prevX = n + 1;
      for (auto i = m - 1; i >= 0; --i) {
        auto idx = idxs[i];
        auto x = buildings[idx][0];
        if (x == prevX) ++covers[idx];
        prevX = x;
      }
    }

    // Sort by y
    sort(idxs.begin(), idxs.end(), [&](int i, int j) -> bool {
      return make_pair(buildings[i][1], buildings[i][0]) < make_pair(buildings[j][1], buildings[j][0]);
    });

    {
      auto prevY = 0;
      for (auto i = 0; i < m; ++i) {
        auto idx = idxs[i];
        auto y = buildings[idx][1];
        if (y == prevY) ++covers[idx];
        prevY = y;
      }
      prevY = n + 1;
      for (auto i = m - 1; i >= 0; --i) {
        auto idx = idxs[i];
        auto y = buildings[idx][1];
        if (y == prevY) ++covers[idx];
        prevY = y;
      }
    }

    // Count
    auto ans = count(covers.cbegin(), covers.cend(), 4);
    return ans;
  }
};

// Min & Max, O(m)
//
// Find the min & max of each row / column.
class Solution3 {
 public:
  int countCoveredBuildings(int n, vector<vector<int>>& buildings) {
    int m = buildings.size();

    // Prepare
    auto minXs = vector(n, n);
    auto maxXs = vector(n, -1);
    auto minYs = vector(n, n);
    auto maxYs = vector(n, -1);

    // Find min & max
    for (auto& building : buildings) {
      auto x = building[0] - 1, y = building[1] - 1;
      minXs[y] = min(minXs[y], x);
      maxXs[y] = max(maxXs[y], x);
      minYs[x] = min(minYs[x], y);
      maxYs[x] = max(maxYs[x], y);
    }

    // Count
    auto ans = 0;
    for (auto i = 0; i < m; ++i) {
      auto x = buildings[i][0] - 1, y = buildings[i][1] - 1;
      ans += (minXs[y] != x && maxXs[y] != x && minYs[x] != y && maxYs[x] != y);
    }

    return ans;
  }
};
