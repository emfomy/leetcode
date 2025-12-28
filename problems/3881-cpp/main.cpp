// Source: https://leetcode.com/problems/maximum-subarray-sum-with-length-divisible-by-k
// Title: Maximum Subarray Sum With Length Divisible by K
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an array of integers `nums` and an integer `k`.
//
// Return the **maximum** sum of a **subarray** of `nums`, such that the size of the subarray is **divisible** by `k`.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// **Example 1:**
//
// ```
// Input: nums = [1,2], k = 1
// Output: 3
// Explanation:
// The subarray `[1, 2]` with sum 3 has length equal to 2 which is divisible by 1.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [-1,-2,-3,-4,-5], k = 4
// Output: -10
// Explanation:
// The maximum sum subarray is `[-1, -2, -3, -4]` which has length equal to 4 which is divisible by 4.
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [-5,1,2,-3,4], k = 2
// Output: 4
// Explanation:
// The maximum sum subarray is `[1, 2, -3, 4]` which has length equal to 4 which is divisible by 2.
// ```
//
// **Constraints:**
//
// - `1 <= k <= nums.length <= 2 * 10^5`
// - `-10^9 <= nums[i] <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <vector>

using namespace std;

// DP, TLE, O(nk)
//
// DP[i][r] is the maximum sum of the subarrays in before i, whose size is congruent to r modulo k.
class Solution {
 public:
  int64_t maxSubarraySum(vector<int>& nums, int k) {
    int n = nums.size();

    auto ans = INT64_MIN;
    auto dp = vector(n + 1, vector(k, INT64_MIN / 2));
    for (auto i = n - 1; i >= 0; --i) {
      int64_t num = nums[i];
      dp[i][1 % k] = max(dp[i][1 % k], num);
      for (auto r = 0; r < k; ++r) {
        dp[i][(r + 1) % k] = max(dp[i][(r + 1) % k], dp[i + 1][r] + num);
      }
      ans = max(ans, dp[i][0]);
    }

    return ans;
  }
};

// Prefix Sum
//
// Prefix[r] is the minimal prefix of subarray[0:i), whose size is congruent to r modulo k.
// For all j, we know that size of [i:j) is divisible by k if i & j are in the same class.
class Solution2 {
 public:
  int64_t maxSubarraySum(vector<int>& nums, int k) {
    int n = nums.size();

    auto ans = INT64_MIN;
    auto sum = int64_t(0);
    auto prefix = vector(k, INT64_MAX / 2);
    prefix[0] = 0;
    for (auto j = 1; j <= n; ++j) {
      sum += nums[j - 1];
      ans = max(ans, sum - prefix[j % k]);
      prefix[j % k] = min(prefix[j % k], sum);
    }

    return ans;
  }
};

// Prefix Sum
class Solution3 {
 public:
  int64_t maxSubarraySum(vector<int>& nums, int k) {
    int n = nums.size();

    auto ans = INT64_MIN;
    auto sum = int64_t(0);
    auto prefix = vector(k, INT64_MAX / 2);
    prefix[k - 1] = 0;
    for (auto j = 0; j < n; ++j) {
      sum += nums[j];
      ans = max(ans, sum - prefix[j % k]);
      prefix[j % k] = min(prefix[j % k], sum);
    }

    return ans;
  }
};
