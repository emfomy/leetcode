// Source: https://leetcode.com/problems/pascals-triangle
// Title: Pascal's Triangle
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer `numRows`, return the first numRows of **Pascal's triangle**.
//
// In **Pascal's triangle**, each number is the sum of the two numbers directly above it as shown:
// https://upload.wikimedia.org/wikipedia/commons/0/0d/PascalTriangleAnimated2.gif
//
// **Example 1:**
//
// ```
// Input: numRows = 5
// Output: [[1],[1,1],[1,2,1],[1,3,3,1],[1,4,6,4,1]]
// ```
//
// **Example 2:**
//
// ```
// Input: numRows = 1
// Output: [[1]]
// ```
//
// **Constraints:**
//
// - `1 <= numRows <= 30`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

class Solution {
 public:
  vector<vector<int>> generate(int numRows) {
    auto triangle = vector<vector<int>>(numRows);
    for (int r = 0; r < numRows; ++r) {
      vector<int>& row = triangle[r];
      row.resize(r + 1);
      row.front() = 1, row.back() = 1;
      for (int c = 1; c < r; ++c) {
        row[c] = triangle[r - 1][c - 1] + triangle[r - 1][c];
      }
    }
    return triangle;
  }
};
