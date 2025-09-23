// Source: https://leetcode.com/problems/longest-increasing-subsequence
// Title: Longest Increasing Subsequence
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer array `nums`, return the length of the longest **strictly increasing subsequence**.
//
// A **subsequence** is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
//
// **Example 1:**
//
// ```
// Input: nums = [10,9,2,5,3,7,101,18]
// Output: 4
// Explanation: The longest increasing subsequence is [2,3,7,101], therefore the length is 4.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [0,1,0,3,2,3]
// Output: 4
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [7,7,7,7,7,7,7]
// Output: 1
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 2500`
// - `-10^4 <= nums[i] <= 10^4`
//
// **Follow up:** Can you come up with an algorithm that runs in`O(n log(n))` time complexity?
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <functional>
#include <iterator>
#include <map>
#include <vector>

using namespace std;

// DP, O(n^2)
class Solution {
 public:
  int lengthOfLIS(vector<int>& nums) {
    int n = nums.size();

    // DP
    auto dp = vector(n, 1);
    for (auto i = 0; i < n; ++i) {
      for (auto j = i + 1; j < n; ++j) {
        if (nums[j] > nums[i]) {
          dp[j] = max(dp[j], dp[i] + 1);
        }
      }
    }

    // Answer
    auto ansIt = max_element(dp.begin(), dp.end());

    return *ansIt;
  }
};

// Construct, O(n log n)
//
// We maintain a subsequence `tails`.
// For each step, we find the maximum less number and replace it.
// If current number is the max, we push it at end.
//
// Note that `tails` is not guaranteed to be a valid subsequence.
// However, the length of `tails` is guaranteed to equal to a valid one.
class Solution2 {
 public:
  int lengthOfLIS(vector<int>& nums) {
    int n = nums.size();

    // Stack
    auto tails = vector<int>();

    for (auto num : nums) {
      auto it = lower_bound(tails.begin(), tails.end(), num);
      if (it == tails.end()) {
        tails.push_back(num);
      } else {
        *it = num;
      }
    }

    return tails.size();
  }
};
