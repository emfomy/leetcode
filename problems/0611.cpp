// Source: https://leetcode.com/problems/valid-triangle-number
// Title: Valid Triangle Number
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer array `nums`, return the number of triplets chosen from the array that can make triangles if we take them as side lengths of a triangle.
//
// **Example 1:**
//
// ```
// Input: nums = [2,2,3,4]
// Output: 3
// Explanation: Valid combinations are:
// 2,3,4 (using the first 2)
// 2,3,4 (using the second 2)
// 2,2,3
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [4,2,3,4]
// Output: 4
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 1000`
// - `0 <= nums[i] <= 1000`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// Sort, O(n^3)
class Solution {
 public:
  int triangleNumber(vector<int>& nums) {
    int n = nums.size();

    sort(nums.begin(), nums.end());

    auto ans = 0;
    for (auto i = 0; i < n; ++i) {
      for (auto j = i + 1; j < n; ++j) {
        for (auto k = j + 1; k < n; ++k) {
          if (nums[i] + nums[j] > nums[k]) {
            ++ans;
          }
        }
      }
    }

    return ans;
  }
};

// Sort + Binary Search, O(n^2 logn)
//
// For each a & b, find maximum c such that a+b > c.
// Note that idx(c) > idx(b).
class Solution2 {
 public:
  int triangleNumber(vector<int>& nums) {
    int n = nums.size();

    sort(nums.begin(), nums.end());

    auto ans = 0;
    for (auto i = 0; i < n; ++i) {
      for (auto j = i + 1; j < n; ++j) {
        // find first invalid index
        int k = lower_bound(nums.cbegin() + j, nums.cend(), nums[i] + nums[j]) - nums.cbegin();
        ans += max(k - j - 1, 0);
      }
    }

    return ans;
  }
};

// Sort + Two Pointer, O(n^2)
//
// Use two pointer to find c
class Solution3 {
 public:
  int triangleNumber(vector<int>& nums) {
    int n = nums.size();

    sort(nums.begin(), nums.end());

    auto ans = 0;
    for (auto i = 0; i < n; ++i) {
      auto k = i + 2;
      for (auto j = i + 1; j < n; ++j) {
        // find first invalid index
        while (k < n && nums[i] + nums[j] > nums[k]) ++k;
        ans += max(k - j - 1, 0);
      }
    }

    return ans;
  }
};

int main() {
  auto nums = vector<int>({0, 0, 0});
  cout << Solution3().triangleNumber(nums) << endl;
  return 0;
}
