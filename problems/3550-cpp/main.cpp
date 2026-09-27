// Source: https://leetcode.com/problems/smallest-index-with-digit-sum-equal-to-index
// Title: Smallest Index With Digit Sum Equal to Index
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `nums`.
//
// Return the **smallest** index `i` such that the sum of the digits of `nums[i]` is equal to `i`.
//
// If no such index exists, return `-1`.
//
// **Example 1:**
//
// ```
// Input: nums = [1,3,2]
// Output: 2
// Explanation:
// - For `nums[2] = 2`, the sum of digits is 2, which is equal to index `i = 2`. Thus, the output is 2.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [1,10,11]
// Output: 1
// Explanation:
// - For `nums[1] = 10`, the sum of digits is `1 + 0 = 1`, which is equal to index `i = 1`.
// - For `nums[2] = 11`, the sum of digits is `1 + 1 = 2`, which is equal to index `i = 2`.
// - Since index 1 is the smallest, the output is 1.
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [1,2,3]
// Output: -1
// Explanation:
// - Since no index satisfies the condition, the output is -1.
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 100`
// - `0 <= nums[i] <= 1000`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

class Solution {
 public:
  int smallestIndex(const vector<int>& nums) {
    const int n = nums.size();

    for (int i = 0; i < n; ++i) {
      int num = nums[i];
      int sum = 0;
      while (num > 0) {
        sum += num % 10;
        num /= 10;
      }
      if (sum == i) return i;
    }

    return -1;
  }
};
