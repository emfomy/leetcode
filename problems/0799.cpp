// Source: https://leetcode.com/problems/champagne-tower
// Title: Champagne Tower
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// We stack glasses in a pyramid, where the **first** row has `1` glass, the **second** row has `2` glasses, and so on until the 100^th row. Each glass holds one cupof champagne.
//
// Then, some champagne is poured into the first glass at the top. When the topmost glass is full, any excess liquid poured will fall equally to the glass immediately to the left and right of it. When those glasses become full, any excess champagne will fall equally to the left and right of those glasses, and so on. (A glass at the bottom row has its excess champagne fall on the floor.)
//
// For example, after one cup of champagne is poured, the top most glass is full. After two cups of champagne are poured, the two glasses on the second row are half full. After three cups of champagne are poured, those two cups become full - there are 3 full glasses total now. After four cups of champagne are poured, the third row has the middle glass half full, and the two outside glasses are a quarter full, as pictured below.
//
// https://s3-lc-upload.s3.amazonaws.com/uploads/2018/03/09/tower.png
//
// Now after pouring some non-negative integer cups of champagne, return how full the `j^th` glass in the `i^th` row is (both `i` and `j` are 0-indexed.)
//
// **Example 1:**
//
// ```
// Input: poured = 1, query_row = 1, query_glass = 1
// Output: 0.00000
// Explanation: We poured 1 cup of champange to the top glass of the tower (which is indexed as (0, 0)). There will be no excess liquid so all the glasses under the top glass will remain empty.
// ```
//
// **Example 2:**
//
// ```
// Input: poured = 2, query_row = 1, query_glass = 1
// Output: 0.50000
// Explanation: We poured 2 cups of champange to the top glass of the tower (which is indexed as (0, 0)). There is one cup of excess liquid. The glass indexed as (1, 0) and the glass indexed as (1, 1) will share the excess liquid equally, and each will get half cup of champange.
// ```
//
// **Example 3:**
//
// ```
// Input: poured = 100000009, query_row = 33, query_glass = 17
// Output: 1.00000
// ```
//
// **Constraints:**
//
// - `0 <=poured <= 10^9`
// - `0 <= query_glass <= query_row< 100`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <utility>
#include <vector>

using namespace std;

// DP
class Solution {
  // Convert negative to zero
  inline double relu(double x) { return max(x, 0.0); }

  // Return only in range [0, 1]
  inline double clamp(double x) { return min(max(x, 0.0), 1.0); }

 public:
  double champagneTower(const int poured, const int queryRow, const int queryGlass) {
    auto currRow = vector<double>(queryRow + 1);
    currRow[0] = poured;

    for (int row = 0; row < queryRow; ++row) {
      auto nextRow = vector<double>(queryRow + 1);
      for (int col = 0; col <= row; ++col) {
        nextRow[col] += relu(currRow[col] - 1) / 2;
        nextRow[col + 1] += relu(currRow[col] - 1) / 2;
      }
      swap(currRow, nextRow);
    }

    return clamp(currRow[queryGlass]);
  }
};

// DP
class Solution2 {
  // Convert negative to zero
  inline double relu(double x) { return max(x, 0.0); }

  // Return only in range [0, 1]
  inline double clamp(double x) { return min(max(x, 0.0), 1.0); }

 public:
  double champagneTower(const int poured, const int queryRow, const int queryGlass) {
    auto currRow = vector<double>(queryRow + 2);  // use 1-indexed
    auto prevRow = vector<double>(queryRow + 2);  // use 1-indexed
    currRow[1] = poured;

    for (int row = 1; row <= queryRow; ++row) {
      swap(currRow, prevRow);
      for (int col = 1; col <= row + 1; ++col) {
        currRow[col] = relu(prevRow[col - 1] - 1) / 2 + relu(prevRow[col] - 1) / 2;
      }
    }

    return clamp(currRow[queryGlass + 1]);
  }
};
