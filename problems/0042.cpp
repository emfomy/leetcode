// Source: https://leetcode.com/problems/trapping-rain-water
// Title: Trapping Rain Water
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given `n` non-negative integers representing an elevation map where the width of each bar is `1`, compute how much water it can trap after raining.

// **Example 1:**
// https://assets.leetcode.com/uploads/2018/10/22/rainwatertrap.png

// ```
// Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
// Output: 6
// Explanation: The above elevation map (black section) is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are being trapped.
// ```

// **Example 2:**

// ```
// Input: height = [4,2,0,3,2,5]
// Output: 9
// ```

// **Constraints:**

// - `n == height.length`
// - `1 <= n <= 2 * 10^4`
// - `0 <= height[i] <= 10^5`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// Three Pass
//
// Scan from left  and track the maximum bar to the left.
// Scan from right and track the maximum bar to the right.
// Finally scan again. The water level the the minimum between left max and right max.
class Solution {
 public:
  int trap(const vector<int>& height) {
    const int n = height.size();

    // Left max
    auto leftMax = vector<int>(n);
    {
      int maxVal = 0;
      for (int i = 0; i < n; ++i) {
        maxVal = max(maxVal, height[i]);
        leftMax[i] = maxVal;
      }
    }

    // Right max
    auto rightMax = vector<int>(n);
    {
      int maxVal = 0;
      for (int i = n - 1; i >= 0; --i) {
        maxVal = max(maxVal, height[i]);
        rightMax[i] = maxVal;
      }
    }

    // Answer
    int total = 0;
    for (int i = 0; i < n; ++i) {
      // level >= height[i] since both math is at least height.
      int level = min(leftMax[i], rightMax[i]);
      total += level - height[i];
    }

    return total;
  }
};

// Two Pointer
//
// Let l=0 and r=n-1 at the beginning.
// Shrink both pointer to the center, and update the leftMax and rightMax.
//
// We want both pointer meet at the highest point.
// Therefore we always shrink the side with lower max value.
class Solution2 {
 public:
  int trap(const vector<int>& height) {
    const int n = height.size();

    // Init
    int left = 0, right = n - 1;
    int leftMax = height[left], rightMax = height[right];

    // Loop
    int total = 0;
    while (left < right) {
      if (leftMax <= rightMax) {
        ++left;
        leftMax = max(leftMax, height[left]);
        total += leftMax - height[left];  // left side's water only flow to left
      } else {
        --right;
        rightMax = max(rightMax, height[right]);
        total += rightMax - height[right];  // right side's water only flow to right
      }
    }

    return total;
  }
};
