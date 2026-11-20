// Source: https://leetcode.com/problems/check-if-there-is-a-valid-parentheses-string-path
// Title: Check if There Is a Valid Parentheses String Path
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// A parentheses string is a **non-empty** string consisting only of `'('` and `')'`. It is **valid** if **any** of the following conditions is **true**:
//
// - It is `()`.
// - It can be written as `AB` (`A` concatenated with `B`), where `A` and `B` are valid parentheses strings.
// - It can be written as `(A)`, where `A` is a valid parentheses string.
//
// You are given an `m x n` matrix of parentheses `grid`. A **valid parentheses string path** in the grid is a path satisfying **all** of the following conditions:
//
// - The path starts from the upper left cell `(0, 0)`.
// - The path ends at the bottom-right cell `(m - 1, n - 1)`.
// - The path only ever moves **down** or **right**.
// - The resulting parentheses string formed by the path is **valid**.
//
// Return `true` if there exists a **valid parentheses string path** in the grid. Otherwise, return `false`.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2022/03/15/example1drawio.png
//
// ```
// Input: grid = [["(","(","("],[")","(",")"],["(","(",")"],["(","(",")"]]
// Output: true
// Explanation: The above diagram shows two possible paths that form valid parentheses strings.
// The first path shown results in the valid parentheses string "()(())".
// The second path shown results in the valid parentheses string "((()))".
// Note that there may be other valid parentheses string paths.
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2022/03/15/example2drawio.png
//
// ```
// Input: grid = [[")",")"],["(","("]]
// Output: false
// Explanation: The two possible paths form the parentheses strings "))(" and ")((". Since neither of them are valid parentheses strings, we return false.
// ```
//
// **Constraints:**
//
// - `m == grid.length`
// - `n == grid[i].length`
// - `1 <= m, n <= 100`
// - `grid[i][j]` is either `'('` or `')'`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <bitset>
#include <cstdint>
#include <vector>

using namespace std;

// 2D-DP + Bitset
//
// For each position, store all possible parentheses depth of that cell.
// Since the length of a path is at most 199, the maximum depth is 99.
class Solution {
  using Bits = bitset<100>;

 public:
  bool hasValidPath(const vector<vector<char>>& grid) {
    const int m = grid.size(), n = grid[0].size();

    // Trivial: invalid start and end
    if (grid[0][0] == ')' || grid[m - 1][n - 1] == '(') return false;

    // DP
    auto dp = vector(m, vector<Bits>(n));
    dp[0][0].set(1);
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        Bits top = (i == 0) ? 0 : dp[i - 1][j];
        Bits left = (j == 0) ? 0 : dp[i][j - 1];

        if (grid[i][j] == '(') {
          dp[i][j] |= (top | left) << 1;
        } else {
          dp[i][j] |= (top | left) >> 1;
        }
      }
    }

    return dp.back().back().test(0);
  }
};

// 2D-DP + Bitset
//
// Since the parity of the depth is equal to the cell position,
// we only need 50 bits for this information.
// Therefore, we can use a 64bit integer.
//
// Bit k means depth 2k+1 for (i+j) even;
//       means depth 2k   for (i+j) odd.
class Solution2 {
 public:
  bool hasValidPath(const vector<vector<char>>& grid) {
    const int m = grid.size(), n = grid[0].size();

    // Trivial: path length not odd
    if ((m + n) % 2 == 0) return false;

    // Trivial: invalid start and end
    if (grid[0][0] == ')' || grid[m - 1][n - 1] == '(') return false;

    // DP
    auto dp = vector(m, vector<uint64_t>(n));
    dp[0][0] = 1;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        uint64_t top = (i == 0) ? 0 : dp[i - 1][j];
        uint64_t left = (j == 0) ? 0 : dp[i][j - 1];

        if (grid[i][j] == '(') {
          dp[i][j] |= (top | left) << ((i + j) % 2 == 1);
        } else {
          dp[i][j] |= (top | left) >> ((i + j) % 2 == 0);
        }
      }
    }

    return dp.back().back() & 1;
  }
};

// 1D-DP + Bitset
class Solution3 {
 public:
  bool hasValidPath(const vector<vector<char>>& grid) {
    const int m = grid.size(), n = grid[0].size();

    // Trivial: path length not odd
    if ((m + n) % 2 == 0) return false;

    // Trivial: invalid start and end
    if (grid[0][0] == ')' || grid[m - 1][n - 1] == '(') return false;

    // DP
    auto prev = vector<uint64_t>(n);
    auto curr = vector<uint64_t>(n);

    for (int i = 0; i < m; ++i) {
      swap(curr, prev);

      for (int j = 0; j < n; ++j) {
        curr[j] = (i + j == 0) ? 1 : 0;  // Init

        uint64_t top = (i == 0) ? 0 : prev[j];
        uint64_t left = (j == 0) ? 0 : curr[j - 1];

        if (grid[i][j] == '(') {
          curr[j] |= (top | left) << ((i + j) % 2 == 1);
        } else {
          curr[j] |= (top | left) >> ((i + j) % 2 == 0);
        }
      }
    }

    return curr.back() & 1;
  }
};

// 1D-DP + Bitset
//
// We only need one array.
class Solution4 {
 public:
  bool hasValidPath(const vector<vector<char>>& grid) {
    const int m = grid.size(), n = grid[0].size();

    // Trivial: path length not odd
    if ((m + n) % 2 == 0) return false;

    // Trivial: invalid start and end
    if (grid[0][0] == ')' || grid[m - 1][n - 1] == '(') return false;

    // DP
    auto dp = vector<uint64_t>(n);

    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        uint64_t top = (i == 0) ? 0 : dp[j];
        uint64_t left = (j == 0) ? 0 : dp[j - 1];

        dp[j] = (i + j == 0) ? 1 : 0;  // Init

        if (grid[i][j] == '(') {
          dp[j] |= (top | left) << ((i + j) % 2 == 1);
        } else {
          dp[j] |= (top | left) >> ((i + j) % 2 == 0);
        }
      }
    }

    return dp.back() & 1;
  }
};
