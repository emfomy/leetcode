// Source: https://leetcode.com/problems/maximize-the-minimum-powered-city
// Title: Maximize the Minimum Powered City
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a **0-indexed** integer array `stations` of length `n`, where `stations[i]` represents the number of power stations in the `i^th` city.
//
// Each power station can provide power to every city in a fixed **range**. In other words, if the range is denoted by `r`, then a power station at city `i` can provide power to all cities `j` such that `|i - j| <= r` and `0 <= i, j <= n - 1`.
//
// - Note that `|x|` denotes **absolute** value. For example, `|7 - 5| = 2` and `|3 - 10| = 7`.
//
// The **power** of a city is the total number of power stations it is being provided power from.
//
// The government has sanctioned building `k` more power stations, each of which can be built in any city, and have the same range as the pre-existing ones.
//
// Given the two integers `r` and `k`, return the **maximum possible minimum power** of a city, if the additional power stations are built optimally.
//
// **Note** that you can build the `k` power stations in multiple cities.
//
// **Example 1:**
//
// ```
// Input: stations = [1,2,4,5,0], r = 1, k = 2
// Output: 5
// Explanation:
// One of the optimal ways is to install both the power stations at city 1.
// So stations will become [1,4,4,5,0].
// - City 0 is provided by 1 + 4 = 5 power stations.
// - City 1 is provided by 1 + 4 + 4 = 9 power stations.
// - City 2 is provided by 4 + 4 + 5 = 13 power stations.
// - City 3 is provided by 5 + 4 = 9 power stations.
// - City 4 is provided by 5 + 0 = 5 power stations.
// So the minimum power of a city is 5.
// Since it is not possible to obtain a larger power, we return 5.
// ```
//
// **Example 2:**
//
// ```
// Input: stations = [4,4,4,4], r = 0, k = 3
// Output: 4
// Explanation:
// It can be proved that we cannot make the minimum power of a city greater than 4.
// ```
//
// **Constraints:**
//
// - `n == stations.length`
// - `1 <= n <= 10^5`
// - `0 <= stations[i] <= 10^5`
// - `0 <= r<= n - 1`
// - `0 <= k<= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

// Prefix Sum + Binary Search
class Solution {
  struct Queue {
    queue<int> data;
    long long sum;

    void push(int x) {
      data.push(x);
      sum += x;
    }

    void pop() {
      auto x = data.front();
      data.pop();
      sum -= x;
    }
  };

 public:
  long long maxPower(vector<int>& stations, int r, int k) {
    int n = stations.size();

    // Pre-compute powers
    auto powers = vector<long long>(n);
    auto que = Queue();
    for (auto i = 0; i < r; ++i) que.push(0);
    for (auto i = 0; i < r; ++i) que.push(stations[i]);
    for (auto i = 0; i < n; ++i) {
      if (i + r < n) que.push(stations[i + r]);
      powers[i] = que.sum;
      que.pop();
    }

    // Helper
    auto check = [&](long long threshold) -> bool {
      auto que = Queue();
      auto kk = 0;
      for (auto i = 0; i < 2 * r; ++i) que.push(0);
      for (auto power : powers) {
        auto x = max(threshold - power - que.sum, 0LL);
        kk += x;
        que.push(x);
        que.pop();
      }
      return kk <= k;
    };

    // Binary search
    // check(lo-1) = true, check(lo=hi) = false
    auto minIt = min_element(powers.begin(), powers.end());
    auto lo = *minIt, hi = (*minIt) + k + 1;
    while (lo < hi) {
      auto mid = lo + (hi - lo) / 2;
      if (check(mid)) {
        lo = mid + 1;
      } else {
        hi = mid;
      }
    }

    return lo - 1;
  }
};
