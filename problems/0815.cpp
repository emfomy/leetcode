// Source: https://leetcode.com/problems/bus-routes
// Title: Bus Routes
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an array `routes` representing bus routes where `routes[i]` is a bus route that the `i^th` bus repeats forever.
//
// - For example, if `routes[0] = [1, 5, 7]`, this means that the `0^th` bus travels in the sequence `1 -> 5 -> 7 -> 1 -> 5 -> 7 -> 1 -> ...` forever.
//
// You will start at the bus stop `source` (You are not on any bus initially), and you want to go to the bus stop `target`. You can travel between bus stops by buses only.
//
// Return the least number of buses you must take to travel from `source` to `target`. Return `-1` if it is not possible.
//
// **Example 1:**
//
// ```
// Input: routes = [[1,2,7],[3,6,7]], source = 1, target = 6
// Output: 2
// Explanation: The best strategy is take the first bus to the bus stop 7, then take the second bus to the bus stop 6.
// ```
//
// **Example 2:**
//
// ```
// Input: routes = [[7,12],[4,5,15],[6],[15,19],[9,12,13]], source = 15, target = 12
// Output: -1
// ```
//
// **Constraints:**
//
// - `1 <= routes.length <= 500`.
// - `1 <= routes[i].length <= 10^5`
// - All the values of `routes[i]` are **unique**.
// - `sum(routes[i].length) <= 10^5`
// - `0 <= routes[i][j] < 10^6`
// - `0 <= source, target < 10^6`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

// BFS
//
// Since each bus travels its route forever, we can add an edge for all stop pairs.
// Next apply BFS to find the shortest path.
//
// However, since the size of bus route is larger than the number of buses,
// instead connect all stop pairs, we create a mapping from stop to buses.
// In BFS, at each stop, we loop all buses and travels to all the stops.
class Solution {
 public:
  int numBusesToDestination(              //
      const vector<vector<int>>& routes,  //
      const int source,                   //
      const int target                    //
  ) {
    const int nBus = routes.size();

    // Edge case
    if (source == target) return 0;

    // Create stop to bus mapping
    auto stop2bus = unordered_map<int, vector<int>>();  // stop -> buses
    for (int bus = 0; bus < nBus; ++bus) {
      for (int stop : routes[bus]) {
        stop2bus[stop].push_back(bus);
      }
    }

    // Check if source & target has bus stop
    if (!stop2bus.contains(source) || !stop2bus.contains(target)) return -1;

    // BFS
    auto dists = unordered_map<int, int>();  // distance of each stop
    auto que = queue<int>();
    dists[source] = 0;
    que.push(source);

    while (!que.empty()) {
      const int stop = que.front();
      que.pop();

      const int nextDist = dists[stop] + 1;
      for (int bus : stop2bus[stop]) {
        for (int nextStop : routes[bus]) {
          if (dists.contains(nextStop)) continue;  // visited
          if (nextStop == target) return nextDist;
          dists[nextStop] = nextDist;
          que.push(nextStop);
        }
      }
    }

    return -1;
  }
};

// BFS
//
// Since its bad to retake a bus, we also track the visited bus in BFS.
class Solution2 {
 public:
  int numBusesToDestination(              //
      const vector<vector<int>>& routes,  //
      const int source,                   //
      const int target                    //
  ) {
    const int nBus = routes.size();

    // Edge case
    if (source == target) return 0;

    // Create stop to bus mapping
    auto stop2bus = unordered_map<int, vector<int>>();  // stop -> buses
    for (int bus = 0; bus < nBus; ++bus) {
      for (int stop : routes[bus]) {
        stop2bus[stop].push_back(bus);
      }
    }

    // Check if source & target has bus stop
    if (!stop2bus.contains(source) || !stop2bus.contains(target)) return -1;

    // BFS
    auto visitedBus = vector<bool>(nBus);    // visited bus
    auto dists = unordered_map<int, int>();  // distance of each stop
    auto que = queue<int>();
    dists[source] = 0;
    que.push(source);

    while (!que.empty()) {
      const int stop = que.front();
      que.pop();

      const int nextDist = dists[stop] + 1;
      for (int bus : stop2bus[stop]) {
        if (visitedBus[bus]) continue;
        visitedBus[bus] = true;
        for (int nextStop : routes[bus]) {
          if (dists.contains(nextStop)) continue;  // visited
          if (nextStop == target) return nextDist;
          dists[nextStop] = nextDist;
          que.push(nextStop);
        }
      }
    }

    return -1;
  }
};

// BFS
//
// We treat both stop and bus as node.
// The final answer is the half of the shortest path.
//
// We use negative values to represent buses.
class Solution3 {
 public:
  int numBusesToDestination(        //
      vector<vector<int>>& routes,  // intentionally remove const
      const int source,             //
      const int target              //
  ) {
    const int nBus = routes.size();

    // Edge case
    if (source == target) return 0;

    // Create graph
    auto graph = unordered_map<int, vector<int>>();
    for (int bus = 0; bus < nBus; ++bus) {
      int busId = -(bus + 1);
      for (int stop : routes[bus]) {
        graph[stop].push_back(busId);
      }
      graph[busId] = std::move(routes[bus]);
    }

    // Check if source & target are in the graph
    if (!graph.contains(source) || !graph.contains(target)) return -1;

    // BFS
    auto dists = unordered_map<int, int>();  // distance of each node
    auto que = queue<int>();
    dists[source] = 0;
    que.push(source);

    while (!que.empty()) {
      const int node = que.front();
      que.pop();

      const int nextDist = dists[node] + 1;
      for (int nextNode : graph[node]) {
        if (dists.contains(nextNode)) continue;  // visited
        if (nextNode == target) return nextDist / 2;
        dists[nextNode] = nextDist;
        que.push(nextNode);
      }
    }

    return -1;
  }
};
