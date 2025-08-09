// Source: https://leetcode.com/problems/insert-interval
// Title: Insert Interval
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an array of non-overlapping intervals `intervals` where `intervals[i] = [start_i, end_i]` represent the start and the end of the `i^th` interval and `intervals` is sorted in ascending order by `start_i`. You are also given an interval `newInterval = [start, end]` that represents the start and end of another interval.
//
// Insert `newInterval` into `intervals` such that `intervals` is still sorted in ascending order by `start_i` and `intervals` still does not have any overlapping intervals (merge overlapping intervals if necessary).
//
// Return `intervals` after the insertion.
//
// **Note** that you don't need to modify `intervals` in-place. You can make a new array and return it.
//
// **Example 1:**
//
// ```
// Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
// Output: [[1,5],[6,9]]
// ```
//
// **Example 2:**
//
// ```
// Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
// Output: [[1,2],[3,10],[12,16]]
// Explanation: Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].
// ```
//
// **Constraints:**
//
// - `0 <= intervals.length <= 10^4`
// - `intervals[i].length == 2`
// - `0 <= start_i <= end_i <= 10^5`
// - `intervals` is sorted by `start_i` in **ascending** order.
// - `newInterval.length == 2`
// - `0 <= start <= end <= 10^5`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

#include "../../utils/print.hpp"

using namespace std;

class Solution {
 public:
  vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
    int n = intervals.size();
    auto ans = vector<vector<int>>();

    // Lower
    int i = 0;
    for (; i < n && intervals[i][1] < newInterval[0]; i++) {
      ans.push_back(intervals[i]);
    }

    // New
    for (; i < n && !(newInterval[1] < intervals[i][0]); i++) {
      auto interval = intervals[i];
      newInterval[0] = min(newInterval[0], interval[0]);
      newInterval[1] = max(newInterval[1], interval[1]);
    }
    ans.push_back(newInterval);

    // Upper
    for (; i < n; i++) {
      ans.push_back(intervals[i]);
    }

    return ans;
  }
};
