// Source: https://leetcode.com/problems/set-intersection-size-at-least-two
// Title: Set Intersection Size At Least Two
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a 2D integer array `intervals` where `intervals[i] = [start_i, end_i]` represents all the integers from `start_i` to `end_i` inclusively.
//
// A **containing set** is an array `nums` where each interval from `intervals` has **at least two** integers in `nums`.
//
// - For example, if `intervals = [[1,3], [3,7], [8,9]]`, then `[1,2,4,7,8,9]` and `[2,3,4,8,9]` are **containing sets**.
//
// Return the minimum possible size of a containing set.
//
// **Example 1:**
//
// ```
// Input: intervals = [[1,3],[3,7],[8,9]]
// Output: 5
// Explanation: let nums = [2, 3, 4, 8, 9].
// It can be shown that there cannot be any containing array of size 4.
// ```
//
// **Example 2:**
//
// ```
// Input: intervals = [[1,3],[1,4],[2,5],[3,5]]
// Output: 3
// Explanation: let nums = [2, 3, 4].
// It can be shown that there cannot be any containing array of size 2.
// ```
//
// **Example 3:**
//
// ```
// Input: intervals = [[1,2],[2,3],[2,4],[4,5]]
// Output: 5
// Explanation: let nums = [1, 2, 3, 4, 5].
// It can be shown that there cannot be any containing array of size 4.
// ```
//
// **Constraints:**
//
// - `1 <= intervals.length <= 3000`
// - `intervals[i].length == 2`
// - `0 <= start_i < end_i <= 10^8`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

// Greedy + Sort
//
// Sort intervals by end. For intervals with same end, put the larger start at front.
//
// For each interval, pick rightmost numbers if needed.
class Solution {
  using Interval = pair<int, int>;

 public:
  int intersectionSizeTwo(vector<vector<int>>& intervals) {
    // Sort by start
    auto comp = [](vector<int>& a, vector<int>& b) -> bool {
      return a[1] != b[1] ? a[1] < b[1] : a[0] > b[0];  //
    };
    sort(intervals.begin(), intervals.end(), comp);

    // Loop
    auto ans = 0;
    auto x = -1, y = -1;  // the two numbers, x < y
    for (auto& interval : intervals) {
      auto l = interval[0], r = interval[1];
      if (l > y) {  // discard x & y
        x = r - 1;
        y = r;
        ans += 2;
      } else if (l > x) {  // discard x
        x = y;
        y = r;
        ans += 1;
      }
    }

    return ans;
  }
};
