// Source: https://leetcode.com/problems/two-best-non-overlapping-events
// Title: Two Best Non-Overlapping Events
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a **0-indexed** 2D integer array of `events` where `events[i] = [startTime_i, endTime_i, value_i]`. The `i^th` event starts at `startTime_i` and ends at `endTime_i`, and if you attend this event, you will receive a value of `value_i`. You can choose **at most** **two** **non-overlapping** events to attend such that the sum of their values is **maximized**.
//
// Return this **maximum** sum.
//
// Note that the start time and end time is **inclusive** : that is, you cannot attend two events where one of them starts and the other ends at the same time. More specifically, if you attend an event with end time `t`, the next event must start at or after `t + 1`.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/09/21/picture5.png
//
// ```
// Input: events = [[1,3,2],[4,5,2],[2,4,3]]
// Output: 4
// Explanation: Choose the green events, 0 and 1 for a sum of 2 + 2 = 4.
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2021/09/21/picture1.png
//
// ```
// Input: events = [[1,3,2],[4,5,2],[1,5,5]]
// Output: 5
// Explanation: Choose event 2 for a sum of 5.
// ```
//
// **Example 3:**
// https://assets.leetcode.com/uploads/2021/09/21/picture3.png
//
// ```
// Input: events = [[1,5,3],[1,5,1],[6,6,5]]
// Output: 8
// Explanation: Choose events 0 and 2 for a sum of 3 + 5 = 8.```
//
// **Constraints:**
//
// - `2 <= events.length <= 10^5`
// - `events[i].length == 3`
// - `1 <= startTime_i <= endTime_i <= 10^9`
// - `1 <= value_i <= 10^6`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <functional>
#include <queue>
#include <vector>

using namespace std;

// Sort + Heap
//
// First sort events by start time.
//
// Loop for each event.
// Push the ended event into a heap (ordered by end time).
// Track the maximum value of ended events.
class Solution {
  using Event = vector<int>;
  using EndEvent = pair<int, int>;  // (end time, value)

 public:
  int maxTwoEvents(vector<Event> &events) {
    int n = events.size();

    // Sort by end time
    sort(events.begin(), events.end(), [](Event &a, Event &b) -> bool { return a[0] < b[0]; });

    // Heap
    auto heap = priority_queue(greater(), std::move(vector<EndEvent>()));  // min-heap

    // Loop
    auto ans = 0;
    auto leftIdx = 0;
    auto maxValue = 0;
    for (auto &event : events) {
      auto start = event[0], end = event[1], value = event[2];

      while (!heap.empty() && heap.top().first < start) {
        maxValue = max(maxValue, heap.top().second);
        heap.pop();
      }

      ans = max(ans, maxValue + value);
      heap.push({end, value});
    }

    return ans;
  }
};
