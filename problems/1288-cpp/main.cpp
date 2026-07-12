// Source: https://leetcode.com/problems/remove-covered-intervals
// Title: Remove Covered Intervals
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array `intervals` where `intervals[i] = [l_i, r_i]` represent the interval `[l_i, r_i)`, remove all intervals that are covered by another interval in the list.
//
// The interval `[a, b)` is covered by the interval `[c, d)` if and only if `c <= a` and `b <= d`.
//
// Return the number of remaining intervals.
//
// **Example 1:**
//
// ```
// Input: intervals = [[1,4],[3,6],[2,8]]
// Output: 2
// Explanation: Interval [3,6] is covered by [2,8], therefore it is removed.
// ```
//
// **Example 2:**
//
// ```
// Input: intervals = [[1,4],[2,3]]
// Output: 1
// ```
//
// **Constraints:**
//
// - `1 <= intervals.length <= 1000`
// - `intervals[i].length == 2`
// - `0 <= l_i < r_i <= 10^5`
// - All the given intervals are **unique**.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// Sort
//
// Sort the intervals by their start (ascending) and end (descending).
//
// For any two interval [a, b) and [c, d).
// WLOG, say a <= c. [a, b) covers [c, d) iff. b >= d.
//
// Loop through the sorted array, and tracks the maximum end value.
// If the end of an interval is less than previous maximum, then it is covered.
class Solution {
  using Interval = vector<int>;

 public:
  int removeCoveredIntervals(vector<Interval>& intervals) {
    // Sort
    auto comp = [](const Interval& a, const Interval& b) -> bool {  //
      return a[0] != b[0] ? (a[0] < b[0]) : a[1] > b[1];
    };
    sort(intervals.begin(), intervals.end(), comp);

    // Loop
    int count = 0, maxEnd = -1;
    for (const Interval& interval : intervals) {
      int end = interval[1];
      if (maxEnd < end) {
        ++count;
        maxEnd = end;
      }
    }
    return count;
  }
};
