// Source: https://leetcode.com/problems/container-with-most-water
// Title: Container With Most Water
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `height` of length `n`. There are `n` vertical lines drawn such that the two endpoints of the `i^th` line are `(i, 0)` and `(i, height[i])`.
//
// Find two lines that together with the x-axis form a container, such that the container contains the most water.
//
// Return the maximum amount of water a container can store.
//
// **Notice** that you may not slant the container.
//
// **Example 1:**
// https://s3-lc-upload.s3.amazonaws.com/uploads/2018/07/17/question_11.jpg
//
// ```
// Input: height = [1,8,6,2,5,4,8,3,7]
// Output: 49
// Explanation: The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7]. In this case, the max area of water (blue section) the container can contain is 49.
// ```
//
// **Example 2:**
//
// ```
// Input: height = [1,1]
// Output: 1
// ```
//
// **Constraints:**
//
// - `n == height.length`
// - `2 <= n <= 10^5`
// - `0 <= height[i] <= 10^4`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

using namespace std;

// Two Pointer
//
// Start from l=0 and r = n-1.
// For each step,
// compare current area with the answer,
// and move the lower pointer to the center.
class Solution {
 public:
  int maxArea(const vector<int>& height) {
    const int n = height.size();
    int l = 0, r = n - 1;

    int ans = 0;
    while (l < n) {
      ans = max(ans, min(height[l], height[r]) * (r - l));
      if (height[l] <= height[r]) {
        ++l;
      } else {
        --r;
      }
    }

    return ans;
  }
};
