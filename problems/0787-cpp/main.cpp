// Source: https://leetcode.com/problems/cheapest-flights-within-k-stops
// Title: Cheapest Flights Within K Stops
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There are `n` cities connected by some number of flights. You are given an array `flights` where `flights[i] = [from_i, to_i, price_i]` indicates that there is a flight from city `from_i` to city `to_i` with cost `price_i`.
//
// You are also given three integers `src`, `dst`, and `k`, return **the cheapest price** from `src` to `dst` with at most `k` stops. If there is no such route, return `-1`.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2022/03/18/cheapest-flights-within-k-stops-3drawio.png
//
// ```
// **Input:** n = 4, flights = [[0,1,100],[1,2,100],[2,0,100],[1,3,600],[2,3,200]], src = 0, dst = 3, k = 1
// **Output:** 700
// **Explanation:**
// The graph is shown above.
// The optimal path with at most 1 stop from city 0 to 3 is marked in red and has cost 100 + 600 = 700.
// Note that the path through cities [0,1,2,3] is cheaper but is invalid because it uses 2 stops.
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2022/03/18/cheapest-flights-within-k-stops-1drawio.png
//
// ```
// **Input:** n = 3, flights = [[0,1,100],[1,2,100],[0,2,500]], src = 0, dst = 2, k = 1
// **Output:** 200
// **Explanation:**
// The graph is shown above.
// The optimal path with at most 1 stop from city 0 to 2 is marked in red and has cost 100 + 100 = 200.
// ```
//
// **Example 3:**
// https://assets.leetcode.com/uploads/2022/03/18/cheapest-flights-within-k-stops-2drawio.png
//
// ```
// **Input:** n = 3, flights = [[0,1,100],[1,2,100],[0,2,500]], src = 0, dst = 2, k = 0
// **Output:** 500
// **Explanation:**
// The graph is shown above.
// The optimal path with no stops from city 0 to 2 is marked in red and has cost 500.
// ```
//
// **Constraints:**
//
// - `2 <= n <= 100`
// - `0 <= flights.length <= (n * (n - 1) / 2)`
// - `flights[i].length == 3`
// - `0 <= from_i, to_i < n`
// - `from_i != to_i`
// - `1 <= price_i <= 10^4`
// - There will not be any multiple flights between two cities.
// - `0 <= src, dst, k < n`
// - `src != dst`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <climits>
#include <functional>
#include <queue>
#include <vector>

using namespace std;

// BFS + Heap (Dijkstra)
class Solution {
  using Item = tuple<int, int, int>;  // cost, city, step
  using Edge = pair<int, int>;        // to, price

 public:
  int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
    // Init graph
    auto graph = vector(n, vector<Edge>());
    for (auto& flight : flights) {
      int from = flight[0], to = flight[1], price = flight[2];
      graph[from].push_back({to, price});
    }

    // BFS
    auto costs = vector(n, vector(k + 2, INT_MAX));  // (city, step) -> cost

    auto queue = priority_queue(greater(), std::move(vector<Item>()));  // min-heap
    queue.push({0, src, 0});

    while (!queue.empty()) {
      auto [cost, city, step] = queue.top();
      queue.pop();

      // Found
      if (city == dst) return cost;

      // Visited
      if (cost >= costs[city][step]) continue;
      costs[city][step] = cost;

      // No more step
      if (step == k + 1) continue;

      // Next step
      auto nextStep = step + 1;
      for (auto [next, price] : graph[city]) {
        auto nextCost = cost + price;
        if (nextCost >= costs[next][nextStep]) continue;
        queue.push({nextCost, next, nextStep});
      }
    }

    return -1;
  }
};

// BFS + Queue
class Solution2 {
  using Edge = pair<int, int>;   // to, price
  using Item = tuple<int, int>;  // cost, city

 public:
  int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
    // Init graph
    auto graph = vector(n, vector<Edge>());
    for (auto& flight : flights) {
      int from = flight[0], to = flight[1], price = flight[2];
      graph[from].push_back({to, price});
    }

    // BFS
    auto costs = vector(n, INT_MAX);  // city -> cost

    auto currQueue = queue<Item>();
    auto nextQueue = queue<Item>();
    currQueue.push({0, src});

    for (int step = 0; step <= k + 1; ++step) {
      while (!currQueue.empty()) {
        auto [cost, city] = currQueue.front();
        currQueue.pop();

        // Visited
        if (cost >= costs[city]) continue;
        costs[city] = cost;

        // No more steps
        if (step == k + 1) continue;

        // Next step
        for (auto [next, price] : graph[city]) {
          auto nextCost = cost + price;
          if (nextCost >= costs[next]) continue;
          nextQueue.push({nextCost, next});
        }
      }

      swap(currQueue, nextQueue);
    }

    return costs[dst] != INT_MAX ? costs[dst] : -1;
  }
};

// Bellman Ford
class Solution3 {
 public:
  int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
    auto currCosts = vector(n, INT_MAX);
    currCosts[src] = 0;

    for (int step = 0; step <= k; ++step) {
      auto nextCosts = currCosts;  // copy, avoid racing
      for (auto& flight : flights) {
        int from = flight[0], to = flight[1], price = flight[2];
        if (currCosts[from] == INT_MAX) continue;  // skip unreachable, avoid overflow
        nextCosts[to] = min(nextCosts[to], currCosts[from] + price);
      }
      swap(currCosts, nextCosts);
    }

    return currCosts[dst] != INT_MAX ? currCosts[dst] : -1;
  }
};
