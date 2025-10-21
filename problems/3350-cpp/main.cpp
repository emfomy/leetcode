// Source: https://leetcode.com/problems/adjacent-increasing-subarrays-detection-ii
// Title: Adjacent Increasing Subarrays Detection II
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array `nums` of `n` integers, your task is to find the **maximum** value of `k` for which there exist **two** adjacent <button type="button" aria-haspopup="dialog" aria-expanded="false" aria-controls="radix-:r1n:" data-state="closed" class="">subarrays</button> of length `k` each, such that both subarrays are **strictly** **increasing**. Specifically, check if there are **two** subarrays of length `k` starting at indices `a` and `b` (`a < b`), where:
//
// - Both subarrays `nums[a..a + k - 1]` and `nums[b..b + k - 1]` are **strictly increasing**.
// - The subarrays must be **adjacent**, meaning `b = a + k`.
//
// Return the **maximum** possible value of `k`.
//
// A **subarray** is a contiguous **non-empty** sequence of elements within an array.
//
// **Example 1:**
//
// ```
// Input: nums = [2,5,7,8,9,2,3,4,3,1]
// Output: 3
// Explanation:
// - The subarray starting at index 2 is `[7, 8, 9]`, which is strictly increasing.
// - The subarray starting at index 5 is `[2, 3, 4]`, which is also strictly increasing.
// - These two subarrays are adjacent, and 3 is the **maximum** possible value of `k` for which two such adjacent strictly increasing subarrays exist.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [1,2,3,4,4,4,4,5,6,7]
// Output: 2
// Explanation:
// - The subarray starting at index 0 is `[1, 2]`, which is strictly increasing.
// - The subarray starting at index 2 is `[3, 4]`, which is also strictly increasing.
// - These two subarrays are adjacent, and 2 is the **maximum** possible value of `k` for which two such adjacent strictly increasing subarrays exist.
// ```
//
// **Constraints:**
//
// - `2 <= nums.length <= 2 * 10^5`
// - `-10^9 <= nums[i] <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// Three pass
class Solution {
 public:
  int maxIncreasingSubarrays(vector<int>& nums) {
    int n = nums.size();

    auto leftSizes = vector<int>(n);
    auto rightSizes = vector<int>(n);

    {
      auto size = 1;
      leftSizes[0] = 1;
      for (auto i = 1; i < n; ++i) {
        if (nums[i] > nums[i - 1]) {
          size++;
        } else {
          size = 1;
        }

        leftSizes[i] = size;
      }
    }

    {
      auto size = 1;
      rightSizes[n - 1] = 1;
      for (auto i = n - 2; i >= 0; --i) {
        if (nums[i] < nums[i + 1]) {
          size++;
        } else {
          size = 1;
        }

        rightSizes[i] = size;
      }
    }

    auto ans = 0;
    for (auto i = 0; i < n - 1; ++i) {
      ans = max(ans, min(leftSizes[i], rightSizes[i + 1]));
    }

    return ans;
  }
};

// One pass
class Solution2 {
 public:
  int maxIncreasingSubarrays(vector<int>& nums) {
    int n = nums.size();

    auto ans = 0;
    auto currSize = 1, prevSize = 0;
    for (auto i = 1; i < n; ++i) {
      if (nums[i] > nums[i - 1]) {
        ++currSize;
      } else {
        prevSize = currSize;
        currSize = 1;
      }

      ans = max(ans, min(prevSize, currSize));
      ans = max(ans, currSize / 2);
    }

    return ans;
  }
};
