// Source: https://leetcode.com/problems/search-in-rotated-sorted-array
// Title: Search in Rotated Sorted Array
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There is an integer array `nums` sorted in ascending order (with **distinct** values).
//
// Prior to being passed to your function, `nums` is **possibly left rotated** at an unknown index `k` (`1 <= k < nums.length`) such that the resulting array is `[nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]]` (**0-indexed**). For example, `[0,1,2,4,5,6,7]` might be left rotated by`3`indices and become `[4,5,6,7,0,1,2]`.
//
// Given the array `nums` **after** the possible rotation and an integer `target`, return the index of `target` if it is in `nums`, or `-1` if it is not in `nums`.
//
// You must write an algorithm with `O(log n)` runtime complexity.
//
// **Example 1:**
//
// ```
// Input: nums = [4,5,6,7,0,1,2], target = 0
// Output: 4
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [4,5,6,7,0,1,2], target = 3
// Output: -1
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [1], target = 0
// Output: -1
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 5000`
// - `-10^4 <= nums[i] <= 10^4`
// - All values of `nums` are **unique**.
// - `nums` is an ascending array that is possibly rotated.
// - `-10^4 <= target <= 10^4`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <functional>
#include <vector>

using namespace std;

// Binary Search
//
// Say the array rotate at k. That is,
// a[k+1] < a[k+2] < ... < a[n-1] < a[0] < a[1] < ... < a[k]
//
// Therefore, in binary search,
// we treat all number less than a[0] greater then all number greater than a[0]
class Solution {
 public:
  int search(vector<int>& nums, int target) {
    int n = nums.size();

    // Helper
    auto num0 = nums[0];
    auto myLess = [=](int a, int b) -> bool {
      if (a >= num0 && b < num0) return true;
      if (a < num0 && b >= num0) return false;
      return a < b;
    };

    // Binary search
    // nums[lo-1] < target, nums[hi] > target
    auto lo = 0, hi = n;
    while (lo < hi) {
      auto mid = lo + (hi - lo) / 2;
      if (nums[mid] == target) return mid;
      if (myLess(nums[mid], target)) {
        lo = mid + 1;
      } else {
        hi = mid;
      }
    }

    return -1;
  }
};
