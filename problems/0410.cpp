// Source: https://leetcode.com/problems/split-array-largest-sum
// Title: Split Array Largest Sum
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer array `nums` and an integer `k`, split `nums` into `k` non-empty subarrays such that the largest sum of any subarray is **minimized**.
//
// Return the minimized largest sum of the split.
//
// A **subarray** is a contiguous part of the array.
//
// **Example 1:**
//
// ```
// Input: nums = [7,2,5,10,8], k = 2
// Output: 18
// Explanation: There are four ways to split nums into two subarrays.
// The best way is to split it into [7,2,5] and [10,8], where the largest sum among the two subarrays is only 18.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [1,2,3,4,5], k = 2
// Output: 9
// Explanation: There are four ways to split nums into two subarrays.
// The best way is to split it into [1,2,3] and [4,5], where the largest sum among the two subarrays is only 9.
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 1000`
// - `0 <= nums[i] <= 10^6`
// - `1 <= k <= min(50, nums.length)`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// Binary Search
class Solution {
 public:
  int splitArray(vector<int>& nums, int k) {
    // Max & Total
    auto maxNum = 0, totalNum = 0;
    for (auto num : nums) {
      maxNum = max(maxNum, num);
      totalNum += num;
    }

    // Helper
    auto check = [&](int mid) -> bool {
      auto subSum = 0;
      auto count = 0;
      for (auto num : nums) {
        subSum += num;
        if (subSum > mid) {
          subSum = num;
          ++count;
        }
      }
      return count < k;
    };

    // Binary search
    // Find in [maxNum, totalNum]
    // check(lo-1) = false, check(hi) = true
    auto lo = maxNum, hi = totalNum;  // unknown [lo, hi)
    while (lo < hi) {
      auto mid = lo + (hi - lo) / 2;
      if (check(mid)) {
        hi = mid;  // [lo, mid)
      } else {
        lo = mid + 1;  // [mid+1, hi)
      }
    }

    return hi;
  }
};
