// Source: https://leetcode.com/problems/pascals-triangle-ii
// Title: Pascal's Triangle II
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer `rowIndex`, return the `rowIndex^th` (**0-indexed**) row of the **Pascal's triangle**.
//
// In **Pascal's triangle**, each number is the sum of the two numbers directly above it as shown:
// https://upload.wikimedia.org/wikipedia/commons/0/0d/PascalTriangleAnimated2.gif
//
// **Example 1:**
//
// ```
// Input: rowIndex = 3
// Output: [1,3,3,1]
// ```
//
// **Example 2:**
//
// ```
// Input: rowIndex = 0
// Output: [1]
// ```
//
// **Example 3:**
//
// ```
// Input: rowIndex = 1
// Output: [1,1]
// ```
//
// **Constraints:**
//
// - `0 <= rowIndex <= 33`
//
// **Follow up:** Could you optimize your algorithm to use only `O(rowIndex)` extra space?
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <utility>
#include <vector>

using namespace std;

// DP
class Solution {
 public:
  vector<int> getRow(int rowIndex) {
    auto prevRow = vector<int>(rowIndex + 1);
    auto currRow = vector<int>(rowIndex + 1);
    currRow[0] = 1;
    for (int r = 1; r <= rowIndex; ++r) {
      swap(currRow, prevRow);
      currRow[0] = 1;
      currRow[r] = 1;
      for (int c = 1; c < r; ++c) {
        currRow[c] = prevRow[c - 1] + prevRow[c];
      }
    }

    return currRow;
  }
};

// DP, single array
class Solution2 {
 public:
  vector<int> getRow(int rowIndex) {
    auto row = vector<int>(rowIndex + 1);
    row[0] = 1;
    for (int r = 1; r <= rowIndex; ++r) {
      for (int c = r; c > 0; --c) {
        row[c] += row[c - 1];
      }
    }

    return row;
  }
};
