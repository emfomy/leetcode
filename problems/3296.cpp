// Source: https://leetcode.com/problems/minimum-number-of-seconds-to-make-mountain-height-zero
// Title: Minimum Number of Seconds to Make Mountain Height Zero
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer `mountainHeight` denoting the height of a mountain.
//
// You are also given an integer array `workerTimes` representing the work time of workers in **seconds**.
//
// The workers work **simultaneously** to **reduce** the height of the mountain. For worker `i`:
//
// - To decrease the mountain's height by `x`, it takes `workerTimes[i] + workerTimes[i] * 2 + ... + workerTimes[i] * x` seconds. For example:
//
// - To reduce the height of the mountain by 1, it takes `workerTimes[i]` seconds.
// - To reduce the height of the mountain by 2, it takes `workerTimes[i] + workerTimes[i] * 2` seconds, and so on.
//
// Return an integer representing the **minimum** number of seconds required for the workers to make the height of the mountain 0.
//
// **Example 1:**
//
// ```
// Input: mountainHeight = 4, workerTimes = [2,1,1]
// Output: 3
// Explanation:
// One way the height of the mountain can be reduced to 0 is:
// - Worker 0 reduces the height by 1, taking `workerTimes[0] = 2` seconds.
// - Worker 1 reduces the height by 2, taking `workerTimes[1] + workerTimes[1] * 2 = 3` seconds.
// - Worker 2 reduces the height by 1, taking `workerTimes[2] = 1` second.
// Since they work simultaneously, the minimum time needed is `max(2, 3, 1) = 3` seconds.
// ```
//
// **Example 2:**
//
// ```
// Input: mountainHeight = 10, workerTimes = [3,2,2,4]
// Output: 12
// Explanation:
// - Worker 0 reduces the height by 2, taking `workerTimes[0] + workerTimes[0] * 2 = 9` seconds.
// - Worker 1 reduces the height by 3, taking `workerTimes[1] + workerTimes[1] * 2 + workerTimes[1] * 3 = 12` seconds.
// - Worker 2 reduces the height by 3, taking `workerTimes[2] + workerTimes[2] * 2 + workerTimes[2] * 3 = 12` seconds.
// - Worker 3 reduces the height by 2, taking `workerTimes[3] + workerTimes[3] * 2 = 12` seconds.
// The number of seconds needed is `max(9, 12, 12, 12) = 12` seconds.
// ```
//
// **Example 3:**
//
// ```
// Input: mountainHeight = 5, workerTimes = [1]
// Output: 15
// Explanation:
// There is only one worker in this example, so the answer is `workerTimes[0] + workerTimes[0] * 2 + workerTimes[0] * 3 + workerTimes[0] * 4 + workerTimes[0] * 5 = 15`.
// ```
//
// **Constraints:**
//
// - `1 <= mountainHeight <= 10^5`
// - `1 <= workerTimes.length <= 10^4`
// - `1 <= workerTimes[i] <= 10^6`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <functional>
#include <queue>
#include <vector>

using namespace std;

// Heap
//
// Compute the marginal cost for each worker, and store it into a heap.
// For each step, pick the cheapest worker to work more.
//
// For each worker, say w = workerTimes[i] and it reduces h heights.
// The cumulative cost is f(h) = w * h(h+1)/2.
// The marginal cost is f(h) - f(h-1) = w * h.
class Solution {
  using Worker = tuple<int64_t, int64_t, int>;  // cumulative cost, marginal cost, worker time

  using Heap = priority_queue<Worker, vector<Worker>, greater<>>;  // min-heap

 public:
  int64_t minNumberOfSeconds(const int mountainHeight, const vector<int>& workerTimes) {
    const int n = workerTimes.size();

    // Init heap
    Heap heap;
    for (int i = 0; i < n; ++i) {
      heap.emplace(workerTimes[i], workerTimes[i], workerTimes[i]);
    }

    // Loop
    int totalHeight = 0;
    int64_t totalTime = 0;
    while (!heap.empty() && totalHeight < mountainHeight) {
      auto [cumulative, marginal, worker] = heap.top();
      heap.pop();

      ++totalHeight;
      totalTime = max(totalTime, cumulative);
      marginal += worker;
      cumulative += marginal;
      heap.emplace(cumulative, marginal, worker);
    }

    return totalTime;
  }
};

// Binary search
//
// Let w = worker[i], then it takes w * t(t+1)/2 seconds for each worker.
// Say the maximum time is T; that is,
// T >= w * t(t+1)/2
// 0 >= t^2 + t - 2T/w
// t <= [-1 + sqrt(1 + 8T/w)] / 2
// Sum all t the check if it is greater than mountainHeight.
class Solution2 {
  int64_t isqrt(int64_t x) {
    int64_t r = sqrt(double(x));
    while (r > 0 && r * r > x) --r;      // fix sqrt precision error
    while ((r + 1) * (r + 1) <= x) ++r;  // fix sqrt precision error
    return r;
  }

 public:
  int64_t minNumberOfSeconds(const int64_t mountainHeight, const vector<int>& workerTimes) {
    // Check if total is enough
    const auto check = [this, mountainHeight, &workerTimes](int64_t total) -> bool {
      int64_t sum = 0;
      for (const auto workerTime : workerTimes) {
        sum += (-1LL + isqrt(1 + 8 * total / workerTime)) / 2LL;
        if (sum >= mountainHeight) return true;
      }
      return false;
    };

    // Get upper bound
    int64_t maxTime = *max_element(workerTimes.cbegin(), workerTimes.cend());
    int64_t maxAns = maxTime * mountainHeight * (mountainHeight + 1) / 2;

    // Binary search
    // check(lo-1) = false, check(hi) = true
    int64_t lo = 0, hi = maxAns;
    while (lo < hi) {
      int64_t mid = lo + (hi - lo) / 2;
      if (check(mid)) {
        hi = mid;
      } else {
        lo = mid + 1;
      }
    }

    return hi;
  }
};
