// Source: https://leetcode.com/problems/count-subarrays-with-median-k
// Title: Count Subarrays With Median K
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an array `nums` of size `n` consisting of **distinct **integers from `1` to `n` and a positive integer `k`.
//
// Return the number of non-empty subarrays in `nums` that have a **median** equal to `k`.
//
// **Note**:
//
// - The median of an array is the **middle **element after sorting the array in **ascending **order. If the array is of even length, the median is the **left **middle element.
//
// - For example, the median of `[2,3,1,4]` is `2`, and the median of `[8,4,3,5,1]` is `4`.
//
// - A subarray is a contiguous part of an array.
//
// **Example 1:**
//
// ```
// Input: nums = [3,2,1,4,5], k = 4
// Output: 3
// Explanation: The subarrays that have a median equal to 4 are: [4], [4,5] and [1,4,5].
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [2,3,1], k = 3
// Output: 1
// Explanation: [3] is the only subarray that has a median equal to 3.
// ```
//
// **Constraints:**
//
// - `n == nums.length`
// - `1 <= n <= 10^5`
// - `1 <= nums[i], k <= n`
// - The integers in `nums` are distinct.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <unordered_map>
#include <vector>

using namespace std;

// Brute Force, TLE
//
// In this problem, the medium must be in the subarray.
//
// We first find the position of number k.
// Next expand the subarray around k,
// and compute the number of elements greater / less than k during scanning.
// A subarray is medium k if these number are equal.
class Solution {
  int sign(int x) {  //
    return x > 0 ? 1 : x < 0 ? -1 : 0;
  }

 public:
  int countSubarrays(const vector<int>& nums, int k) {
    const int n = nums.size();

    // Find k
    int idx = find(nums.cbegin(), nums.cend(), k) - nums.cbegin();

    // Loop for subarray [i, j]
    int count = 0;
    int diffLeft = 0;  // #greater - #less before k
    for (int i = idx; i >= 0; --i) {
      diffLeft += sign(nums[i] - k);

      int diffRight = 0;  // #greater - #less after k
      for (int j = idx; j < n; ++j) {
        diffRight += sign(nums[j] - k);
        count += (diffLeft + diffRight == 0 || diffLeft + diffRight == 1);
      }
    }

    return count;
  }
};

// Hash Map
//
// Instead of brute-force all subarrays,
// we compute the difference value of left/right subarray around k.
// We use hash map to count these values, and compute the at the end.
class Solution2 {
  int sign(int x) {  //
    return x > 0 ? 1 : x < 0 ? -1 : 0;
  }

 public:
  int countSubarrays(const vector<int>& nums, int k) {
    const int n = nums.size();

    auto leftCount = unordered_map<int, int>();
    auto rightCount = unordered_map<int, int>();

    // Find k
    int idx = find(nums.cbegin(), nums.cend(), k) - nums.cbegin();

    // Left subarray
    for (int diff = 0, i = idx; i >= 0; --i) {
      diff += sign(nums[i] - k);
      ++leftCount[diff];
    }

    // Right subarray
    for (int diff = 0, j = idx; j < n; ++j) {
      diff += sign(nums[j] - k);
      ++rightCount[diff];
    }

    // Count
    int count = 0;
    for (const auto [diff, cnt] : leftCount) {
      count += cnt * (rightCount[-diff] + rightCount[-diff + 1]);
    }

    return count;
  }
};

// Hash Map (Array)
//
// We can use array instead of hash map to speed up.
// The difference is between -(n-1) ~ (n-1).
class Solution3 {
  int sign(int x) {  //
    return x > 0 ? 1 : x < 0 ? -1 : 0;
  }

 public:
  int countSubarrays(const vector<int>& nums, int k) {
    const int n = nums.size();

    auto leftCount = vector<int>(2 * n + 1);
    auto rightCount = vector<int>(2 * n + 1);

    // Find k
    int idx = find(nums.cbegin(), nums.cend(), k) - nums.cbegin();

    // Left subarray
    for (int diff = 0, i = idx; i >= 0; --i) {
      diff += sign(nums[i] - k);
      ++leftCount[diff + n];
    }

    // Right subarray
    for (int diff = 0, j = idx; j < n; ++j) {
      diff += sign(nums[j] - k);
      ++rightCount[diff + n];
    }

    // Count
    int count = 0;
    for (int diff = -(n - 1); diff <= (n - 1); ++diff) {
      count += leftCount[diff + n] * (rightCount[-diff + n] + rightCount[-diff + n + 1]);
    }

    return count;
  }
};
