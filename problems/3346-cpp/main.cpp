// Source: https://leetcode.com/problems/maximum-frequency-of-an-element-after-performing-operations-i
// Title: Maximum Frequency of an Element After Performing Operations I
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `nums` and two integers `k` and `numOperations`.
//
// You must perform an **operation** `numOperations` times on `nums`, where in each operation you:
//
// - Select an index `i` that was **not** selected in any previous operations.
// - Add an integer in the range `[-k, k]` to `nums[i]`.
//
// Return the **maximum** possible <button type="button" aria-haspopup="dialog" aria-expanded="false" aria-controls="radix-:r1n:" data-state="closed" class="">frequency</button> of any element in `nums` after performing the **operations**.
//
// **Example 1:**
//
// ```
// Input: nums = [1,4,5], k = 1, numOperations = 2
// Output: 2
// Explanation:
// We can achieve a maximum frequency of two by:
// - Adding 0 to `nums[1]`. `nums` becomes `[1, 4, 5]`.
// - Adding -1 to `nums[2]`. `nums` becomes `[1, 4, 4]`.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [5,11,20,20], k = 5, numOperations = 1
// Output: 2
// Explanation:
// We can achieve a maximum frequency of two by:
// - Adding 0 to `nums[1]`.
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 10^5`
// - `1 <= nums[i] <= 10^5`
// - `0 <= k <= 10^5`
// - `0 <= numOperations <= nums.length`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

using namespace std;

// Diff Array
//
// For each number x, we treat it as an interval [x-k, x+k].
//
// Assuming that numOperations is large enough.
// Now the problems becomes the maximum number of interval among all positions.
// We can use diff array to solve it.
//
// If the numOperations is not large enough,
// we also count the numbers among all positions.
// The frequency is equal to min(#intervals, count + numOperations)
class Solution {
 public:
  int maxFrequency(vector<int>& nums, int k, int numOperations) {
    const int N = 1e5;
    auto diffs = vector<int>(N + 2);
    auto counts = vector<int>(N + 2);

    for (auto num : nums) {
      auto left = max(1, num - k), right = min(N, num + k) + 1;
      ++counts[num];
      ++diffs[left];
      --diffs[right];
    }

    auto ans = 0, intervals = 0;
    for (auto i = 1; i <= N; ++i) {
      intervals += diffs[i];
      ans = max(ans, min(intervals, counts[i] + numOperations));
    }

    return ans;
  }
};

// Diff Array
class Solution2 {
 public:
  int maxFrequency(vector<int>& nums, int k, int numOperations) {
    auto minVal = *min_element(nums.cbegin(), nums.cend());
    auto maxVal = *max_element(nums.cbegin(), nums.cend());
    auto n = maxVal - minVal + 1;
    auto diffs = vector<int>(n + 2 * k + 1);
    auto counts = vector<int>(n + 2 * k + 1);

    for (auto num : nums) {
      auto left = num - minVal, center = left + k, right = left + 2 * k + 1;
      ++counts[center];
      ++diffs[left];
      --diffs[right];
    }

    auto ans = 0, intervals = 0;
    for (auto i = 0; i <= n + 2 * k; ++i) {
      intervals += diffs[i];
      ans = max(ans, min(intervals, counts[i] + numOperations));
    }

    return ans;
  }
};
