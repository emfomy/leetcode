// Source: https://leetcode.com/problems/merge-intervals
// Title: Merge Intervals
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array of `intervals`where `intervals[i] = [start_i, end_i]`, merge all overlapping intervals, and return an array of the non-overlapping intervals that cover all the intervals in the input.
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

// Use sort
class Solution {
 public:
  vector<vector<int>> merge(vector<vector<int>>& intervals) {
    int n = intervals.size();

    // Sort
    sort(intervals.begin(), intervals.end(), [](vector<int>& a, vector<int>& b) -> bool { return a[0] < b[0]; });

    // Loop
    vector<vector<int>> ans;
    int left = intervals[0][0];
    int right = intervals[0][1];
    for (auto i = 1; i < n; i++) {
      auto& interval = intervals[i];
      if (interval[0] > right) {  // not overlap
        ans.push_back({left, right});
        left = interval[0];
        right = interval[1];
      } else {
        right = max(right, interval[1]);
      }
    }
    ans.push_back({left, right});

    return ans;
  }
};
