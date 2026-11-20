// Source: https://leetcode.com/problems/intersection-of-two-arrays
// Title: Intersection of Two Arrays
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given two integer arrays `nums1` and `nums2`, return an array of their **intersection**. Each element in the result must be **unique** and you may return the result in **any order**.
//
// The **intersection** of two arrays is defined as the set of elements that are present in both arrays.
//
// **Example 1:**
//
// ```
// Input: nums1 = [1,2,2,1], nums2 = [2,2]
// Output: [2]
// ```
//
// **Example 2:**
//
// ```
// Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
// Output: [9,4]
// Explanation: [4,9] is also accepted.
// ```
//
// **Constraints:**
//
// - `1 <= nums1.length, nums2.length <= 1000`
// - `0 <= nums1[i], nums2[i] <= 1000`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
    auto set1 = vector<bool>(1001);
    auto set2 = vector<bool>(1001);

    for (auto num : nums1) set1[num] = true;
    for (auto num : nums2) set2[num] = true;

    auto ans = vector<int>();
    for (auto num = 0; num <= 1000; ++num) {
      if (set1[num] && set2[num]) {
        ans.push_back(num);
      }
    }

    return ans;
  }
};
