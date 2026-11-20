// Source: https://leetcode.com/problems/meeting-rooms-ii
// Title: Meeting Rooms II
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array of meeting time intervals `intervals` where `intervals[i] = [start_i, end_i]`, return the minimum number of conference rooms required.
//
// **Example 1:**
//
// ```
// Input: intervals = [[0,30],[5,10],[15,20]]
// Output: 2
// ```
//
// **Example 2:**
//
// ```
// Input: intervals = [[7,10],[2,4]]
// Output: 1
// ```
//
// **Constraints:**
//
// - `1 <=intervals.length <= 10^4`
// - `0 <= start_i < end_i <= 10^6`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

using namespace std;

// Sort + Sweep Line
//
// Sort each time point, and track the ongoing meeting count.
class Solution {
  enum Label { START = 1, END = -1 };  // START > END since the meeting is closed-open
  using Point = pair<int, Label>;

 public:
  int minMeetingRooms(const vector<vector<int>>& intervals) {
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
    int maxRooms = 0, rooms = 0;
    for (auto [_, label] : points) {
      rooms += label;
      maxRooms = max(maxRooms, rooms);
    }

    return maxRooms;
  }
};
