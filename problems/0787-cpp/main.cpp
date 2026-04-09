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
// Input: n = 4, flights = [[0,1,100],[1,2,100],[2,0,100],[1,3,600],[2,3,200]], src = 0, dst = 3, k = 1
// Output: 700
// Explanation:
// The graph is shown above.
// The optimal path with at most 1 stop from city 0 to 3 is marked in red and has cost 100 + 600 = 700.
// Note that the path through cities [0,1,2,3] is cheaper but is invalid because it uses 2 stops.
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2022/03/18/cheapest-flights-within-k-stops-1drawio.png
//
// ```
// Input: n = 3, flights = [[0,1,100],[1,2,100],[0,2,500]], src = 0, dst = 2, k = 1
// Output: 200
// Explanation:
// The graph is shown above.
// The optimal path with at most 1 stop from city 0 to 2 is marked in red and has cost 100 + 100 = 200.
// ```
//
// **Example 3:**
// https://assets.leetcode.com/uploads/2022/03/18/cheapest-flights-within-k-stops-2drawio.png
//
// ```
// Input: n = 3, flights = [[0,1,100],[1,2,100],[0,2,500]], src = 0, dst = 2, k = 0
// Output: 500
// Explanation:
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

#include <algorithm>
#include <climits>
#include <queue>
#include <vector>

using namespace std;

// Dijkstra
//
// Duplicate and stack the graph into k+2 layers.
// Redirect the edge to the next layer.
class Solution {
  using Edge = pair<int, int>;            // price, to
  using DFSState = tuple<int, int, int>;  // cost, node, step

  using Heap = priority_queue<DFSState, vector<DFSState>, greater<>>;  // min-heap

 public:
  int findCheapestPrice(                   //
      const int n,                         //
      const vector<vector<int>>& flights,  //
      const int src,                       //
      const int dst,                       //
      int k                                //
  ) {
    // Build graph
    auto graph = vector<vector<Edge>>(n);
    for (const auto& flight : flights) {
      int from = flight[0], to = flight[1], price = flight[2];
      graph[from].push_back(Edge{price, to});
    }

    // Prepare
    auto costs = vector<vector<int>>(n, vector<int>(k + 2, INT_MAX));
    Heap heap;
    costs[src][0] = 0;
    heap.push(DFSState{0, src, 0});

    // Loop
    while (!heap.empty()) {
      const auto [cost, from, step] = heap.top();
      heap.pop();

      // Early Stop
      if (from == dst) return cost;

      // Relax
      if (costs[from][step] < cost || step == k + 1) continue;

      // Traversal
      for (const auto [price, to] : graph[from]) {
        int nextCost = cost + price;
        if (costs[to][step + 1] <= nextCost) continue;
        costs[to][step + 1] = nextCost;
        heap.push(DFSState{nextCost, to, step + 1});
      }
    }

    return -1;  // unreachable
  }
};

// Bellman-Ford
//
// Loop for at most k+1 steps.
class Solution2 {
 public:
  int findCheapestPrice(                   //
      const int n,                         //
      const vector<vector<int>>& flights,  //
      const int src,                       //
      const int dst,                       //
      const int k                          //
  ) {
    // Prepare
    auto prevCosts = vector<int>(n);
    auto currCosts = vector<int>(n, INT_MAX);
    currCosts[src] = 0;

    // Loop
    for (int stop = 0; stop <= k; ++stop) {
      bool updated = false;

      // Copy, avoid racing
      copy(currCosts.begin(), currCosts.end(), prevCosts.begin());

      // Loop
      for (const auto& flight : flights) {
        int from = flight[0], to = flight[1], price = flight[2];
        if (prevCosts[from] == INT_MAX) continue;

        int nextCost = prevCosts[from] + price;
        if (currCosts[to] > nextCost) {
          currCosts[to] = nextCost;
          updated = true;
        }
      }

      // Early Stop
      if (!updated) break;
    }

    return currCosts[dst] == INT_MAX ? -1 : currCosts[dst];
  }
};
