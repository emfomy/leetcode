// Source: https://leetcode.com/problems/trionic-array-ii
// Title: Trionic Array II
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `nums` of length `n`.
//
// A **trionic subarray** is a contiguous subarray `nums[l...r]` (with `0 <= l < r < n`) for which there exist indices `l < p < q < r` such that:
//
// - `nums[l...p]` is **strictly** increasing,
// - `nums[p...q]` is **strictly** decreasing,
// - `nums[q...r]` is **strictly** increasing.
//
// Return the **maximum** sum of any trionic subarray in `nums`.
//
// **Example 1:**
//
// Input: nums = [0,-2,-1,-3,0,2,-1]
//
// Output: -4
//
// Explanation:
//
// Pick `l = 1`, `p = 2`, `q = 3`, `r = 5`:
//
// - `nums[l...p] = nums[1...2] = [-2, -1]` is strictly increasing (`-2 < -1`).
// - `nums[p...q] = nums[2...3] = [-1, -3]` is strictly decreasing (`-1 > -3`)
// - `nums[q...r] = nums[3...5] = [-3, 0, 2]` is strictly increasing (`-3 < 0 < 2`).
// - Sum = `(-2) + (-1) + (-3) + 0 + 2 = -4`.
//
// **Example 2:**
//
// Input: nums = [1,4,2,7]
//
// Output: 14
//
// Explanation:
//
// Pick `l = 0`, `p = 1`, `q = 2`, `r = 3`:
//
// - `nums[l...p] = nums[0...1] = [1, 4]` is strictly increasing (`1 < 4`).
// - `nums[p...q] = nums[1...2] = [4, 2]` is strictly decreasing (`4 > 2`).
// - `nums[q...r] = nums[2...3] = [2, 7]` is strictly increasing (`2 < 7`).
// - Sum = `1 + 4 + 2 + 7 = 14`.
//
// **Constraints:**
//
// - `4 <= n = nums.length <= 10^5`
// - `-10^9 <= nums[i] <= 10^9`
// - It is guaranteed that at least one trionic subarray exists.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <climits>
#include <cstdint>
#include <vector>

using namespace std;

// DP
//
// We first list all peak points.
// Next loop for each p & q, use DP for both direction to find the maximum sum.
class Solution {
  enum PeakType { PEAK, VALLEY, BAD };  // BAD means non-strictly

  using Peak = pair<int, PeakType>;  // index, peak type

 public:
  long long maxSumTrionic(vector<int>& nums) {
    int n = nums.size();

    auto peaks = vector<Peak>();
    for (auto i = 1; i < n - 1; ++i) {
      if (nums[i - 1] < nums[i] && nums[i] > nums[i + 1]) {
        peaks.push_back({i, PEAK});
      } else if (nums[i - 1] > nums[i] && nums[i] < nums[i + 1]) {
        peaks.push_back({i, VALLEY});
      } else if (nums[i - 1] == nums[i] || nums[i] == nums[i + 1]) {
        peaks.push_back({i, BAD});
      }
    }
    int m = peaks.size();

    int64_t ans = INT64_MIN;
    for (auto i = 0; i < m - 1; ++i) {
      if (peaks[i].second != PEAK || peaks[i + 1].second != VALLEY) continue;

      // p is PEAK; q is VALLEY
      auto p = peaks[i].first, q = peaks[i + 1].first;

      // Sum [p, q]
      int64_t sum = 0;
      for (auto i = p; i <= q; ++i) sum += nums[i];

      // Find left most and right most
      auto ll = (i == 0) ? 0 : peaks[i - 1].first;
      auto rr = (i + 1 == m - 1) ? n - 1 : peaks[i + 2].first;

      int64_t lMax = INT64_MIN, lCurr = 0;
      for (auto l = p - 1; l >= ll; --l) {
        lCurr += nums[l];
        lMax = max(lMax, lCurr);
      }

      int64_t rMax = INT64_MIN, rCurr = 0;
      for (auto r = q + 1; r <= rr; ++r) {
        rCurr += nums[r];
        rMax = max(rMax, rCurr);
      }

      ans = max(ans, sum + lMax + rMax);
    }

    return ans;
  }
};
