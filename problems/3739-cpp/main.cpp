// Source: https://leetcode.com/problems/count-subarrays-with-majority-element-i
// Title: Count Subarrays With Majority Element II
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `nums` and an integer `target`.
//
// Return the number of **<button>subarrays</button>** of `nums` in which `target` is the **majority element**.
//
// The **majority element** of a subarray is the element that appears **strictly** **more than half** of the times in that subarray.
//
// **Example 1:**
//
// ```
// Input: nums = [1,2,2,3], target = 2
// Output: 5
// Explanation:
// Valid subarrays with `target = 2` as the majority element:
// - `nums[1..1] = [2]`
// - `nums[2..2] = [2]`
// - `nums[1..2] = [2,2]`
// - `nums[0..2] = [1,2,2]`
// - `nums[1..3] = [2,2,3]`
// So there are 5 such subarrays.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [1,1,1,1], target = 1
// Output: 10
// Explanation:
// All 10 subarrays have 1 as the majority element.
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [1,2,3], target = 4
// Output: 0
// Explanation:
// `target = 4` does not appear in `nums` at all. Therefore, there cannot be any subarray where 4 is the majority element. Hence the answer is 0.
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 10^5`
// - `1 <= nums[i] <= 10^9`
// - `1 <= target <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// Prefix Sum + Count
//
// Define the `prefix` array as above.
// Note that we want to count the number of [l, r) with prefix[l] < prefix[r].
//
// Loop r from 0 to n, and count the number of prefix values.
// Use a value for accumulation sum.
//
// If current prefix[r] increases (i.e. nums[r] == target),
// add the number of prefix[r] (not including this one) to the accumulation sum.
// If decreases, substract prefix[r-1] from the accumulation sum.
class Solution {
 public:
  long long countMajoritySubarrays(const vector<int>& nums, int target) {
    const int n = nums.size();

    // Loop
    auto freqs = vector<int>(2 * n + 1);  // freq of prefix[i] of value [-n, ..., n]; offset by n
    freqs[n] = 1;
    int presum = n;       // prefix[r]
    int currCount = 0;    // valid l for this r
    long long count = 0;  // valid subarrays
    for (int num : nums) {
      if (num == target) {
        currCount += freqs[presum];
        ++presum;
        ++freqs[presum];
      } else {
        --presum;
        currCount -= freqs[presum];
        ++freqs[presum];
      }
      count += currCount;
    }

    return count;
  }
};
