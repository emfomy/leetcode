// Source: https://leetcode.com/problems/find-the-maximum-number-of-fruits-collected
// Title: Find the Maximum Number of Fruits Collected
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There is a game dungeon comprised of`n x n` rooms arranged in a grid.
//
// You are given a 2D array `fruits` of size `n x n`, where `fruits[i][j]` represents the number of fruits in the room `(i, j)`. Three children will play in the game dungeon, with **initial** positions at the corner rooms `(0, 0)`, `(0, n - 1)`, and `(n - 1, 0)`.
//
// The children will make **exactly** `n - 1` moves according to the following rules to reach the room `(n - 1, n - 1)`:
//
// - The child starting from `(0, 0)` must move from their current room `(i, j)` to one of the rooms `(i + 1, j + 1)`, `(i + 1, j)`, and `(i, j + 1)` if the target room exists.
// - The child starting from `(0, n - 1)` must move from their current room `(i, j)` to one of the rooms `(i + 1, j - 1)`, `(i + 1, j)`, and `(i + 1, j + 1)` if the target room exists.
// - The child starting from `(n - 1, 0)` must move from their current room `(i, j)` to one of the rooms `(i - 1, j + 1)`, `(i, j + 1)`, and `(i + 1, j + 1)` if the target room exists.
//
// When a child enters a room, they will collect all the fruits there. If two or more children enter the same room, only one child will collect the fruits, and the room will be emptied after they leave.
//
// Return the **maximum** number of fruits the children can collect from the dungeon.
//
// **Example 1:**
//
// ```
// Input: fruits = [[1,2,3,4],[5,6,8,7],[9,10,11,12],[13,14,15,16]]
// Output: 100
// Explanation:
// https://assets.leetcode.com/uploads/2024/10/15/example_1.gif
// In this example:
// - The 1^st child (green) moves on the path `(0,0) -> (1,1) -> (2,2) -> (3, 3)`.
// - The 2^nd child (red) moves on the path `(0,3) -> (1,2) -> (2,3) -> (3, 3)`.
// - The 3^rd child (blue) moves on the path `(3,0) -> (3,1) -> (3,2) -> (3, 3)`.
// In total they collect `1 + 6 + 11 + 16 + 4 + 8 + 12 + 13 + 14 + 15 = 100` fruits.
// ```
//
// **Example 2:**
//
// ```
// Input: fruits = [[1,1],[1,1]]
// Output: 4
// Explanation:
// In this example:
// - The 1^st child moves on the path `(0,0) -> (1,1)`.
// - The 2^nd child moves on the path `(0,1) -> (1,1)`.
// - The 3^rd child moves on the path `(1,0) -> (1,1)`.
// In total they collect `1 + 1 + 1 + 1 = 4` fruits.
// ```
//
// **Constraints:**
//
// - `2 <= n == fruits.length == fruits[i].length <= 1000`
// - `0 <= fruits[i][j] <= 1000`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// Note that the children will make exactly n-1 moves to (n-1, n-1).
// The first child must do diagonally, we move it first.
//
// Since the first child uses took all fruits on the diagonal,
// the second/third child must stay in the upper/lower triangle.
//
// We can use DP to find the solution.
class Solution {
 public:
  int maxCollectedFruits(vector<vector<int>>& fruits) {
    int n = fruits.size();

    vector<int> curr(n);
    vector<int> next(n);

    // First child
    auto ans = 0;
    for (auto i = 0; i < n; i++) {
      ans += fruits[i][i];
    }

    // Second child
    fill(curr.begin(), curr.end(), 0);
    curr[n - 1] = fruits[0][n - 1];
    for (auto i = 1; i < n - 1; i++) {
      fill(next.begin(), next.end(), 0);
      for (auto j = max(i + 1, n - i - 1); j < n; j++) {
        next[j] = curr[j];
        if (j - 1 >= 0) next[j] = max(next[j], curr[j - 1]);
        if (j + 1 < n) next[j] = max(next[j], curr[j + 1]);
        next[j] += fruits[i][j];
      }
      curr.swap(next);
    }
    ans += curr[n - 1];

    // Third child
    fill(curr.begin(), curr.end(), 0);
    curr[n - 1] = fruits[n - 1][0];
    for (auto j = 1; j < n - 1; j++) {
      fill(next.begin(), next.end(), 0);
      for (auto i = max(j + 1, n - j - 1); i < n; i++) {
        next[i] = curr[i];
        if (i - 1 >= 0) next[i] = max(next[i], curr[i - 1]);
        if (i + 1 < n) next[i] = max(next[i], curr[i + 1]);
        next[i] += fruits[i][j];
      }
      curr.swap(next);
    }
    ans += curr[n - 1];

    return ans;
  }
};
