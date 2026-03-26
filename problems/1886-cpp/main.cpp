// Source: https://leetcode.com/problems/determine-whether-matrix-can-be-obtained-by-rotation
// Title: Determine Whether Matrix Can Be Obtained By Rotation
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given two `n x n` binary matrices `mat` and `target`, return `true` if it is possible to make `mat` equal to `target` by **rotating** `mat` in **90-degree increments**, or `false` otherwise.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/05/20/grid3.png
//
// ```
// Input: mat = [[0,1],[1,0]], target = [[1,0],[0,1]]
// Output: true
// Explanation: We can rotate mat 90 degrees clockwise to make mat equal target.
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2021/05/20/grid4.png
//
// ```
// Input: mat = [[0,1],[1,1]], target = [[1,0],[0,1]]
// Output: false
// Explanation: It is impossible to make mat equal to target by rotating mat.
// ```
//
// **Example 3:**
// https://assets.leetcode.com/uploads/2021/05/26/grid4.png
//
// ```
// Input: mat = [[0,0,0],[0,1,0],[1,1,1]], target = [[1,1,1],[0,1,0],[0,0,0]]
// Output: true
// Explanation: We can rotate mat 90 degrees clockwise two times to make mat equal target.
// ```
//
// **Constraints:**
//
// - `n == mat.length == target.length`
// - `n == mat[i].length == target[i].length`
// - `1 <= n <= 10`
// - `mat[i][j]` and `target[i][j]` are either `0` or `1`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

class Solution {
 public:
  bool findRotation(const vector<vector<int>>& mat, const vector<vector<int>>& target) {
    return check0(mat, target) ||    // 0-degree
           check90(mat, target) ||   // 90-degree
           check180(mat, target) ||  // 180-degree
           check270(mat, target);    // 270-degree
  }

  bool check0(const vector<vector<int>>& mat, const vector<vector<int>>& target) {
    const int n = mat.size();
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (mat[i][j] != target[i][j]) return false;
      }
    }
    return true;
  }
  bool check90(const vector<vector<int>>& mat, const vector<vector<int>>& target) {
    const int n = mat.size();
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (mat[i][j] != target[n - j - 1][i]) return false;
      }
    }
    return true;
  }
  bool check180(const vector<vector<int>>& mat, const vector<vector<int>>& target) {
    const int n = mat.size();
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (mat[i][j] != target[n - i - 1][n - j - 1]) return false;
      }
    }
    return true;
  }
  bool check270(const vector<vector<int>>& mat, const vector<vector<int>>& target) {
    const int n = mat.size();
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (mat[i][j] != target[j][n - i - 1]) return false;
      }
    }
    return true;
  }
};
