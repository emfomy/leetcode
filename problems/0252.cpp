// Source: https://leetcode.com/problems/meeting-rooms
// Title: Meeting Rooms
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array of meeting time `intervals`where `intervals[i] = [start_i, end_i]`, determine if a person could attend all meetings.
//
// **Example 1:**
//
// ```
// Input: intervals = [[0,30],[5,10],[15,20]]
// Output: false
// ```
//
// **Example 2:**
//
// ```
// Input: intervals = [[7,10],[2,4]]
// Output: true
// ```
//
// **Constraints:**
//
// - `0 <= intervals.length <= 10^4`
// - `intervals[i].length == 2`
// - `0 <= start_i <end_i <= 10^6`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

using namespace std;

// Sort + Sweep Line
//
// Sort each time point.
// It should alternative between START and END.
class Solution {
  enum Label { START = 1, END = -1 };  // START > END since the meeting is closed-open
  using Point = pair<int, Label>;

 public:
  int canAttendMeetings(const vector<vector<int>>& intervals) {
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
    int prevLabel = END;
    for (auto [_, label] : points) {
      if (prevLabel == label) return false;
      prevLabel = label;
    }

    return true;
  }
};
