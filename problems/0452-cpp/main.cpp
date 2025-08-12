// Source: https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons
// Title: Minimum Number of Arrows to Burst Balloons
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There are some spherical balloons taped onto a flat wall that represents the XY-plane. The balloons are represented as a 2D integer array `points` where `points[i] = [x_start, x_end]` denotes a balloon whose **horizontal diameter** stretches between `x_start` and `x_end`. You do not know the exact y-coordinates of the balloons.
//
// Arrows can be shot up **directly vertically** (in the positive y-direction) from different points along the x-axis. A balloon with `x_start` and `x_end` is **burst** by an arrow shot at `x` if `x_start <= x <= x_end`. There is **no limit** to the number of arrows that can be shot. A shot arrow keeps traveling up infinitely, bursting any balloons in its path.
//
// Given the array `points`, return the **minimum** number of arrows that must be shot to burst all balloons.
//
// **Example 1:**
//
// ```
// Input: points = [[10,16],[2,8],[1,6],[7,12]]
// Output: 2
// Explanation: The balloons can be burst by 2 arrows:
// - Shoot an arrow at x = 6, bursting the balloons [2,8] and [1,6].
// - Shoot an arrow at x = 11, bursting the balloons [10,16] and [7,12].
// ```
//
// **Example 2:**
//
// ```
// Input: points = [[1,2],[3,4],[5,6],[7,8]]
// Output: 4
// Explanation: One arrow needs to be shot for each balloon for a total of 4 arrows.
// ```
//
// **Example 3:**
//
// ```
// Input: points = [[1,2],[2,3],[3,4],[4,5]]
// Output: 2
// Explanation: The balloons can be burst by 2 arrows:
// - Shoot an arrow at x = 2, bursting the balloons [1,2] and [2,3].
// - Shoot an arrow at x = 4, bursting the balloons [3,4] and [4,5].
// ```
//
// **Constraints:**
//
// - `1 <= points.length <= 10^5`
// - `points[i].length == 2`
// - `-2^31 <= x_start < x_end <= 2^31 - 1`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cstdint>
#include <vector>

using namespace std;

// Use Greedy + Sort
//
// Sort the balloons by end position.
// The left-most balloon should be shot at the end coordinate.
//
// Say there is a minimal shot with the left-most shot NOT at the end of the left-most (by end) balloon.
// Say the shot's x coordinate is s, and the end of left-most balloon is b. s < b.
// For all balloons hit by this shot, we have x_start <= s <= x_end.
// Note that b is end of the left-most balloon.
// That is, x_start <= s < b <= x_end.
// Therefore we can use b instead.
//
// Loop this untail all balloon blows.
class Solution {
 public:
  int findMinArrowShots(vector<vector<int>> &points) {
    int n = points.size();

    // Sort
    auto startIdxs = vector<int>(n);
    auto endIdxs = vector<int>(n);
    auto bursted = vector<bool>(n);
    for (auto i = 0; i < n; i++) {
      startIdxs[i] = i;
      endIdxs[i] = i;
    }

    auto startComp = [&](int i, int j) -> bool { return points[i][0] < points[j][0]; };
    auto endComp = [&](int i, int j) -> bool { return points[i][1] < points[j][1]; };
    sort(startIdxs.begin(), startIdxs.end(), startComp);
    sort(endIdxs.begin(), endIdxs.end(), endComp);

    // Greedy
    auto ans = 0;
    auto startIdx = 0;
    for (auto endIdx = 0; endIdx < n; endIdx++) {
      // Already bursted
      if (bursted[endIdxs[endIdx]]) {
        continue;
      }

      // Make shot
      ans++;
      auto shot = points[endIdxs[endIdx]][1];
      bursted[endIdxs[endIdx]] = true;

      // Burst balloons
      while (startIdx < n) {
        auto &balloon = points[startIdxs[startIdx]];
        if (balloon[0] > shot) break;  // no need to check end here since shot is at left-most
        bursted[startIdxs[startIdx]] = true;
        startIdx++;
      }
    }

    return ans;
  }
};

// Use Greedy + Sort
//
// Same as above, but we don't need to sort by start.
// In the loop, all balloon start before previous shot must have been bursted.
class Solution2 {
 public:
  int findMinArrowShots(vector<vector<int>> &points) {
    int n = points.size();

    // Sort
    auto comp = [](vector<int> &a, vector<int> &b) -> bool { return a[1] < b[1]; };
    sort(points.begin(), points.end(), comp);

    // Greedy
    auto ans = 0;
    auto shot = -(int64_t(1) << 32);
    for (auto &point : points) {
      // Already bursted
      if (point[0] <= shot) continue;

      // Make shot
      shot = point[1];
      ans++;
    }

    return ans;
  }
};
