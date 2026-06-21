// Source: https://leetcode.com/problems/maximum-building-height
// Title: Maximum Building Height
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You want to build `n` new buildings in a city. The new buildings will be built in a line and are labeled from `1` to `n`.
//
// However, there are city restrictions on the heights of the new buildings:
//
// - The height of each building must be a non-negative integer.
// - The height of the first building **must** be `0`.
// - The height difference between any two adjacent buildings **cannot exceed** `1`.
//
// Additionally, there are city restrictions on the maximum height of specific buildings. These restrictions are given as a 2D integer array `restrictions` where `restrictions[i] = [id_i, maxHeight_i]` indicates that building `id_i` must have a height **less than or equal to** `maxHeight_i`.
//
// It is guaranteed that each building will appear **at most once** in `restrictions`, and building `1` will **not** be in `restrictions`.
//
// Return the **maximum possible height** of the **tallest** building.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/04/08/ic236-q4-ex1-1.png
//
// ```
// Input: n = 5, restrictions = [[2,1],[4,1]]
// Output: 2
// Explanation: The green area in the image indicates the maximum allowed height for each building.
// We can build the buildings with heights [0,1,2,1,2], and the tallest building has a height of 2.```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2021/04/08/ic236-q4-ex2.png
//
// ```
// Input: n = 6, restrictions = []
// Output: 5
// Explanation: The green area in the image indicates the maximum allowed height for each building.
// We can build the buildings with heights [0,1,2,3,4,5], and the tallest building has a height of 5.
// ```
//
// **Example 3:**
// https://assets.leetcode.com/uploads/2021/04/08/ic236-q4-ex3.png
//
// ```
// Input: n = 10, restrictions = [[5,3],[2,5],[7,4],[10,3]]
// Output: 5
// Explanation: The green area in the image indicates the maximum allowed height for each building.
// We can build the buildings with heights [0,1,2,3,3,4,4,5,4,3], and the tallest building has a height of 5.
// ```
//
// **Constraints:**
//
// - `2 <= n <= 10^9`
// - `0 <= restrictions.length <= min(n - 1, 10^5)`
// - `2 <= id_i <= n`
// - `id_i`is **unique**.
// - `0 <= maxHeight_i <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// Sort + Greedy
//
// Say we have two restriction (a, A) and (b, B). WLOG, a < b.
// We want to find the maximum building in [a, b].
//
// If A <= B and B > A+(b-a), then we can update B as A+(b-a)
// since the build at b can't not be taller than A+(b-a).
// Similarly to A >= B. We can update A to B+(b-a) if A is too large.
//
// We add two more restrictions (1, 0) and (n, n-1) at the front and the back.
// Next sort the restrictions.
//
// Now we scan from left to right and update the restrictions to the right.
// Next scan from right to left and update the restrictions to the left.
// After above two scanning and updating, all restriction are useful,
// and we can find the maximum building in each segment.
//
// The maximum building in [a, b] is (A+B+(b-a))/2 (flooring).
class Solution {
 public:
  int maxBuilding(int n, vector<vector<int>> &restrictions) {
    // Sort
    auto &&r = restrictions;
    r.push_back({1, 0});      // front sentinel
    r.push_back({n, n - 1});  // back sentinel
    sort(r.begin(), r.end());
    const int m = r.size();

    // Scan
    for (int i = 1; i < m; ++i) {
      int a = r[i - 1][0], b = r[i][0];
      int ha = r[i - 1][1], &hb = r[i][1];
      hb = min(hb, ha + (b - a));
    }
    for (int i = m - 1; i > 0; --i) {
      int a = r[i - 1][0], b = r[i][0];
      int &ha = r[i - 1][1], hb = r[i][1];
      ha = min(ha, hb + (b - a));
    }

    // Find max
    int maxHeight = 0;
    for (int i = 1; i < m; ++i) {
      int a = r[i - 1][0], b = r[i][0];
      int ha = r[i - 1][1], hb = r[i][1];
      maxHeight = max(maxHeight, (ha + hb + (b - a)) / 2);
    }

    return maxHeight;
  }
};
