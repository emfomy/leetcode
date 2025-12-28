// Source: https://leetcode.com/problems/minimum-time-to-make-rope-colorful
// Title: Minimum Time to Make Rope Colorful
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Alice has `n` balloons arranged on a rope. You are given a **0-indexed** string `colors` where `colors[i]` is the color of the `i^th` balloon.
//
// Alice wants the rope to be **colorful**. She does not want **two consecutive balloons** to be of the same color, so she asks Bob for help. Bob can remove some balloons from the rope to make it **colorful**. You are given a **0-indexed** integer array `neededTime` where `neededTime[i]` is the time (in seconds) that Bob needs to remove the `i^th` balloon from the rope.
//
// Return the **minimum time** Bob needs to make the rope **colorful**.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/12/13/ballon1.jpg
//
// ```
// Input: colors = "abaac", neededTime = [1,2,3,4,5]
// Output: 3
// Explanation: In the above image, 'a' is blue, 'b' is red, and 'c' is green.
// Bob can remove the blue balloon at index 2. This takes 3 seconds.
// There are no longer two consecutive balloons of the same color. Total time = 3.```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2021/12/13/balloon2.jpg
//
// ```
// Input: colors = "abc", neededTime = [1,2,3]
// Output: 0
// Explanation: The rope is already colorful. Bob does not need to remove any balloons from the rope.
// ```
//
// **Example 3:**
// https://assets.leetcode.com/uploads/2021/12/13/balloon3.jpg
//
// ```
// Input: colors = "aabaa", neededTime = [1,2,3,4,1]
// Output: 2
// Explanation: Bob will remove the balloons at indices 0 and 4. Each balloons takes 1 second to remove.
// There are no longer two consecutive balloons of the same color. Total time = 1 + 1 = 2.
// ```
//
// **Constraints:**
//
// - `n == colors.length == neededTime.length`
// - `1 <= n <= 10^5`
// - `1 <= neededTime[i] <= 10^4`
// - `colors` contains only lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// Greedy
//
// For any consecutive balloons with same color, we can only keep one of them.
// We can always remove the one with minimum needed time.
class Solution {
 public:
  int minCost(string colors, vector<int>& neededTime) {
    int n = colors.size();

    auto ans = 0;

    auto prevCol = ' ';
    auto prevCost = -1;
    for (auto idx = 0; idx < n; ++idx) {
      auto col = colors[idx];
      auto cost = neededTime[idx];

      if (col != prevCol) {
        prevCol = col;
        prevCost = cost;
      } else {
        ans += min(cost, prevCost);
        prevCost = max(cost, prevCost);
      }
    }

    return ans;
  }
};
