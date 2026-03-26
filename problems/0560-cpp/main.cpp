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

// Prefix Sum + Hash Map
//
// Compute the prefix sums.
// Use a hash map to store the counts of each sum value.
// For each prefix sum, add the counts for sum-k.
class Solution {
 public:
  int subarraySum(const vector<int>& nums, const int k) {
    const int n = nums.size();
    auto sumMap = unordered_map<int, int>();  // prefix sum -> count
    sumMap.reserve(n);

    // Prefix sum
    int ans = 0;
    int sum = 0;
    ++sumMap[sum];
    for (int num : nums) {
      sum += num;
      ans += sumMap[sum - k];
      ++sumMap[sum];
    }

    return ans;
  }
};
