// Source: https://leetcode.com/problems/minimum-operations-to-make-a-uni-value-grid
// Title: Minimum Operations to Make a Uni-Value Grid
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a 2D integer `grid` of size `m x n` and an integer `x`. In one operation, you can **add** `x` to or **subtract** `x` from any element in the `grid`.
//
// A **uni-value grid** is a grid where all the elements of it are equal.
//
// Return the **minimum** number of operations to make the grid **uni-value**. If it is not possible, return `-1`.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/09/21/gridtxt.png
//
// ```
// Input: grid = [[2,4],[6,8]], x = 2
// Output: 4
// Explanation: We can make every element equal to 4 by doing the following:
// - Add x to 2 once.
// - Subtract x from 6 once.
// - Subtract x from 8 twice.
// A total of 4 operations were used.
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2021/09/21/gridtxt-1.png
//
// ```
// Input: grid = [[1,5],[2,3]], x = 1
// Output: 5
// Explanation: We can make every element equal to 3.
// ```
//
// **Example 3:**
// https://assets.leetcode.com/uploads/2021/09/21/gridtxt-2.png
//
// ```
// Input: grid = [[1,2],[3,4]], x = 2
// Output: -1
// Explanation: It is impossible to make every element equal.
// ```
//
// **Constraints:**
//
// - `m == grid.length`
// - `n == grid[i].length`
// - `1 <= m, n <= 10^5`
// - `1 <= m * n <= 10^5`
// - `1 <= x, grid[i][j] <= 10^4`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

using namespace std;

// Sort
//
// Sort the array, and compute the difference to the minimal element.
// If any of the difference is not a multiple of x, then the problem is impossible.
//
// Minimize Diff = |a[0] - k| + ... + |a[n-1] - k|.
// Say a[t-1] <= k < a[t]:
// Diff = (k - a[1]) + ... + (k - a_[t-1]) + (a[t] - k) + ... + (a[n-1] - k)
//      = sum(a[i]) - 2*(a[0]+...+a[t-1]) - (n-2t)*k
class Solution {
 public:
  int minOperations(const vector<vector<int>>& grid, int x) {
    const int mn = grid.size() * grid[0].size();

    // Sort
    auto nums = vector<int>();
    nums.reserve(mn);
    for (const auto& row : grid) {
      nums.insert(nums.cend(), row.cbegin(), row.cend());
    }
    sort(nums.begin(), nums.end());

    // Total Sum
    int sum = 0;
    int target = nums.front();
    for (const int num : nums) {
      if ((num - target) % x) return -1;
      sum += num;
    }

    // Loop
    int t = 0;  // nums[t-1] <= target < nums[t]
    int minDiff = sum, preSum = 0;
    for (int target = nums.front(); target <= nums.back(); target += x) {
      while (t < mn && nums[t] <= target) {
        preSum += nums[t];
        ++t;
      }
      minDiff = min(minDiff, sum - 2 * preSum - (mn - 2 * t) * target);
    }

    return minDiff / x;
  }
};

// Math (Medium)
//
// Say T is the target value, a[t-1] <= T < a[t].
// Diff = |a[0] - k| + ... + |a[mn-1] - k|.
//      = (T - a[0]) + ... + (T - a_[t-1]) + (a[t] - T) + ... + (a[N-1] - T)
//
// If we change T to T+x, then left t terms increases and right N-t terms decreases.
// More precisely, increases x*t and decreases x*(N-t).
// Therefore the Diff is minimized when x*t = x(N-t); that is, t = N/2.
//
// Hence T is the medium of the array.
class Solution2 {
 public:
  int minOperations(const vector<vector<int>>& grid, int x) {
    const int mn = grid.size() * grid[0].size();

    // Sort
    auto nums = vector<int>();
    nums.reserve(mn);
    {
      int firstNum = grid[0][0];
      for (const auto& row : grid) {
        for (const int num : row) {
          if ((num - firstNum) % x) return -1;
          nums.push_back(num);
        }
      }
    }
    nth_element(nums.begin(), nums.begin() + mn / 2, nums.end());
    int target = nums[mn / 2];

    // Loop
    int diff = 0;
    for (const int num : nums) {
      diff += abs(num - target);
    }

    return diff / x;
  }
};
