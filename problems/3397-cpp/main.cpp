// Source: https://leetcode.com/problems/maximum-number-of-distinct-elements-after-operations
// Title: Maximum Number of Distinct Elements After Operations
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `nums` and an integer `k`.
//
// You are allowed to perform the following **operation** on each element of the array **at most** once:
//
// - Add an integer in the range `[-k, k]` to the element.
//
// Return the **maximum** possible number of **distinct** elements in `nums` after performing the **operations**.
//
// **Example 1:**
//
// ```
// Input: nums = [1,2,2,3,3,4], k = 2
// Output: 6
// Explanation:
// `nums` changes to `[-1, 0, 1, 2, 3, 4]` after performing operations on the first four elements.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [4,4,4,4], k = 1
// Output: 3
// Explanation:
// By adding -1 to `nums[0]` and 1 to `nums[1]`, `nums` changes to `[3, 5, 4, 4]`.
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 10^5`
// - `1 <= nums[i] <= 10^9`
// - `0 <= k <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// Greedy
//
// We first sort the numbers.
// Loop the numbers from to minimal.
// For each number, convert it to the smallest possible distinct number.
class Solution {
 public:
  int maxDistinctElements(vector<int>& nums, int k) {
    sort(nums.begin(), nums.end());

    auto ans = 0;
    auto prev = -k;
    for (auto num : nums) {
      auto curr = min(max(prev + 1, num - k), num + k);
      if (prev < curr) ++ans;
      prev = curr;
    }

    return ans;
  }
};
