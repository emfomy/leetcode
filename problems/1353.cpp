// Source: https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended
// Title: Maximum Number of Events That Can Be Attended
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an array of `events` where `events[i] = [startDay_i, endDay_i]`. Every event `i` starts at `startDay_i`_ and ends at `endDay_i`.
//
// You can attend an event `i` at any day `d` where `startDay_i <= d <= endDay_i`. You can only attend one event at any time `d`.
//
// Return the maximum number of events you can attend.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2020/02/05/e1.png
//
// ```
// Input: events = [[1,2],[2,3],[3,4]]
// Output: 3
// Explanation: You can attend all the three events.
// One way to attend them all is as shown.
// Attend the first event on day 1.
// Attend the second event on day 2.
// Attend the third event on day 3.
// ```
//
// **Example 2:**
//
// ```
// Input: events= [[1,2],[2,3],[3,4],[1,2]]
// Output: 4
// ```
//
// **Constraints:**
//
// - `1 <= events.length <= 10^5`
// - `events[i].length == 2`
// - `1 <= startDay_i <= endDay_i <= 10^5`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <numeric>
#include <queue>
#include <vector>

using namespace std;

// Greedy + Heap
//
// Sort the event by start time.
// Always attend the event that end first.
class Solution {
  using Heap = priority_queue<int, vector<int>, greater<>>;  // min-heap, end time

 public:
  int maxEvents(vector<vector<int>>& events) {
    const int n = events.size();

    // Sort
    const auto comp = [](const vector<int>& a, const vector<int>& b) -> bool {  //
      return a[0] < b[0];
    };
    sort(events.begin(), events.end(), comp);

    // Loop
    Heap heap;
    int now = 0, ans = 0;
    int idx = 0;  // event index
    while (idx < n || !heap.empty()) {
      // Enable started events
      while (idx < n && events[idx][0] <= now) {
        heap.push(events[idx][1]);
        ++idx;
      }

      // Remove finished events
      while (!heap.empty() && heap.top() < now) {
        heap.pop();
      }

      // Attend a event
      if (!heap.empty()) {
        ++ans;
        heap.pop();
      }

      ++now;
    }

    return ans;
  }
};

// Greedy + Heap
class Solution2 {
  using Heap = priority_queue<int, vector<int>, greater<>>;  // min-heap, end time

 public:
  int maxEvents(vector<vector<int>>& events) {
    const int n = events.size();

    // Sort
    const auto comp = [](const vector<int>& a, const vector<int>& b) -> bool {  //
      return a[0] < b[0];
    };
    sort(events.begin(), events.end(), comp);

    // Loop
    Heap heap;
    int now = 0, ans = 0;
    int idx = 0;  // event index
    while (idx < n || !heap.empty()) {
      // Jump to next event
      if (heap.empty()) {
        now = events[idx][0];
      }

      // Enable started events
      while (idx < n && events[idx][0] <= now) {
        heap.push(events[idx][1]);
        ++idx;
      }

      // Attend a event
      heap.pop();
      ++ans;
      ++now;

      // Remove finished events
      while (!heap.empty() && heap.top() < now) {
        heap.pop();
      }
    }

    return ans;
  }
};
