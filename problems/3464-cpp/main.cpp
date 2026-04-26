// Source: https://leetcode.com/problems/maximize-the-distance-between-points-on-a-square
// Title: Maximize the Distance Between Points on a Square
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer `side`, representing the edge length of a square with corners at `(0, 0)`, `(0, side)`, `(side, 0)`, and `(side, side)` on a Cartesian plane.
//
// You are also given a **positive** integer `k` and a 2D integer array `points`, where `points[i] = [x_i, y_i]` represents the coordinate of a point lying on the **boundary** of the square.
//
// You need to select `k` elements among `points` such that the **minimum** Manhattan distance between any two points is **maximized**.
//
// Return the **maximum** possible **minimum** Manhattan distance between the selected `k` points.
//
// The Manhattan Distance between two cells `(x_i, y_i)` and `(x_j, y_j)` is `|x_i - x_j| + |y_i - y_j|`.
//
// **Example 1:**
//
// ```
// Input: side = 2, points = [[0,2],[2,0],[2,2],[0,0]], k = 4
// Output: 2
// Explanation:
// https://assets.leetcode.com/uploads/2025/01/28/4080_example0_revised.png
// Select all four points.
// ```
//
// **Example 2:**
//
// ```
// Input: side = 2, points = [[0,0],[1,2],[2,0],[2,2],[2,1]], k = 4
// Output: 1
// Explanation:
// https://assets.leetcode.com/uploads/2025/01/28/4080_example1_revised.png
// Select the points `(0, 0)`, `(2, 0)`, `(2, 2)`, and `(2, 1)`.
// ```
//
// **Example 3:**
//
// ```
// Input: side = 2, points = [[0,0],[0,1],[0,2],[1,2],[2,0],[2,2],[2,1]], k = 5
// Output: 1
// Explanation:
// https://assets.leetcode.com/uploads/2025/01/28/4080_example2_revised.png
// Select the points `(0, 0)`, `(0, 1)`, `(0, 2)`, `(1, 2)`, and `(2, 2)`.
// ```
//
// **Constraints:**
//
// - `1 <= side <= 10^9`
// - `4 <= points.length <= min(4 * side, 15 * 10^3)`
// - `points[i] == [xi, yi]`
// - The input is generated such that:
//   - `points[i]` lies on the boundary of the square.
//   - All `points[i]` are **unique**.
// - `4 <= k <= min(25, points.length)`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// Binary Search + Two Pointer + DFS
//
// Since we only care about the Manhattan distance,
// we can treat the square as a 1D cyclic line (counterclockwise).
//
// Next run binary search on the minimal distance.
// With the minimal distance fixed (say `d`), we can find the maximum `k` greedily.
// For each point `x`, we find the next `y` satisfies y >= x+d.
// Now the points forms a directed graph.
// The maximum k is equal to the size of the maximum cycle.
//
// To find these edges, we use two pointer approach.
// For the first point `x`, we find its `y` using linear scan.
// Next we shift `x` to the next one, and also shift `y` if needed.
//
// Since each node has only one out-edge, the graph is called functional graph.
// In a functional graph, each connected component is rho (greek letter) shape;
// that is, each connected component has only one cycle, with some tails connected to it.
//
// We can use a three-color DFS to find the cycles.
// WHITE are the unprocessed points.
// GRAY are the processing points (in the same connected component).
// BLACK are the processed points (in other same connected components).
//
// Initially, all points are WHITE.
// Pick a WHITE point, traverse along the path and mark every WHITE points to GRAY.
// If we run into a GRAY point, then we find the entry point of the cycle.
// Now we keep traverse and compute the cycle size until we loop back to this point.
// Next mark all gray points to BLACK (rerun the traverse)
//
// However, if we run into a BLACK point, then the path is a tail of a previous connected component.
// In this case, we just mark all points to BLACK.
//
// Note that, some of the cycles must loop the square more than one time.
// Therefore, we need to track the winding number while applying the DFS.
class Solution {
  enum class Color { WHITE, GRAY, BLACK };
  using enum Color;

 public:
  int maxDistance(const int side, const vector<vector<int>>& points, const int k) {
    const int n = points.size();
    const long long perimeter = side * 4LL;

    // Convert points to 1D coordinates
    auto coords = vector<long long>();
    coords.reserve(n);
    for (const auto& point : points) {
      const long long x = point[0], y = point[1];
      const long long coord = (x == 0 || y == side) ? x + y : perimeter - (x + y);
      coords.push_back(coord);
    }
    sort(coords.begin(), coords.end());

    // Helper, get coordinate for wraparound
    // 0 <= i < 2n
    const auto getCoord = [n, perimeter, &coords](int i) -> long long {  //
      return i < n ? coords[i] : coords[i - n] + perimeter;
    };

    // Helper, find k from minimal distance
    auto graph = vector<int>(n);     // reused
    auto colors = vector<Color>(n);  // reused
    const auto maxCycle = [n, &getCoord, &graph, &colors](int dist) -> int {
      // Build graph
      for (int i = 0, j = 0; i < n; ++i) {
        while (getCoord(j) - getCoord(i) < dist) ++j;
        graph[i] = j % n;
      }

      // Reset Color
      fill(colors.begin(), colors.end(), WHITE);

      // DFS
      int maxSize = 0;
      for (int i = 0; i < n; ++i) {
        if (colors[i] != WHITE) continue;

        // Loop
        int p = i;
        while (colors[p] == WHITE) {
          colors[p] = GRAY;
          p = graph[p];
        }

        // Find cycle size
        if (colors[p] == GRAY) {
          int size = 0, winding = 0;
          int q = p;
          do {
            ++size;
            winding += (graph[q] <= q);
            q = graph[q];
          } while (q != p);
          maxSize = max(maxSize, size / winding);
        }

        // Mark all black
        p = i;
        while (colors[p] == GRAY) {
          colors[p] = BLACK;
          p = graph[p];
        }
      }

      return maxSize;
    };

    // Binary search
    // check(lo-1) = true, check(hi) = false
    int lo = 2, hi = side + 1;
    while (lo < hi) {
      int mid = lo + (hi - lo) / 2;
      if (maxCycle(mid) >= k) {
        lo = mid + 1;
      } else {
        hi = mid;
      }
    }

    return lo - 1;
  }
};
