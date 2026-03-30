// Source: https://leetcode.com/problems/matrix-similarity-after-cyclic-shifts
// Title: Matrix Similarity After Cyclic Shifts
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an `m x n` integer matrix `mat` and an integer `k`. The matrix rows are 0-indexed.
//
// The following proccess happens `k` times:
//
// - **Even-indexed** rows (0, 2, 4, ...) are cyclically shifted to the left.
//
// https://assets.leetcode.com/uploads/2024/05/19/lshift.jpg
//
// - **Odd-indexed** rows (1, 3, 5, ...) are cyclically shifted to the right.
//
// https://assets.leetcode.com/uploads/2024/05/19/rshift-stlone.jpg
//
// Return `true` if the final modified matrix after `k` steps is identical to the original matrix, and `false` otherwise.
//
// **Example 1:**
//
// ```
// Input: mat = [[1,2,3],[4,5,6],[7,8,9]], k = 4
// Output: false
// Explanation:
// In each step left shift is applied to rows 0 and 2 (even indices), and right shift to row 1 (odd index).
// https://assets.leetcode.com/uploads/2024/05/19/t1-2.jpg
// ```
//
// **Example 2:**
//
// ```
// Input: mat = [[1,2,1,2],[5,5,5,5],[6,3,6,3]], k = 2
// Output: true
// Explanation:
// https://assets.leetcode.com/uploads/2024/05/19/t1-3.jpg
// ```
//
// **Example 3:**
//
// ```
// Input: mat = [[2,2],[2,2]], k = 3
// Output: true
// Explanation:
// As all the values are equal in the matrix, even after performing cyclic shifts the matrix will remain the same.
// ```
//
// **Constraints:**
//
// - `1 <= mat.length <= 25`
// - `1 <= mat[i].length <= 25`
// - `1 <= mat[i][j] <= 25`
// - `1 <= k <= 50`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// For even rows, we check if row[i] == row[i+k] (cyclicly).
// For odd rows, we check if row[i] == row[i-k] (cyclicly).
//
// Note that both conditions are identical.
// Both implies row[i-k] == row[i] == row[i+k] (cyclicly).
class Solution {
 public:
  bool areSimilar(const vector<vector<int>>& mat, int k) {
    const int m = mat.size(), n = mat[0].size();

    // Normalize input
    k %= n;

    // Trivial case
    if (k == 0) return true;

    // Loop
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (mat[i][j] != mat[i][(j + k) % n]) return false;
      }
    }

    return true;
  }
};
