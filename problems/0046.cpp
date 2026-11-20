// Source: https://leetcode.com/problems/permutations
// Title: Permutations
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array `nums` of distinct integers, return all the possible **permutations**. You can return the answer in **any order**.
//
// A **permutation** is a rearrangement of all the elements of an array.
//
// **Example 1:**
//
// ```
// Input: nums = [1,2,3]
// Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [0,1]
// Output: [[0,1],[1,0]]
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [1]
// Output: [[1]]
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 6`
// - `-10 <= nums[i] <= 10`
// - All the integers of `nums` are **unique**.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

using namespace std;

// Built-in
class Solution {
 public:
  vector<vector<int>> permute(vector<int>& nums) {
    int n = nums.size();
    int facts[] = {1, 1, 2, 6, 24, 120, 720};

    auto ans = vector<vector<int>>();
    for (auto i = 0; i < facts[n]; ++i) {
      ans.push_back(nums);
      next_permutation(nums.begin(), nums.end());
    }

    return ans;
  }
};
