// Source: https://leetcode.com/problems/minimum-moves-to-make-array-complementary
// Title: Minimum Moves to Make Array Complementary
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `nums` of **even** length `n` and an integer `limit`. In one move, you can replace any integer from `nums` with another integer between `1` and `limit`, inclusive.
//
// The array `nums` is **complementary** if for all indices `i` (**0-indexed**), `nums[i] + nums[n - 1 - i]` equals the same number. For example, the array `[1,2,3,4]` is complementary because for all indices `i`, `nums[i] + nums[n - 1 - i] = 5`.
//
// Return the **minimum** number of moves required to make `nums` **complementary**.
//
// **Example 1:**
//
// ```
// Input: nums = [1,2,4,3], limit = 4
// Output: 1
// Explanation: In 1 move, you can change nums to [1,2,2,3] (underlined elements are changed).
// nums[0] + nums[3] = 1 + 3 = 4.
// nums[1] + nums[2] = 2 + 2 = 4.
// nums[2] + nums[1] = 2 + 2 = 4.
// nums[3] + nums[0] = 3 + 1 = 4.
// Therefore, nums[i] + nums[n-1-i] = 4 for every i, so nums is complementary.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [1,2,2,1], limit = 2
// Output: 2
// Explanation: In 2 moves, you can change nums to [2,2,2,2]. You cannot change any number to 3 since 3 > limit.
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [1,2,1,2], limit = 2
// Output: 0
// Explanation: nums is already complementary.
// ```
//
// **Constraints:**
//
// - `n == nums.length`
// - `2 <= n<=10^5`
// - `1 <= nums[i]<= limit <=10^5`
// - `n` is even.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

using namespace std;

// Difference Array
//
// For each pair, compute the sum.
// It takes 0~2 moves to change a pair sum to a target number.
//
// Say we have a pair (a, b). WLOG, a <= b.
//
// It takes 2 moves to change to [2, a] by reducing both.
// It takes 1 moves to change to (a, a+b) by reducing b.
// It takes 0 moves to change to a+b.
// It takes 1 moves to change to (a+b, limit+b] by increasing a.
// It takes 2 moves to change to (limit+b, 2limit] by increasing both.
//
// Use a difference array with range [0, 2limit]
// to compute the moves differences between all possible target sums.
class Solution {
 public:
  int minMoves(const vector<int>& nums, int limit) {
    const int n = nums.size();

    auto diffs = vector<int>(2 * limit + 2);

    // Diff array
    for (int i = 0; i < n / 2; ++i) {
      int a = nums[i], b = nums[n - 1 - i];
      if (a > b) swap(a, b);
      diffs[2] += 2;
      diffs[a + 1] -= 1;
      diffs[a + b] -= 1;
      diffs[a + b + 1] += 1;
      diffs[limit + b + 1] += 1;
    }

    // Find min
    int minMoves = 2 * n;
    int moves = 0;
    for (int sum = 2; sum <= 2 * limit; ++sum) {
      moves += diffs[sum];
      minMoves = min(minMoves, moves);
    }

    return minMoves;
  }
};
