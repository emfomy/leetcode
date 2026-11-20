// Source: https://leetcode.com/problems/largest-perimeter-triangle
// Title: Largest Perimeter Triangle
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer array `nums`, return the largest perimeter of a triangle with a non-zero area, formed from three of these lengths. If it is impossible to form any triangle of a non-zero area, return `0`.
//
// **Example 1:**
//
// ```
// Input: nums = [2,1,2]
// Output: 5
// Explanation: You can form a triangle with three side lengths: 1, 2, and 2.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [1,2,1,10]
// Output: 0
// Explanation:
// You cannot use the side lengths 1, 1, and 2 to form a triangle.
// You cannot use the side lengths 1, 1, and 10 to form a triangle.
// You cannot use the side lengths 1, 2, and 10 to form a triangle.
// As we cannot use any three side lengths to form a triangle of non-zero area, we return 0.
// ```
//
// **Constraints:**
//
// - `3 <= nums.length <= 10^4`
// - `1 <= nums[i] <= 10^6`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <functional>
#include <vector>

using namespace std;

// Sort
class Solution {
 public:
  int largestPerimeter(vector<int>& nums) {
    int n = nums.size();
    sort(nums.begin(), nums.end(), greater<int>());  // sort desc

    for (auto i = 2; i < n; ++i) {
      auto a = nums[i - 2], b = nums[i - 1], c = nums[i];
      if (a < b + c) return a + b + c;
    }
    return 0;
  }
};
