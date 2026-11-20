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

#include <algorithm>
#include <climits>
#include <numeric>
#include <vector>

using namespace std;

// Brute-Force + Permutation
//
// Try all matching.
class Solution {
  int getDist(const vector<int>& p1, const vector<int>& p2) {  //
    return abs(p1[0] - p2[0]) + abs(p1[1] - p2[1]);
  }

 public:
  int assignBikes(const vector<vector<int>>& workers, const vector<vector<int>>& bikes) {
    int n = workers.size(), m = bikes.size();

    // Guard
    if (n > m) return -1;

    // Init index
    auto idxs = vector<int>(m);  // assign worker i to bike idxs[i]
    iota(idxs.begin(), idxs.end(), 0);

    // All permutation
    int minDist = INT_MAX;
    do {
      int dist = 0;
      for (int i = 0; i < n; ++i) {
        dist += getDist(workers[i], bikes[idxs[i]]);
      }
      minDist = min(minDist, dist);
    } while (next_permutation(idxs.begin(), idxs.end()));

    return minDist;
  }
};

// Brute-Force + Permutation
//
// Try all matching.
//
// Note that we don't need all permutation of size-m.
// We only need the size-n subset.
//
// We can reverse all result in [n, m) after calling next_permutation.
// This operation will skip all permutations for the last (m-n) elements.
class Solution2 {
  int getDist(const vector<int>& p1, const vector<int>& p2) {  //
    return abs(p1[0] - p2[0]) + abs(p1[1] - p2[1]);
  }

 public:
  int assignBikes(const vector<vector<int>>& workers, const vector<vector<int>>& bikes) {
    int n = workers.size(), m = bikes.size();

    // Guard
    if (n > m) return -1;

    // Init index
    auto idxs = vector<int>(m);  // assign worker i to bike idxs[i]
    iota(idxs.begin(), idxs.end(), 0);

    // All permutation
    int minDist = INT_MAX;
    do {
      int dist = 0;
      for (int i = 0; i < n; ++i) {
        dist += getDist(workers[i], bikes[idxs[i]]);
      }
      minDist = min(minDist, dist);

      // Skip permutations for unused part
      reverse(idxs.begin() + n, idxs.end());
    } while (next_permutation(idxs.begin(), idxs.end()));

    return minDist;
  }
};

// Use DFS + DP
//
// Loop for each worker, choose any available bike.
// We cache the state (worker ID, used bikes)
// Note that we use bit mask to store bikes.
class Solution3 {
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
      int dist = INT_MAX;
      for (auto j = 0; j < m; j++) {
        auto xj = bikes[j][0], yj = bikes[j][1];
        if ((mask & (1 << j)) == 0) {
          auto dist2 = dfs(i + 1, mask | (1 << j));
          dist = min(dist, abs(xi - xj) + abs(yi - yj) + dist2);
        }
      }

      cache[i][mask] = dist;
      return dist;
    };

    return dfs(0, 0);
  }
};

// DP + Backtracking
//
// We fisrt consider a simple case: N = 1.
// In this case, just pick the nearest bike.
//
// Now assume we want to find the bast solution of a K-size subset.
// Say we know the solution of all (K-1)-size sub-subsets,
// we can make the new worker pick the nearest non-pick bike.
// Among all above cases, we pick the best distance for this K-size subset.
//
// Use bit mask to represent the subsets.
class Solution4 {
  int getDist(const vector<int>& p1, const vector<int>& p2) { return abs(p1[0] - p2[0]) + abs(p1[1] - p2[1]); }

  using Mask = unsigned int;

 public:
  int assignBikes(const vector<vector<int>>& workers, const vector<vector<int>>& bikes) {
    const int n = workers.size(), m = bikes.size();
    const unsigned int N = 1u << n;  // 2^n;

    // Init DP array
    auto minDists = vector<int>(N, INT_MAX);
    auto usedBikes = vector<Mask>(N);
    minDists[0] = 0;

    // Group subset by size
    auto maskGroups = vector<vector<Mask>>(n + 1);
    for (unsigned int mask = 1; mask < N; ++mask) {
      maskGroups[popcount(mask)].push_back(mask);
    }

    // loop through all mask with different size
    for (int k = 1; k <= n; ++k) {
      for (Mask mask : maskGroups[k]) {
        for (int worker = 0; worker < n; ++worker) {
          Mask workerBit = 1u << worker;

          // Guard, check worker in subset
          if ((mask & workerBit) == 0) continue;

          Mask subset = mask - workerBit;
          int subsetDist = minDists[subset];
          Mask subsetUsedBikes = usedBikes[subset];

          // Find nearest bike
          int bestBike = -1;
          int bestBikeDist = INT_MAX;
          for (int bike = 0; bike < m; ++bike) {
            Mask bikeBit = 1u << bike;

            // Guard, bike used
            if (usedBikes[subset] & bikeBit) continue;

            int dist = getDist(workers[worker], bikes[bike]);
            if (bestBikeDist > dist) {
              bestBikeDist = dist;
              bestBike = bike;
            }
          }

          // Update DP
          int newDist = subsetDist + bestBikeDist;
          if (minDists[mask] > newDist) {
            minDists[mask] = newDist;
            usedBikes[mask] = subsetUsedBikes | (1u << bestBike);
          }
        }
      }
    }

    return minDists[N - 1];
  }
};
