// Source: https://leetcode.com/problems/number-of-laser-beams-in-a-bank
// Title: Number of Laser Beams in a Bank
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Anti-theft security devices are activated inside a bank. You are given a **0-indexed** binary string array `bank` representing the floor plan of the bank, which is an `m x n` 2D matrix. `bank[i]` represents the `i^th` row, consisting of `'0'`s and `'1'`s. `'0'` means the cell is empty, while`'1'` means the cell has a security device.
//
// There is **one** laser beam between any **two** security devices **if both** conditions are met:
//
// - The two devices are located on two **different rows**: `r_1` and `r_2`, where `r_1 < r_2`.
// - For **each** row `i` where `r_1 < i < r_2`, there are **no security devices** in the `i^th` row.
//
// Laser beams are independent, i.e., one beam does not interfere nor join with another.
//
// Return the total number of laser beams in the bank.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/12/24/laser1.jpg
//
// ```
// Input: bank = ["011001","000000","010100","001000"]
// Output: 8
// Explanation: Between each of the following device pairs, there is one beam. In total, there are 8 beams:
//  * bank[0][1] -- bank[2][1]
//  * bank[0][1] -- bank[2][3]
//  * bank[0][2] -- bank[2][1]
//  * bank[0][2] -- bank[2][3]
//  * bank[0][5] -- bank[2][1]
//  * bank[0][5] -- bank[2][3]
//  * bank[2][1] -- bank[3][2]
//  * bank[2][3] -- bank[3][2]
// Note that there is no beam between any device on the 0^th row with any on the 3^rd row.
// This is because the 2^nd row contains security devices, which breaks the second condition.
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2021/12/24/laser2.jpg
//
// ```
// Input: bank = ["000","111","000"]
// Output: 0
// Explanation: There does not exist two devices located on two different rows.
// ```
//
// **Constraints:**
//
// - `m == bank.length`
// - `n == bank[i].length`
// - `1 <= m, n <= 500`
// - `bank[i][j]` is either `'0'` or `'1'`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

using namespace std;

// O(n) time, O(1) space
// Sum of products of devices count between adjacency rows. Skipping empty rows.
class Solution {
 public:
  int numberOfBeams(vector<string>& bank) {
    auto ans = 0;
    auto prevCount = 0;
    for (auto row : bank) {
      auto currCount = count(row.cbegin(), row.cend(), '1');
      if (currCount == 0) continue;
      ans += currCount * prevCount;
      prevCount = currCount;
    }
    return ans;
  }
};
