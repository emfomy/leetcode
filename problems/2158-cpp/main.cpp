// Source: https://leetcode.com/problems/amount-of-new-area-painted-each-day
// Title: Amount of New Area Painted Each Day
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There is a long and thin painting that can be represented by a number line. You are given a **0-indexed** 2D integer array `paint` of length `n`, where `paint[i] = [start_i, end_i]`. This means that on the `i^th` day you need to paint the area **between** `start_i` and `end_i`.
//
// Painting the same area multiple times will create an uneven painting so you only want to paint each area of the painting at most **once**.
//
// Return an integer array `worklog` of length `n`, where `worklog[i]` is the amount of **new** area that you painted on the `i^th` day.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2022/02/01/screenshot-2022-02-01-at-17-16-16-diagram-drawio-diagrams-net.png
//
// ```
// Input: paint = [[1,4],[4,7],[5,8]]
// Output: [3,3,1]
// Explanation:
// On day 0, paint everything between 1 and 4.
// The amount of new area painted on day 0 is 4 - 1 = 3.
// On day 1, paint everything between 4 and 7.
// The amount of new area painted on day 1 is 7 - 4 = 3.
// On day 2, paint everything between 7 and 8.
// Everything between 5 and 7 was already painted on day 1.
// The amount of new area painted on day 2 is 8 - 7 = 1.
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2022/02/01/screenshot-2022-02-01-at-17-17-45-diagram-drawio-diagrams-net.png
//
// ```
// Input: paint = [[1,4],[5,8],[4,7]]
// Output: [3,3,1]
// Explanation:
// On day 0, paint everything between 1 and 4.
// The amount of new area painted on day 0 is 4 - 1 = 3.
// On day 1, paint everything between 5 and 8.
// The amount of new area painted on day 1 is 8 - 5 = 3.
// On day 2, paint everything between 4 and 5.
// Everything between 5 and 7 was already painted on day 1.
// The amount of new area painted on day 2 is 5 - 4 = 1.
// ```
//
// **Example 3:**
// https://assets.leetcode.com/uploads/2022/02/01/screenshot-2022-02-01-at-17-19-49-diagram-drawio-diagrams-net.png
//
// ```
// Input: paint = [[1,5],[2,4]]
// Output: [4,0]
// Explanation:
// On day 0, paint everything between 1 and 5.
// The amount of new area painted on day 0 is 5 - 1 = 4.
// On day 1, paint nothing because everything between 2 and 4 was already painted on day 0.
// The amount of new area painted on day 1 is 0.
// ```
//
// **Constraints:**
//
// - `1 <= paint.length <= 10^5`
// - `paint[i].length == 2`
// - `0 <= start_i < end_i <= 5 * 10^4`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <map>
#include <vector>

using namespace std;

// Line Sweep + Tree Map
//
// Store the painted ranges of each paint in a tree map (map end to start).
//
// For each day, use binary search to find the painted ranges overlaps the new range.
// We loop through these ranges, compute their sizes,
// merge with the new range, and remove them.
class Solution {
 public:
  vector<int> amountPainted(const vector<vector<int>>& paint) {
    const int n = paint.size();
    auto areas = vector<int>(n);

    auto ranges = map<int, int>();  // end -> start
    for (int i = 0; i < n; ++i) {
      int newStart = paint[i][0], newEnd = paint[i][1];

      // Count area
      int oldArea = 0;
      auto firstIt = ranges.lower_bound(newStart);
      auto lastIt = firstIt;
      for (; lastIt != ranges.cend(); ++lastIt) {
        auto [end, start] = *lastIt;
        if (start > newEnd) break;  // no overlap

        oldArea += (end - start);  // exclude painted ranges
        newStart = min(newStart, start);
        newEnd = max(newEnd, end);
      }
      int newArea = (newEnd - newStart);  // newly painted range
      areas[i] = newArea - oldArea;

      // Update
      ranges.erase(firstIt, lastIt);
      ranges[newEnd] = newStart;
    }

    return areas;
  }
};

// Union Find
//
// We use an array for each tile.
// If a tile is painted, we store the end index for that tile.
//
// For each day, we loop through the new range,
// converting all empty tile to the end of the new range.
// If we found a painted tile, we directly jump to the end index of that tile.
//
// Note that we also do the path compression
// by converting the that painted tile to the end of the new range.
class Solution2 {
  constexpr static int maxX = 5e4;

 public:
  vector<int> amountPainted(const vector<vector<int>>& paint) {
    const int n = paint.size();
    auto areas = vector<int>(n);

    auto endIdxs = vector<int>(maxX + 1);
    for (int i = 0; i < n; ++i) {
      const int start = paint[i][0], end = paint[i][1];

      int area = 0;
      int x = start;
      while (x < end) {
        if (endIdxs[x] > 0) {
          int nextX = endIdxs[x];
          endIdxs[x] = end;  // compress
          x = nextX;         // jump
        } else {
          ++area;
          endIdxs[x] = end;
          ++x;
        }

        areas[i] = area;
      }
    }

    return areas;
  }
};
