// Source: https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended-ii
// Title: Maximum Number of Events That Can Be Attended II
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an array of `events` where `events[i] = [startDay_i, endDay_i, value_i]`. The `i^th` event starts at `startDay_i`_ and ends at `endDay_i`, and if you attend this event, you will receive a value of `value_i`. You are also given an integer `k` which represents the maximum number of events you can attend.
//
// You can only attend one event at a time. If you choose to attend an event, you must attend the **entire** event. Note that the end day is **inclusive**: that is, you cannot attend two events where one of them starts and the other ends on the same day.
//
// Return the **maximum sum** of values that you can receive by attending events.
//
// **Example 1:**
//
// https://assets.leetcode.com/uploads/2021/01/10/screenshot-2021-01-11-at-60048-pm.png
//
// ```
// Input: events = [[1,2,4],[3,4,3],[2,3,1]], k = 2
// Output: 7
// Explanation: Choose the green events, 0 and 1 (0-indexed) for a total value of 4 + 3 = 7.```
//
// **Example 2:**
//
// https://assets.leetcode.com/uploads/2021/01/10/screenshot-2021-01-11-at-60150-pm.png
//
// ```
// Input: events = [[1,2,4],[3,4,3],[2,3,10]], k = 2
// Output: 10
// Explanation: Choose event 2 for a total value of 10.
// Notice that you cannot attend any other event as they overlap, and that you do **not** have to attend k events.```
//
// **Example 3:**
//
// **https://assets.leetcode.com/uploads/2021/01/10/screenshot-2021-01-11-at-60703-pm.png**
//
// ```
// Input: events = [[1,1,1],[2,2,2],[3,3,3],[4,4,4]], k = 3
// Output: 9
// Explanation: Although the events do not overlap, you can only attend 3 events. Pick the highest valued three.```
//
// **Constraints:**
//
// - `1 <= k <= events.length`
// - `1 <= k * events.length <= 10^6`
// - `1 <= startDay_i <= endDay_i <= 10^9`
// - `1 <= value_i <= 10^6`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <functional>
#include <queue>
#include <vector>

using namespace std;

// DP + Binary Search
//
// We first sort the events by its start time
//
// Let DP(t, i) be the maximum values for attending t of first i events.
//
// For each event, we may either attend it or skip it.
// If we skip it, we move the next event.
// If we attend it, we use binary search to find next available event (i.e. start after this event's end time).
class Solution {
  struct DFS {
    int n;
    int k;
    const vector<vector<int>>& events;
    vector<vector<int>> memo;

    DFS(const vector<vector<int>>& events, int k)
        : n(events.size()),  //
          k(k),
          events(events),
          memo(k, vector<int>(n, -1)) {}

    int run(int t, int idx) {
      // End
      if (t == k || idx == n) return 0;

      // Cache hit
      int& value = memo[t][idx];
      if (value >= 0) return value;

      // Find next event
      const auto cond = [end = events[idx][1]](const vector<int>& x) -> bool {  //
        return !(x[0] > end);
      };
      int nextIdx = partition_point(events.cbegin() + idx, events.cend(), cond) - events.cbegin();

      // Traverse
      value = max(                              //
          run(t, idx + 1),                      // skip this event
          run(t + 1, nextIdx) + events[idx][2]  // attend this event
      );

      return value;
    }
  };

 public:
  int maxValue(vector<vector<int>>& events, int k) {
    const int n = events.size();

    // Sort
    const auto comp = [](const vector<int>& a, const vector<int>& b) -> bool {  //
      return a[0] < b[0];
    };
    sort(events.begin(), events.end(), comp);

    // DFS
    auto dfs = DFS(events, k);
    return dfs.run(0, 0);
  }
};

// DP + Heap
//
// Instead of binary search, we use heap to precompute the next event.
class Solution2 {
  struct DFS {
    int n;
    int k;
    const vector<vector<int>>& events;
    const vector<int>& nextIdxs;
    vector<vector<int>> memo;

    DFS(const vector<vector<int>>& events, const vector<int>& nextIdxs, int k)
        : n(events.size()),  //
          k(k),
          events(events),
          nextIdxs(nextIdxs),
          memo(k, vector<int>(n, -1)) {}

    int run(int t, int idx) {
      // End
      if (t == k || idx == n) return 0;

      // Cache hit
      int& value = memo[t][idx];
      if (value >= 0) return value;

      // Traverse
      value = max(                                    //
          run(t, idx + 1),                            // skip this event
          run(t + 1, nextIdxs[idx]) + events[idx][2]  // attend this event
      );

      return value;
    }
  };

  using Event = pair<int, int>;  // end time, index

  using Heap = priority_queue<Event, vector<Event>, greater<>>;  // min-heap

 public:
  int maxValue(vector<vector<int>>& events, int k) {
    const int n = events.size();

    // Sort
    const auto comp = [](const vector<int>& a, const vector<int>& b) -> bool {  //
      return a[0] < b[0];
    };
    sort(events.begin(), events.end(), comp);

    // Precompute next event
    auto nextIdxs = vector<int>(n, n);  // default to n, indicate the end iterator
    Heap heap;
    for (int i = 0; i < n; ++i) {
      // Find events finished before current event
      while (!heap.empty() && heap.top().first < events[i][0]) {
        nextIdxs[heap.top().second] = i;
        heap.pop();
      }

      // Put current event into the pool
      heap.push(Event{events[i][1], i});
    }

    // DFS
    auto dfs = DFS(events, nextIdxs, k);
    return dfs.run(0, 0);
  }
};

// DP + Binary Search
//
// Use Button-Up DP instead.
class Solution3 {
 public:
  int maxValue(vector<vector<int>>& events, int k) {
    const int n = events.size();

    // Sort
    const auto comp = [](const vector<int>& a, const vector<int>& b) -> bool {  //
      return a[0] < b[0];
    };
    sort(events.begin(), events.end(), comp);

    // DP
    auto memo = vector(k + 1, vector<int>(n + 1, 0));
    for (int i = n - 1; i >= 0; --i) {
      // Find next event
      const auto cond = [end = events[i][1]](const vector<int>& x) -> bool {  //
        return !(x[0] > end);
      };
      int nextIdx = partition_point(events.cbegin() + i, events.cend(), cond) - events.cbegin();

      for (int t = k - 1; t >= 0; --t) {
        memo[t][i] = max(memo[t][i + 1], memo[t + 1][nextIdx] + events[i][2]);
      }
    }

    return memo[0][0];
  }
};
