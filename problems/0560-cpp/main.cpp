// Source: https://leetcode.com/problems/subarray-sum-equals-k
// Title: Subarray Sum Equals K
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array of integers `nums` and an integer `k`, return the total number of subarrays whose sum equals to `k`.
//
// A subarray is a contiguous **non-empty** sequence of elements within an array.
//
// **Example 1:**
//
// ```
// Input: nums = [1,1,1], k = 2
// Output: 2
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [1,2,3], k = 3
// Output: 2
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 2 * 10^4`
// - `-1000 <= nums[i] <= 1000`
// - `-10^7 <= k <= 10^7`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <unordered_map>
#include <vector>

using namespace std;

// Loop & Sum
class Solution {
 public:
  int subarraySum(vector<int>& nums, int k) {
    int n = nums.size();

    // Loop
    auto ans = 0;
    for (auto i = 0; i < n; ++i) {
      auto sum = 0;
      for (auto j = i; j < n; ++j) {
        sum += nums[j];
        if (sum == k) {
          ++ans;
        }
      }
    }

    return ans;
  }
};

// Prefix Sum + Hash Map Count
//
// Precompute prefix sum.
// Use idea of two sum to find the answer.
//
// A - B = k, B = a - k.
class Solution2 {
 public:
  int subarraySum(vector<int>& nums, int k) {
    int n = nums.size();

    // Prefix sum
    auto prefixs = vector<int>(n + 1);
    for (auto i = 0; i < n; ++i) {
      prefixs[i + 1] = prefixs[i] + nums[i];
    }

    // Difference
    auto ans = 0;
    auto counter = unordered_map<int, int>();
    for (auto prefix : prefixs) {
      ans += counter[prefix - k];
      counter[prefix]++;
    }

    return ans;
  }
};

// Prefix Sum + Hash Map Count
//
// We don't need array for prefix sum
class Solution3 {
 public:
  int subarraySum(vector<int>& nums, int k) {
    auto counter = unordered_map<int, int>();

    // Prefix sum
    auto ans = 0, prefix = 0;
    counter[0] = 1;
    for (auto num : nums) {
      prefix += num;
      ans += counter[prefix - k];
      counter[prefix]++;
    }

    return ans;
  }
};
