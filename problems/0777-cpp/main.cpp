// Source: https://leetcode.com/problems/swap-adjacent-in-lr-string
// Title: Swap Adjacent in LR String
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// In a string composed of `'L'`, `'R'`, and `'X'` characters, like `"RXXLRXRXL"`, a move consists of either replacing one occurrence of `"XL"` with `"LX"`, or replacing one occurrence of `"RX"` with `"XR"`. Given the starting string `start` and the ending string `result`, return `True` if and only if there exists a sequence of moves to transform `start` to `result`.

// **Example 1:**

// ```
// Input: start = "RXXLRXRXL", result = "XRLXXRRLX"
// Output: true
// Explanation: We can transform start to result following these steps:
// RXXLRXRXL ->
// XRXLRXRXL ->
// XRLXRXRXL ->
// XRLXXRRXL ->
// XRLXXRRLX
// ```

// **Example 2:**

// ```
// Input: start = "X", result = "L"
// Output: false
// ```

// **Constraints:**

// - `1 <= start.length<= 10^4`
// - `start.length == result.length`
// - Both `start` and `result` will only consist of characters in `'L'`, `'R'`, and`'X'`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <string>

using namespace std;

// Two pointer
//
// Loop through both string and skip all X.
// Compare non-X characters. Denote them as `s` in start and `t` in result.
// If s != t, then return false (impossible).
// If s = t = 'L', then index of t must be left of s.
// If s = t = 'R', then index of t must be right of s.
class Solution {
 public:
  bool canTransform(string start, string result) {
    // Count X
    if (count(start.cbegin(), start.cend(), 'X') != count(result.cbegin(), result.cend(), 'X')) return false;

    int n = start.size();
    auto i = 0, j = 0;
    while (i < n || j < n) {
      // Skip X
      while (i < n && start[i] == 'X') ++i;
      while (j < n && result[j] == 'X') ++j;

      // Check end
      if (i == n || j == n) return i == j;

      // Check characters
      if (start[i] != result[j]) return false;
      if (start[i] == 'L' && j > i) return false;
      if (start[i] == 'R' && j < i) return false;

      ++i;
      ++j;
    }

    return true;
  }
};
