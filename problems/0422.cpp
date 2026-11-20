// Source: https://leetcode.com/problems/valid-word-square
// Title: Valid Word Square
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array of strings `words`, return `true` if it forms a valid **word square**.
//
// A sequence of strings forms a valid **word square** if the `k^th` row and column read the same string, where `0 <= k < max(numRows, numColumns)`.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/04/09/validsq1-grid.jpg
//
// ```
// Input: words = ["abcd","bnrt","crmy","dtye"]
// Output: true
// Explanation:
// The 1^st row and 1^st column both read "abcd".
// The 2^nd row and 2^nd column both read "bnrt".
// The 3^rd row and 3^rd column both read "crmy".
// The 4^th row and 4^th column both read "dtye".
// Therefore, it is a valid word square.
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2021/04/09/validsq2-grid.jpg
//
// ```
// Input: words = ["abcd","bnrt","crm","dt"]
// Output: true
// Explanation:
// The 1^st row and 1^st column both read "abcd".
// The 2^nd row and 2^nd column both read "bnrt".
// The 3^rd row and 3^rd column both read "crm".
// The 4^th row and 4^th column both read "dt".
// Therefore, it is a valid word square.
// ```
//
// **Example 3:**
// https://assets.leetcode.com/uploads/2021/04/09/validsq3-grid.jpg
//
// ```
// Input: words = ["ball","area","read","lady"]
// Output: false
// Explanation:
// The 3^rd row reads "read" while the 3^rd column reads "lead".
// Therefore, it is NOT a valid word square.
// ```
//
// **Constraints:**
//
// - `1 <= words.length <= 500`
// - `1 <= words[i].length <= 500`
// - `words[i]` consists of only lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>

using namespace std;

class Solution {
 public:
  bool validWordSquare(vector<string>& words) {
    const int n = words.size();

    for (int row = 0; row < n; ++row) {
      if (words[row].size() > n) return false;
      for (int col = 0; col < row; ++col) {
        char lower = col < words[row].size() ? words[row][col] : '\0';
        char upper = row < words[col].size() ? words[col][row] : '\0';
        if (lower != upper) return false;
      }
    }

    return true;
  }
};
