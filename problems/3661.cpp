// Source: https://leetcode.com/problems/maximum-walls-destroyed-by-robots
// Title: Maximum Walls Destroyed by Robots
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There is an endless straight line populated with some robots and walls. You are given integer arrays `robots`, `distance`, and `walls`:
//
// - `robots[i]` is the position of the `i^th` robot.
// - `distance[i]` is the **maximum** distance the `i^th` robot's bullet can travel.
// - `walls[j]` is the position of the `j^th` wall.
//
// Every robot has **one** bullet that can either fire to the left or the right **at most **`distance[i]` meters.
//
// A bullet destroys every wall in its path that lies within its range. Robots are fixed obstacles: if a bullet hits another robot before reaching a wall, it **immediately stops** at that robot and cannot continue.
//
// Return the **maximum** number of **unique** walls that can be destroyed by the robots.
//
// Notes:
//
// - A wall and a robot may share the same position; the wall can be destroyed by the robot at that position.
// - Robots are not destroyed by bullets.
//
// **Example 1:**
//
// ```
// Input: robots = [4], distance = [3], walls = [1,10]
// Output: 1
// Explanation:
// - `robots[0] = 4` fires **left** with `distance[0] = 3`, covering `[1, 4]` and destroys `walls[0] = 1`.
// - Thus, the answer is 1.
// ```
//
// **Example 2:**
//
// ```
// Input: robots = [10,2], distance = [5,1], walls = [5,2,7]
// Output: 3
// Explanation:
// - `robots[0] = 10` fires **left** with `distance[0] = 5`, covering `[5, 10]` and destroys `walls[0] = 5` and `walls[2] = 7`.
// - `robots[1] = 2` fires **left** with `distance[1] = 1`, covering `[1, 2]` and destroys `walls[1] = 2`.
// - Thus, the answer is 3.
// ```
//
// **Example 3:**
//
// ```
// Input: robots = [1,2], distance = [100,1], walls = [10]
// Output: 0
// Explanation:
// In this example, only `robots[0]` can reach the wall, but its shot to the **right** is blocked by `robots[1]`; thus the answer is 0.
// ```
//
// **Constraints:**
//
// - `1 <= robots.length == distance.length <= 10^5`
// - `1 <= walls.length <= 10^5`
// - `1 <= robots[i], walls[j] <= 10^9`
// - `1 <= distance[i] <= 10^5`
// - All values in `robots` are **unique**
// - All values in `walls` are **unique**
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <numeric>
#include <vector>

using namespace std;

// Sort + DP
class Solution {
 public:
  int maxWalls(                     //
      const vector<int>& robots,    //
      const vector<int>& distance,  //
      const vector<int>& walls      //
  ) {
    const int n = robots.size(), m = walls.size();

    // Sort
    auto robotIdxs = vector<int>(n);
    auto wallIdxs = vector<int>(m);
    iota(robotIdxs.begin(), robotIdxs.end(), 0);
    iota(wallIdxs.begin(), wallIdxs.end(), 0);
    sort(robotIdxs.begin(), robotIdxs.end(), [&robots](int i, int j) { return robots[i] < robots[j]; });
    sort(wallIdxs.begin(), wallIdxs.end(), [&walls](int i, int j) { return walls[i] < walls[j]; });

    // Count targets
    auto leftTargets = vector<int>(n);    // walls in the left range of a robot-i
    auto rightTargets = vector<int>(n);   // walls in the right range of robot-i
    auto commonTargets = vector<int>(n);  // walls in the left range of robot-i and the right range of robot-(i-1)
    {
      // robot[prevIdx] < wall <= robot[currIdx]
      int i = 0;  // index of robotIdxs
      for (const int wallIdx : wallIdxs) {
        int wall = walls[wallIdx];
        while (i < n && wall > robots[robotIdxs[i]]) ++i;

        // Wall and robot overlap
        if (i < n && wall == robots[robotIdxs[i]]) {
          ++rightTargets[i];
          ++leftTargets[i];
          continue;
        }

        bool inLeftBotRange = i > 0 && robots[robotIdxs[i - 1]] + distance[robotIdxs[i - 1]] >= wall;
        bool inRightBotRange = i < n && robots[robotIdxs[i]] - distance[robotIdxs[i]] <= wall;
        if (inLeftBotRange) ++rightTargets[i - 1];
        if (inRightBotRange) ++leftTargets[i];
        if (inLeftBotRange && inRightBotRange) ++commonTargets[i];
      }
    }

    // DP
    int currLeft = 0;   // maximum walls destroyed if the last robot fire left.
    int currRight = 0;  // maximum walls destroyed if the last robot fire right.
    for (int i = 0; i < n; ++i) {
      int nextLeft = max(currLeft, currRight - commonTargets[i]) + leftTargets[i];
      int nextRight = max(currLeft, currRight) + rightTargets[i];
      currLeft = nextLeft, currRight = nextRight;
    }

    return max(currLeft, currRight);
  }
};
