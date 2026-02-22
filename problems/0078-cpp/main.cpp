// Source: https://leetcode.com/problems/subsets
// Title: Subsets
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer array `nums` of **unique** elements, return all possible **subsets** (the power set).
//
// The solution set **must not** contain duplicate subsets. Return the solution in **any order**.
//
// **Example 1:**
//
// ```
// Input: nums = [1,2,3]
// Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [0]
// Output: [[],[0]]
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 10`
// - `-10 <= nums[i] <= 10`
// - All the numbers of`nums` are **unique**.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <bit>
#include <cstddef>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<vector<int>> subsets(vector<int>& nums) {
    const int n = nums.size(), m = 1 << n;  // m = 2^n

    auto subsets = vector<vector<int>>();
    subsets.reserve(m);

    for (size_t bits = 0; bits < m; ++bits) {
      auto subset = vector<int>();
      subset.reserve(popcount(bits));

      for (auto b = 0; b < n; ++b) {
        if (bits & (size_t(1) << b)) {
          subset.push_back(nums[b]);
        }
      }

      subsets.push_back(std::move(subset));
    }

    return subsets;
  }
};
