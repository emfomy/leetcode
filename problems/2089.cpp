// Source: https://leetcode.com/problems/find-target-indices-after-sorting-array
// Title: Find Target Indices After Sorting Array
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a **0-indexed** integer array `nums` and a target element `target`.
//
// A **target index** is an index `i` such that `nums[i] == target`.
//
// Return a list of the target indices of `nums` after sorting `nums` in **non-decreasing** order. If there are no target indices, return an **empty** list. The returned list must be sorted in **increasing** order.
//
// **Example 1:**
//
// ```
// Input: nums = [1,2,5,2,3], target = 2
// Output: [1,2]
// Explanation: After sorting, nums is [1,**2**,**2**,3,5].
// The indices where nums[i] == 2 are 1 and 2.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [1,2,5,2,3], target = 3
// Output: [3]
// Explanation: After sorting, nums is [1,2,2,**3**,5].
// The index where nums[i] == 3 is 3.
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [1,2,5,2,3], target = 5
// Output: [4]
// Explanation: After sorting, nums is [1,2,2,3,**5**].
// The index where nums[i] == 5 is 4.
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 100`
// - `1 <= nums[i], target <= 100`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

// Sort + Binary Search
class Solution {
 public:
  vector<int> targetIndices(vector<int>& nums, int target) {
    // Sort
    sort(nums.begin(), nums.end());

    // Find
    auto [lo, hi] = equal_range(nums.cbegin(), nums.cend(), target);

    // Answer
    auto ans = vector<int>(hi - lo);
    iota(ans.begin(), ans.end(), lo - nums.cbegin());
    return ans;
  }
};

// Count
//
// Count number of element less/greater than target.
class Solution2 {
 public:
  vector<int> targetIndices(const vector<int>& nums, int target) {
    int smaller = 0, equal = 0;
    for (int num : nums) {
      if (num < target) {
        ++smaller;
      } else if (num == target) {
        ++equal;
      }
    }

    // Answer
    auto ans = vector<int>(equal);
    iota(ans.begin(), ans.end(), smaller);
    return ans;
  }
};
