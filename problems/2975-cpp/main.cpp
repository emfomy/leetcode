// Source: https://leetcode.com/problems/maximum-square-area-by-removing-fences-from-a-field
// Title: Maximum Square Area by Removing Fences From a Field
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There is a large `(m - 1) x (n - 1)` rectangular field with corners at `(1, 1)` and `(m, n)` containing some horizontal and vertical fences given in arrays `hFences` and `vFences` respectively.
//
// Horizontal fences are from the coordinates `(hFences[i], 1)` to `(hFences[i], n)` and vertical fences are from the coordinates `(1, vFences[i])` to `(m, vFences[i])`.
//
// Return the **maximum** area of a **square** field that can be formed by **removing** some fences (**possibly none**) or `-1` if it is impossible to make a square field.
//
// Since the answer may be large, return it **modulo** `10^9 + 7`.
//
// **Note: **The field is surrounded by two horizontal fences from the coordinates `(1, 1)` to `(1, n)` and `(m, 1)` to `(m, n)` and two vertical fences from the coordinates `(1, 1)` to `(m, 1)` and `(1, n)` to `(m, n)`. These fences **cannot** be removed.
//
// **Example 1:**
//
// https://assets.leetcode.com/uploads/2023/11/05/screenshot-from-2023-11-05-22-40-25.png
//
// ```
// Input: m = 4, n = 3, hFences = [2,3], vFences = [2]
// Output: 4
// Explanation: Removing the horizontal fence at 2 and the vertical fence at 2 will give a square field of area 4.
// ```
//
// **Example 2:**
//
// https://assets.leetcode.com/uploads/2023/11/22/maxsquareareaexample1.png
//
// ```
// Input: m = 6, n = 7, hFences = [2], vFences = [4]
// Output: -1
// Explanation: It can be proved that there is no way to create a square field by removing fences.
// ```
//
// **Constraints:**
//
// - `3 <= m, n <= 10^9`
// - `1 <= hFences.length, vFences.length <= 600`
// - `1 < hFences[i] < m`
// - `1 < vFences[i] < n`
// - `hFences` and `vFences` are unique.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <unordered_set>
#include <vector>

using namespace std;

// Convert hFences & vFences into hash sets.
// For each possible square side size,
// loop through all fences and check if such gap exists.
class Solution {
  constexpr static int64_t modulo = 1e9 + 7;

 public:
  int maximizeSquareArea(int m, int n, vector<int>& hFences, vector<int>& vFences) {
    // Sort
    hFences.push_back(1);
    hFences.push_back(m);
    vFences.push_back(1);
    vFences.push_back(n);
    sort(hFences.begin(), hFences.end());
    sort(vFences.begin(), vFences.end());

    // Find sides
    auto hSides = unordered_set<int>();
    auto vSides = unordered_set<int>();
    for (auto i = 0; i < hFences.size(); ++i) {
      for (auto j = 0; j < i; ++j) {
        hSides.insert(hFences[i] - hFences[j]);
      }
    }
    for (auto i = 0; i < vFences.size(); ++i) {
      for (auto j = 0; j < i; ++j) {
        vSides.insert(vFences[i] - vFences[j]);
      }
    }

    // Compare
    auto side = -1;
    for (auto hSide : hSides) {
      if (vSides.contains(hSide)) side = max(side, hSide);
    }

    if (side == -1) return -1;
    return (int64_t(side) * int64_t(side)) % modulo;
  }
};
