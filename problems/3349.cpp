// Source: https://leetcode.com/problems/adjacent-increasing-subarrays-detection-i
// Title: Adjacent Increasing Subarrays Detection I
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array `nums` of `n` integers and an integer `k`, determine whether there exist **two** **adjacent** <button type="button" aria-haspopup="dialog" aria-expanded="false" aria-controls="radix-:r1n:" data-state="closed" class="">subarrays</button> of length `k` such that both subarrays are **strictly** **increasing**. Specifically, check if there are **two** subarrays starting at indices `a` and `b` (`a < b`), where:
//
// - Both subarrays `nums[a..a + k - 1]` and `nums[b..b + k - 1]` are **strictly increasing**.
// - The subarrays must be **adjacent**, meaning `b = a + k`.
//
// Return `true` if it is possible to find **two **such subarrays, and `false` otherwise.
//
// **Example 1:**
//
// ```
// Input: nums = [2,5,7,8,9,2,3,4,3,1], k = 3
// Output: true
// Explanation:
// - The subarray starting at index `2` is `[7, 8, 9]`, which is strictly increasing.
// - The subarray starting at index `5` is `[2, 3, 4]`, which is also strictly increasing.
// - These two subarrays are adjacent, so the result is `true`.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [1,2,3,4,4,4,4,5,6,7], k = 5
// Output: false
// ```
//
// **Constraints:**
//
// - `2 <= nums.length <= 100`
// - `1 < 2 * k <= nums.length`
// - `-1000 <= nums[i] <= 1000`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// Scan from left to right, mark ending index after at least k increasing numbers.
class Solution {
 public:
  bool hasIncreasingSubarrays(vector<int>& nums, int k) {
    int n = nums.size();

    // Prepare indices
    auto idxs = vector<bool>(n);
    auto prev = 10000;
    auto size = 0;
    for (auto i = 0; i < n; ++i) {
      if (nums[i] > prev) {
        size++;
      } else {
        size = 1;
      }

      if (size >= k) {
        idxs[i] = true;
        if (i >= k && idxs[i - k]) return true;
      }

      prev = nums[i];
    }

    return false;
  }
};

// Two pointer
class Solution2 {
 public:
  bool hasIncreasingSubarrays(vector<int>& nums, int k) {
    int n = nums.size();

    // Prepare indices
    auto left = 0, right = k;
    auto leftSize = 0, rightSize = 0;
    while (right < n) {
      if (left > 0 && nums[left] > nums[left - 1]) {
        ++leftSize;
      } else {
        leftSize = 1;
      }

      if (right > 0 && nums[right] > nums[right - 1]) {
        ++rightSize;
      } else {
        rightSize = 1;
      }

      if (leftSize >= k && rightSize >= k) return true;

      ++left;
      ++right;
    }

    return false;
  }
};
