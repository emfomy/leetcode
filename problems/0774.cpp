// Source: https://leetcode.com/problems/minimize-max-distance-to-gas-station
// Title: Minimize Max Distance to Gas Station
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `stations` that represents the positions of the gas stations on the **x-axis**. You are also given an integer `k`.
//
// You should add `k` new gas stations. You can add the stations anywhere on the **x-axis**, and not necessarily on an integer position.
//
// Let `penalty()` be the maximum distance between **adjacent** gas stations after adding the `k` new stations.
//
// Return the smallest possible value of `penalty()`. Answers within `10^-6` of the actual answer will be accepted.
//
// **Example 1:**
//
// ```
// Input: stations = [1,2,3,4,5,6,7,8,9,10], k = 9
// Output: 0.50000
// ```
//
// **Example 2:**
//
// ```
// Input: stations = [23,24,36,39,46,56,57,65,84,98], k = 1
// Output: 14.00000
// ```
//
// **Constraints:**
//
// - `10 <= stations.length <= 2000`
// - `0 <= stations[i] <= 10^8`
// - `stations` is sorted in a **strictly increasing** order.
// - `1 <= k <= 10^6`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <queue>
#include <vector>

using namespace std;

// Use Heap (TLE)
class Solution {
  using Space = tuple<double, double, int>;  // new dist, orig dist, new station count

 public:
  double minmaxGasDist(vector<int>& stations, int k) {
    int n = stations.size();

    // Prepare
    auto spaces = vector<Space>();
    for (auto i = 0; i < n - 1; ++i) {
      auto dist = stations[i + 1] - stations[i];
      spaces.push_back({dist, dist, 1});
    }
    auto heap = priority_queue(less(), std::move(spaces));  // max-heap

    for (auto i = 0; i < k; ++i) {
      auto [_, dist, cnt] = heap.top();
      heap.pop();
      ++cnt;
      heap.push({dist / cnt, dist, cnt});
    }

    return get<0>(heap.top());
  }
};

// Use Binary Search
class Solution2 {
 public:
  double minmaxGasDist(vector<int>& stations, int k) {
    int n = stations.size();

    // Prepare
    auto dists = vector<double>();
    auto maxDist = 0.0;
    for (auto i = 0; i < n - 1; ++i) {
      double dist = stations[i + 1] - stations[i];
      dists.push_back(dist);
      maxDist = max(maxDist, dist);
    }

    // Helper
    auto check = [&](double dist) -> bool {
      auto count = 0;
      for (auto space : dists) count += ceil(space / dist) - 1;
      return count <= k;  // smaller gap need more new stations
    };

    // Binary Search
    // Greater gap need more new stations
    // check(lo) = false, check(hi) = true
    auto lo = 0.0, hi = maxDist;  // unknown (lo, hi)
    while (hi - lo > 1e-6) {
      auto mid = (lo + hi) / 2;
      if (check(mid)) {
        hi = mid;  // [lo, mid)
      } else {
        lo = mid;  // [mid, hi)
      }
    }

    return hi;
  }
};
