// Source: https://leetcode.com/problems/finding-the-number-of-visible-mountains
// Title: Finding the Number of Visible Mountains
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a **0-indexed** 2D integer array `peaks` where `peaks[i] = [x_i, y_i]` states that mountain `i` has a peak at coordinates `(x_i, y_i)`. A mountain can be described as a right-angled isosceles triangle, with its base along the `x`-axis and a right angle at its peak. More formally, the **gradients** of ascending and descending the mountain are `1` and `-1` respectively.
//
// A mountain is considered **visible** if its peak does not lie within another mountain (including the border of other mountains).
//
// Return the number of visible mountains.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2022/07/19/ex1.png
//
// ```
// Input: peaks = [[2,2],[6,3],[5,4]]
// Output: 2
// Explanation: The diagram above shows the mountains.
// - Mountain 0 is visible since its peak does not lie within another mountain or its sides.
// - Mountain 1 is not visible since its peak lies within the side of mountain 2.
// - Mountain 2 is visible since its peak does not lie within another mountain or its sides.
// There are 2 mountains that are visible.```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2022/07/19/ex2new1.png
//
// ```
// Input: peaks = [[1,3],[1,3]]
// Output: 0
// Explanation: The diagram above shows the mountains (they completely overlap).
// Both mountains are not visible since their peaks lie within each other.
// ```
//
// **Constraints:**
//
// - `1 <= peaks.length <= 10^5`
// - `peaks[i].length == 2`
// - `1 <= x_i, y_i <= 10^5`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <climits>
#include <vector>

using namespace std;

// Sort
//
// First sort the peaks by x. For peaks with the same x, only keeps the highest one.
//
// Let z = y+x, represent the right side slope level of each peak.
// Loop the peaks from left to right.
// A peak is invisible if any peak to the left has greater slope level.
//
// Let w = y-x, represent the left side slope level of each peak.
// Loop the peaks from right to left.
// A peak is invisible if any peak to the right has greater slope level.
class Solution {
 public:
  int visibleMountains(vector<vector<int>>& peaks_) {
    int n = peaks_.size();
    auto visible = vector<bool>(n, true);

    // Prepare
    auto peaks = vector<pair<int, int>>();
    for (auto& peakVec : peaks_) peaks.push_back({peakVec[0], peakVec[1]});

    // Sort
    sort(peaks.begin(), peaks.end());

    // Left to right
    auto maxZ = INT_MIN;
    for (auto i = 0; i < n; ++i) {
      auto [x, y] = peaks[i];
      auto z = y + x;
      if (z <= maxZ) visible[i] = false;
      maxZ = max(maxZ, z);
    }

    // Right to left
    auto maxW = INT_MIN;
    for (auto i = n - 1; i >= 0; --i) {
      auto [x, y] = peaks[i];
      auto w = y - x;
      if (w <= maxW) visible[i] = false;
      maxW = max(maxW, w);
    }

    // Answer
    auto ans = count(visible.cbegin(), visible.cend(), true);

    return ans;
  }
};
