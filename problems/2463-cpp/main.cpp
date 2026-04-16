// Source: https://leetcode.com/problems/minimum-total-distance-traveled
// Title: Minimum Total Distance Traveled
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There are some robots and factories on the X-axis. You are given an integer array `robot` where `robot[i]` is the position of the `i^th` robot. You are also given a 2D integer array `factory` where `factory[j] = [position_j, limit_j]` indicates that `position_j` is the position of the `j^th` factory and that the `j^th` factory can repair at most `limit_j` robots.
//
// The positions of each robot are **unique**. The positions of each factory are also **unique**. Note that a robot can be **in the same position** as a factory initially.
//
// All the robots are initially broken; they keep moving in one direction. The direction could be the negative or the positive direction of the X-axis. When a robot reaches a factory that did not reach its limit, the factory repairs the robot, and it stops moving.
//
// **At any moment**, you can set the initial direction of moving for **some** robot. Your target is to minimize the total distance traveled by all the robots.
//
// Return the minimum total distance traveled by all the robots. The test cases are generated such that all the robots can be repaired.
//
// **Note that**
//
// - All robots move at the same speed.
// - If two robots move in the same direction, they will never collide.
// - If two robots move in opposite directions and they meet at some point, they do not collide. They cross each other.
// - If a robot passes by a factory that reached its limits, it crosses it as if it does not exist.
// - If the robot moved from a position `x` to a position `y`, the distance it moved is `|y - x|`.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2022/09/15/example1.jpg
//
// ```
// Input: robot = [0,4,6], factory = [[2,2],[6,2]]
// Output: 4
// Explanation: As shown in the figure:
// - The first robot at position 0 moves in the positive direction. It will be repaired at the first factory.
// - The second robot at position 4 moves in the negative direction. It will be repaired at the first factory.
// - The third robot at position 6 will be repaired at the second factory. It does not need to move.
// The limit of the first factory is 2, and it fixed 2 robots.
// The limit of the second factory is 2, and it fixed 1 robot.
// The total distance is |2 - 0| + |2 - 4| + |6 - 6| = 4. It can be shown that we cannot achieve a better total distance than 4.
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2022/09/15/example-2.jpg
//
// ```
// Input: robot = [1,-1], factory = [[-2,1],[2,1]]
// Output: 2
// Explanation: As shown in the figure:
// - The first robot at position 1 moves in the positive direction. It will be repaired at the second factory.
// - The second robot at position -1 moves in the negative direction. It will be repaired at the first factory.
// The limit of the first factory is 1, and it fixed 1 robot.
// The limit of the second factory is 1, and it fixed 1 robot.
// The total distance is |2 - 1| + |(-2) - (-1)| = 2. It can be shown that we cannot achieve a better total distance than 2.
// ```
//
// **Constraints:**
//
// - `1 <= robot.length, factory.length <= 100`
// - `factory[j].length == 2`
// - `-10^9 <= robot[i], position_j <= 10^9`
// - `0 <= limit_j <= robot.length`
// - The input will be generated such that it is always possible to repair every robot.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <vector>

using namespace std;

// 2D-DP
//
// The problem is equal to find the minimal match of robot and factory (respect to its limit).
//
// Say robot A wants to go to factory C, and robot B wants to go to factory D.
// We claim that B will not reach C before A (and so vice versa).
//
// Say robot A and B are going the same direction (WLOG, right).
// Assume the claim does not hold; that is, B reach C before A,
// then we know that A < B <= C < D.
// The expected distance is (C-A) + (D-B), which is equal to the actual distance (D-A) + (C-B).
// Therefore, we can simply swap the target factory of A and B
// to make the claim holds without interference the target distance.
//
// Say robot A and B are going the different direction (WLOG, A right and B left).
// Assume the claim does not hold; that is, B reach C before A,
// then we know that A < D <= C < B.
// The expected distance is (C-A) + (B-D), which is longer than the actual distance (D-A) + (B-C).
// Therefore, this case is impossible. Hence the claim holds.
//
// Assume the robots and the factories are sorted.
// With above claim, we know that the matching is also sorted.
//
// Now use DP for matching.
// We treat the factory with limit as multiple factories with limit=1.
// DP[i][j] is the min distance for first-i robots matches to the first-j factories.
//
// DP[0][0] = dist(0, 0)
// DP[i][j] = INF for i > j
// DP[0][j] = min(
//   dist(0, j), // use this factory
//   DP[0][j-1], // skip this factory
// )
// DP[i][j] = min(
//   DP[i-1][j-1] + dist(i, j), // use this factory
//   DP[i][j-1],                // skip this factory
// )
class Solution {
 public:
  int64_t minimumTotalDistance(vector<int>& robots, vector<vector<int>>& factories) {
    // Sort
    sort(robots.begin(), robots.end());
    sort(factories.begin(), factories.end(), [](auto& a, auto& b) -> bool {  //
      return a[0] < b[0];
    });

    // Duplicate factories
    auto facts = vector<int>();
    for (auto factory : factories) {
      int pos = factory[0], limit = factory[1];
      for (int l = 0; l < limit; ++l) facts.push_back(pos);
    }
    const int n = robots.size(), m = facts.size();

    // DP
    auto dp = vector<vector<int64_t>>(n, vector<int64_t>(m));

    // i=0
    dp[0][0] = abs(robots[0] - facts[0]);
    for (int j = 1; j < m; ++j) {
      int64_t dist = abs(robots[0] - facts[j]);
      dp[0][j] = min(dp[0][j - 1], dist);
    }

    // i>0
    for (int i = 1; i < n; ++i) {
      dp[i][i - 1] = INT64_MAX;
      for (int j = i; j < m; ++j) {
        int64_t dist = abs(robots[i] - facts[j]);
        dp[i][j] = min(dp[i - 1][j - 1] + dist, dp[i][j - 1]);
      }
    }

    return dp[n - 1][m - 1];
  }
};

// 2D-DP
//
// Add an addition row and column to DP matrix.
//
// DP[i][j] = min distance for matching all robots < i to some factories < j.
//
// DP[0][j] = 0
// DP[i][j] = INF for i > j
// DP[i][j] = min(
//   DP[i-1][j-1] + dist(i-1, j-1),
//   DP[i][j-1],
// )
class Solution2 {
 public:
  int64_t minimumTotalDistance(vector<int>& robots, vector<vector<int>>& factories) {
    // Sort
    sort(robots.begin(), robots.end());
    sort(factories.begin(), factories.end(), [](auto& a, auto& b) -> bool {  //
      return a[0] < b[0];
    });

    // Duplicate factories
    auto facts = vector<int>();
    for (auto factory : factories) {
      int pos = factory[0], limit = factory[1];
      for (int l = 0; l < limit; ++l) facts.push_back(pos);
    }
    const int n = robots.size(), m = facts.size();

    // DP
    auto dp = vector<vector<int64_t>>(n + 1, vector<int64_t>(m + 1));

    for (int i = 1; i <= n; ++i) {
      dp[i][i - 1] = INT64_MAX;
      for (int j = i; j <= m; ++j) {
        int64_t dist = abs(robots[i - 1] - facts[j - 1]);
        dp[i][j] = min(dp[i - 1][j - 1] + dist, dp[i][j - 1]);
      }
    }

    return dp[n][m];
  }
};

// 1D-DP
//
// DP[i][j] = min distance for matching all robots < i to some factories < j.
//
// DP[0][j] = 0
// DP[i][j] = INF for i > j
// DP[i][j] = min(
//   DP[i-1][j-1] + dist(i-1, j-1),
//   DP[i][j-1],
// )
//
// Prev = DP[i-1] and Curr = DP[i]
class Solution3 {
 public:
  int64_t minimumTotalDistance(vector<int>& robots, vector<vector<int>>& factories) {
    // Sort
    sort(robots.begin(), robots.end());
    sort(factories.begin(), factories.end(), [](auto& a, auto& b) -> bool {  //
      return a[0] < b[0];
    });

    // Duplicate factories
    auto facts = vector<int>();
    for (auto factory : factories) {
      int pos = factory[0], limit = factory[1];
      for (int l = 0; l < limit; ++l) facts.push_back(pos);
    }
    const int n = robots.size(), m = facts.size();

    // DP
    auto prev = vector<int64_t>(m + 1);
    auto curr = vector<int64_t>(m + 1);

    for (int i = 1; i <= n; ++i) {
      swap(curr, prev);
      curr[i - 1] = INT64_MAX;
      for (int j = i; j <= m; ++j) {
        int64_t dist = abs(robots[i - 1] - facts[j - 1]);
        curr[j] = min(prev[j - 1] + dist, curr[j - 1]);
      }
    }

    return curr[m];
  }
};

// 1D-DP
//
// DP[i][j] = min distance for matching all robots < i to some factories < j.
//
// DP[0][j] = 0
// DP[i][j] = INF for i > j
// DP[i][j] = min(
//   DP[i-1][j-1] + dist(i-1, j-1),
//   DP[i][j-1],
// )
//
// Let DP2[i][k] = DP[i][i+k] i.e. k=j-i
// DP2[0][k] = 0
// DP2[i][k] = min(
//   DP2[i-1][k] + dist(i-1, i+k-1),
//   DP2[i][k-1]
// )
class Solution4 {
 public:
  int64_t minimumTotalDistance(vector<int>& robots, vector<vector<int>>& factories) {
    // Sort
    sort(robots.begin(), robots.end());
    sort(factories.begin(), factories.end(), [](auto& a, auto& b) -> bool {  //
      return a[0] < b[0];
    });

    // Duplicate factories
    auto facts = vector<int>();
    for (auto factory : factories) {
      int pos = factory[0], limit = factory[1];
      for (int l = 0; l < limit; ++l) facts.push_back(pos);
    }
    const int n = robots.size(), m = facts.size();

    // DP
    auto dp = vector<int64_t>(m - n + 2);
    dp[0] = INT64_MAX;

    for (int i = 0; i < n; ++i) {
      for (int k = 0; k <= m - n; ++k) {
        int64_t dist = abs(robots[i] - facts[i + k]);
        dp[k + 1] = min(dp[k + 1] + dist, dp[k]);
      }
    }

    return dp[m - n + 1];
  }
};
