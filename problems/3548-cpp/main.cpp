// Source: https://leetcode.com/problems/equal-sum-grid-partition-ii
// Title: Equal Sum Grid Partition II
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an `m x n` matrix `grid` of positive integers. Your task is to determine if it is possible to make **either one horizontal or one vertical cut** on the grid such that:
//
// - Each of the two resulting sections formed by the cut is **non-empty**.
// - The sum of elements in both sections is **equal**, or can be made equal by discounting **at most** one single cell in total (from either section).
// - If a cell is discounted, the rest of the section must **remain connected**.
//
// Return `true` if such a partition exists; otherwise, return `false`.
//
// **Note:** A section is **connected** if every cell in it can be reached from any other cell by moving up, down, left, or right through other cells in the section.
//
// **Example 1:**
//
// ```
// Input: grid = [[1,4],[2,3]]
// Output: true
// Explanation:
// https://assets.leetcode.com/uploads/2025/03/30/lc.jpeg
// - A horizontal cut after the first row gives sums `1 + 4 = 5` and `2 + 3 = 5`, which are equal. Thus, the answer is `true`.
// ```
//
// **Example 2:**
//
// ```
// Input: grid = [[1,2],[3,4]]
// Output: true
// Explanation:
// https://assets.leetcode.com/uploads/2025/04/01/chatgpt-image-apr-1-2025-at-05_28_12-pm.png
// - A vertical cut after the first column gives sums `1 + 3 = 4` and `2 + 4 = 6`.
// - By discounting 2 from the right section (`6 - 2 = 4`), both sections have equal sums and remain connected. Thus, the answer is `true`.
// ```
//
// **Example 3:**
//
// ```
// Input: grid = [[1,2,4],[2,3,5]]
// Output: false
// Explanation:
// **https://assets.leetcode.com/uploads/2025/04/01/chatgpt-image-apr-2-2025-at-02_50_29-am.png**
// - A horizontal cut after the first row gives `1 + 2 + 4 = 7` and `2 + 3 + 5 = 10`.
// - By discounting 3 from the bottom section (`10 - 3 = 7`), both sections have equal sums, but they do not remain connected as it splits the bottom section into two parts (`[2]` and `[5]`). Thus, the answer is `false`.
// ```
//
// **Example 4:**
//
// ```
// Input: grid = [[4,1,8],[3,2,6]]
// Output: false
// Explanation:
// No valid cut exists, so the answer is `false`.
// ```
//
// **Constraints:**
//
// - `1 <= m == grid.length <= 10^5`
// - `1 <= n == grid[i].length <= 10^5`
// - `2 <= m * n <= 10^5`
// - `1 <= grid[i][j] <= 10^5`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <unordered_map>
#include <vector>

using namespace std;

// Hash Map
//
// If the section is at least 2 for both side, then we can freely discard any cell.
// Otherwise, we can only discard one of the end cell.
//
// We first compute the total sum, and count for each cell number using hash map.
// Next loop row-wise and column-wise, and update the counter.
// For each step, we check if the difference of both section exist int the hash map.
//
// Note that we handle the size-1 section independently.
class Solution {
  struct Counter {
    int64_t sum = 0;
    unordered_map<int64_t, int> counts;

    Counter() = default;
    Counter(Counter&& other) = default;
    Counter& operator=(Counter&&) = default;

    void add(int64_t val) {
      sum += val;
      ++counts[val];
    }

    void remove(int64_t val) {
      sum -= val;
      if (--counts[val] == 0) counts.erase(val);
    }

    bool contains(int64_t val) const {  //
      return counts.contains(val);
    }
  };

 public:
  bool canPartitionGrid(vector<vector<int>>& grid) {
    const int m = grid.size(), n = grid[0].size();

    // Guard
    if (m == 1 && n == 1) return true;

    // Total sum
    Counter total;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        total.add(grid[i][j]);
      }
    }

    // Row-wise
    {
      Counter tops;
      Counter bottoms(std::move(total));
      for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
          tops.add(grid[i][j]);
          bottoms.remove(grid[i][j]);
        }
        int64_t diff = tops.sum - bottoms.sum;

        // Bottom section is empty
        if (i == m - 1) continue;

        // Prefect Cut
        if (diff == 0) return true;  // perfect cut

        // Thin grid
        if (n == 1) {
          // Remove from top
          if (i != 0 && (diff == grid[0][0] || diff == grid[i][0])) return true;

          // Remove from bottom
          if (i != m - 2 && (-diff == grid[m - 1][0] || diff == grid[i + 1][0])) return true;
          continue;
        }

        // Remove from top
        if (tops.contains(diff)) {
          if (i != 0) return true;

          // Only allowed to remove from end of the section
          if (diff == grid[0][0] || diff == grid[0][n - 1]) return true;
        }

        // Remove from bottom
        if (bottoms.contains(-diff)) {
          if (i != m - 2) return true;

          // Only allowed to remove from end of the section
          if (-diff == grid[m - 1][0] || -diff == grid[m - 1][n - 1]) return true;
        }
      }
      swap(total, tops);
    }

    // Column-wise
    {
      Counter lefts;
      Counter rights(std::move(total));
      for (int j = 0; j < n; ++j) {
        for (int i = 0; i < m; ++i) {
          lefts.add(grid[i][j]);
          rights.remove(grid[i][j]);
        }
        int64_t diff = lefts.sum - rights.sum;

        // right section is empty
        if (j == n - 1) continue;

        // Prefect Cut
        if (diff == 0) return true;  // perfect cut

        // Thin grid
        if (m == 1) {
          // Remove from left
          if (j != 0 && (diff == grid[0][0] || diff == grid[0][j])) return true;

          // Remove from right
          if (j != n - 2 && (-diff == grid[0][n - 1] || diff == grid[0][j + 1])) return true;
          continue;
        }

        // Remove from left
        if (lefts.contains(diff)) {
          if (j != 0) return true;

          // Only allowed to remove from end of the section
          if (diff == grid[0][0] || diff == grid[m - 1][0]) return true;
        }

        // Remove from right
        if (rights.contains(-diff)) {
          if (j != m - 2) return true;

          // Only allowed to remove from end of the section
          if (-diff == grid[0][n - 1] || -diff == grid[m - 1][n - 1]) return true;
        }
      }
      swap(total, lefts);
    }

    return false;
  }
};
