// Source: https://leetcode.com/problems/ransom-note
// Title: Ransom Note
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an `m x n` `matrix`, return all elements of the `matrix` in spiral order.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2020/11/13/spiral1.jpg
//
// ```
// Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
// Output: [1,2,3,6,9,8,7,4,5]
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2020/11/13/spiral.jpg
//
// ```
// Input: matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
// Output: [1,2,3,4,8,12,11,10,9,5,6,7]
// ```
//
// **Constraints:**
//
// - `m == matrix.length`
// - `n == matrix[i].length`
// - `1 <= m, n <= 10`
// - `-100 <= matrix[i][j] <= 100`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <array>
#include <string>
using namespace std;

// Use counter
class Solution {
 public:
  bool canConstruct(string ransomNote, string magazine) {
    array<int, 26> rCounter;
    array<int, 26> mCounter;

    for (auto ch : ransomNote) {
      rCounter[ch - 'a']++;
    }
    for (auto ch : magazine) {
      mCounter[ch - 'a']++;
    }

    for (int ch = 0; ch < 26; ch++) {
      if (rCounter[ch] > mCounter[ch]) {
        return false;
      }
    }

    return true;
  }
};
