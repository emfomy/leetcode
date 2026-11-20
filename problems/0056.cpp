// Source: https://leetcode.com/problems/merge-intervals
// Title: Merge Intervals
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an arrayof `intervals`where `intervals[i] = [start_i, end_i]`, merge all overlapping intervals, and return an array of the non-overlapping intervals that cover all the intervals in the input.
//
// **Example 1:**
//
// ```
// Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
// Output: [[1,6],[8,10],[15,18]]
// Explanation: Since intervals [1,3] and [2,6] overlap, merge them into [1,6].
// ```
//
// **Example 2:**
//
// ```
// Input: intervals = [[1,4],[4,5]]
// Output: [[1,5]]
// Explanation: Intervals [1,4] and [4,5] are considered overlapping.
// ```
//
// **Example 3:**
//
// ```
// Input: intervals = [[4,7],[1,4]]
// Output: [[1,7]]
// Explanation: Intervals [1,4] and [4,7] are considered overlapping.
// ```
//
// **Constraints:**
//
// - `1 <= intervals.length <= 10^4`
// - `intervals[i].length == 2`
// - `0 <= start_i <= end_i <= 10^4`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

using namespace std;

// Sort
class Solution {
 public:
  vector<vector<int>> merge(vector<vector<int>>& intervals) {
    if (intervals.empty()) return {};
    // Sort
    const auto comp = [](const vector<int>& a, const vector<int>& b) -> bool { return a[0] < b[0]; };
    sort(intervals.begin(), intervals.end(), comp);

    // Merge
    auto merged = vector<vector<int>>();
    int currStart = intervals[0][0], currEnd = intervals[0][1];
    for (const auto& interval : intervals) {
      const int start = interval[0], end = interval[1];
      if (start > currEnd) {
        merged.push_back({currStart, currEnd});
        currStart = start;
      }
      currEnd = max(currEnd, end);
    }
    merged.push_back({currStart, currEnd});

    return merged;
  }
};

// Sort + Line Sweep
class Solution2 {
  // we want to sort START before END since [a, b] & [b, c] is consider overlapping.
  enum Label { START = 0, END = 1 };

  using Point = pair<int, Label>;

 public:
  vector<vector<int>> merge(const vector<vector<int>>& intervals) {
    if (intervals.empty()) return {};
    const int n = intervals.size();

    // Sort points
    auto points = vector<Point>();
    points.reserve(2 * n);
    for (const auto& interval : intervals) {
      points.emplace_back(interval[0], START);
      points.emplace_back(interval[1], END);
    }
    sort(points.begin(), points.end());

    // Loop
    auto merged = vector<vector<int>>();
    int startIdx = -1;
    int count = 0;  // number of active intervals
    for (const auto [idx, label] : points) {
      // Start of a merged interval
      if (count == 0) {
        startIdx = idx;
      }

      count += (label == START) ? +1 : -1;

      // End of a merged interval
      if (count == 0) {
        merged.push_back({startIdx, idx});
      }
    }

    return merged;
  }
};
