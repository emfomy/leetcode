// Source: https://leetcode.com/problems/campus-bikes-ii
// Title: Campus Bikes II
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// On a campus represented as a 2D grid, there are `n` workers and `m` bikes, with `n <= m`. Each worker and bike is a 2D coordinate on this grid.
//
// We assign one unique bike to each worker so that the sum of the **Manhattan distances** between each worker and their assigned bike is minimized.
//
// Return `the minimum possible sum of Manhattan distances between each worker and their assigned bike`.
//
// The **Manhattan distance** between two points `p1` and `p2` is `Manhattan(p1, p2) = |p1.x - p2.x| + |p1.y - p2.y|`.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2019/03/06/1261_example_1_v2.png
//
// ```
// Input: workers = [[0,0],[2,1]], bikes = [[1,2],[3,3]]
// Output: 6
// Explanation:
// We assign bike 0 to worker 0, bike 1 to worker 1. The Manhattan distance of both assignments is 3, so the output is 6.
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2019/03/06/1261_example_2_v2.png
//
// ```
// Input: workers = [[0,0],[1,1],[2,0]], bikes = [[1,0],[2,2],[2,1]]
// Output: 4
// Explanation:
// We first assign bike 0 to worker 0, then assign bike 1 to worker 1 or worker 2, bike 2 to worker 2 or worker 1. Both assignments lead to sum of the Manhattan distances as 4.
// ```
//
// **Example 3:**
//
// ```
// Input: workers = [[0,0],[1,0],[2,0],[3,0],[4,0]], bikes = [[0,999],[1,999],[2,999],[3,999],[4,999]]
// Output: 4995
// ```
//
// **Constraints:**
//
// - `n == workers.length`
// - `m == bikes.length`
// - `1 <= n <= m <= 10`
// - `workers[i].length == 2`
// - `bikes[i].length == 2`
// - `0 <= workers[i][0], workers[i][1], bikes[i][0], bikes[i][1] < 1000`
// - All the workers and the bikes locations are **unique**.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <functional>
#include <vector>

using namespace std;

// Use DFS + DP
//
// Loop for each worker, choose any available bike.
// We cache the state (worker ID, used bikes)
// Note that we use bit mask to store bikes.
class Solution {
 public:
  int assignBikes(vector<vector<int>>& workers, vector<vector<int>>& bikes) {
    int n = workers.size(), m = bikes.size();
    auto cache = vector(n, vector<int>(1 << m));  // worker id, bike mask -> distance

    function<int(int, int)> dfs = [&](int i, int mask) -> int {
      if (i == n) return 0;

      if (cache[i][mask]) {
        return cache[i][mask];
      }

      auto xi = workers[i][0], yi = workers[i][1];
      int dist = 1e5;  // (1000 + 1000) * 10
      for (auto j = 0; j < m; j++) {
        auto jBit = 1 << j;
        auto xj = bikes[j][0], yj = bikes[j][1];
        if (!(mask & jBit)) {
          auto dist2 = dfs(i + 1, mask | jBit);
          dist = min(dist, abs(xi - xj) + abs(yi - yj) + dist2);
        }
      }

      cache[i][mask] = dist;
      return dist;
    };

    return dfs(0, {});
  }
};
