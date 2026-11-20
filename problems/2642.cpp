// Source: https://leetcode.com/problems/design-graph-with-shortest-path-calculator
// Title: Design Graph With Shortest Path Calculator
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There is a **directed weighted** graph that consists of `n` nodes numbered from `0` to `n - 1`. The edges of the graph are initially represented by the given array `edges` where `edges[i] = [from_i, to_i, edgeCost_i]` meaning that there is an edge from `from_i` to `to_i` with the cost `edgeCost_i`.
//
// Implement the `Graph` class:
//
// - `Graph(int n, int[][] edges)` initializes the object with `n` nodes and the given edges.
// - `addEdge(int[] edge)` adds an edge to the list of edges where `edge = [from, to, edgeCost]`. It is guaranteed that there is no edge between the two nodes before adding this one.
// - `int shortestPath(int node1, int node2)` returns the **minimum** cost of a path from `node1` to `node2`. If no path exists, return `-1`. The cost of a path is the sum of the costs of the edges in the path.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2023/01/11/graph3drawio-2.png
//
// ```
// Input
//
// ["Graph", "shortestPath", "shortestPath", "addEdge", "shortestPath"]
// [[4, [[0, 2, 5], [0, 1, 2], [1, 2, 1], [3, 0, 3]]], [3, 2], [0, 3], [[1, 3, 4]], [0, 3]]
// Output
//
// [null, 6, -1, null, 6]
//
// Explanation
//
// Graph g = new Graph(4, [[0, 2, 5], [0, 1, 2], [1, 2, 1], [3, 0, 3]]);
// g.shortestPath(3, 2); // return 6. The shortest path from 3 to 2 in the first diagram above is 3 -> 0 -> 1 -> 2 with a total cost of 3 + 2 + 1 = 6.
// g.shortestPath(0, 3); // return -1. There is no path from 0 to 3.
// g.addEdge([1, 3, 4]); // We add an edge from node 1 to node 3, and we get the second diagram above.
// g.shortestPath(0, 3); // return 6. The shortest path from 0 to 3 now is 0 -> 1 -> 3 with a total cost of 2 + 4 = 6.
// ```
//
// **Constraints:**
//
// - `1 <= n <= 100`
// - `0 <= edges.length <= n * (n - 1)`
// - `edges[i].length == edge.length == 3`
// - `0 <= from_i, to_i, from, to, node1, node2 <= n - 1`
// - `1 <= edgeCost_i, edgeCost <= 10^6`
// - There are no repeated edges and no self-loops in the graph at any point.
// - At most `100` calls will be made for `addEdge`.
// - At most `100` calls will be made for `shortestPath`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <functional>
#include <queue>
#include <vector>

using namespace std;

// Floyd–Warshall
//
// When adding a new edge (u, v), for each pair (x, y),
// We can update d[x, y] to d[x, u] + d[u, v] + d[v, y] if new path is shorter.
class Graph {
  constexpr static int kInf = 2e8;  // max path is 10^6 * 100 = 10^8, 3*kInf < 2^31

  vector<vector<int>> dist;

 public:
  // O(N^3)
  Graph(int n, const vector<vector<int>>& edges) : dist(n, vector<int>(n, kInf)) {
    // Init graph
    for (int x = 0; x < n; ++x) {
      dist[x][x] = 0;
    }
    for (auto const& edge : edges) {
      int u = edge[0], v = edge[1], w = edge[2];
      dist[u][v] = min(dist[u][v], w);
    }

    // Floyd–Warshall
    for (int z = 0; z < n; ++z) {
      for (int x = 0; x < n; ++x) {
        for (int y = 0; y < n; ++y) {
          dist[x][y] = min(dist[x][y], dist[x][z] + dist[z][y]);
        }
      }
    }
  }

  // O(N^2)
  void addEdge(const vector<int>& edge) {
    const int n = dist.size();
    int u = edge[0], v = edge[1], w = edge[2];

    // Guard
    if (w > dist[u][v]) return;  // no need to update

    // Update
    dist[u][v] = w;
    for (int x = 0; x < n; ++x) {
      for (int y = 0; y < n; ++y) {
        dist[x][y] = min(dist[x][y], dist[x][u] + w + dist[v][y]);
      }
    }
  }

  // O(1)
  int shortestPath(int u, int v) {  //
    return dist[u][v] >= kInf ? -1 : dist[u][v];
  }
};

// Dijkstra
//
// We can cache previous result to speed up Dijkstra.
class Graph2 {
  constexpr static int kInf = 2e8;  // max path is 10^6 * 100 = 10^8, 3*kInf < 2^31

  struct Edge {
    int dest;  // dest node
    int weight;
  };

  vector<vector<Edge>> graph;
  vector<vector<int>> dist;

  using HeapItem = pair<int, int>;                                     // cost, node
  using Heap = priority_queue<HeapItem, vector<HeapItem>, greater<>>;  // min-heap

 public:
  // O(E)
  Graph2(int n, const vector<vector<int>>& edges) : graph(n), dist(n, vector<int>(n, kInf)) {
    // Init graph
    for (auto const& edge : edges) {
      int u = edge[0], v = edge[1], w = edge[2];
      graph[u].push_back({v, w});
    }
  }

  // O(1), should not input duplicated edge
  void addEdge(const vector<int>& edge) {
    const int n = dist.size();
    int u = edge[0], v = edge[1], w = edge[2];
    graph[u].push_back({v, w});
  }

  // O(E logN)
  int shortestPath(int source, int target) {  //
    const int n = dist.size();
    auto heap = Heap();
    auto& costs = dist[source];
    auto visited = vector<bool>(n);
    heap.emplace(0, source);

    while (!heap.empty()) {
      auto [uCost, u] = heap.top();
      heap.pop();

      // Early stop
      if (u == target) return uCost;

      // Relax
      if (costs[u] < uCost || visited[u]) continue;
      costs[u] = uCost;
      visited[u] = true;

      // Traversal
      for (auto [v, weight] : graph[u]) {
        int vCost = uCost + weight;
        if (costs[v] < vCost || costs[v] == vCost && visited[v]) continue;
        costs[v] = vCost;
        heap.emplace(vCost, v);
      }
    }

    return costs[target] >= kInf ? -1 : costs[target];
  }
};
