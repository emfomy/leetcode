// Source: https://leetcode.com/problems/search-insert-position
// Title: Search Insert Position
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a sorted array of distinct integers and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.
//
// You mustwrite an algorithm with`O(log n)` runtime complexity.
//
// **Example 1:**
//
// ```
// Input: nums = [1,3,5,6], target = 5
// Output: 2
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [1,3,5,6], target = 2
// Output: 1
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [1,3,5,6], target = 7
// Output: 4
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 10^4`
// - `-10^4 <= nums[i] <= 10^4`
// - `nums` contains **distinct** values sorted in **ascending** order.
// - `-10^4 <= target <= 10^4`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

using namespace std;

// Binary Search (STL)
class Solution {
 public:
  int searchInsert(vector<int>& nums, int target) { return lower_bound(nums.cbegin(), nums.cend(), target) - nums.cbegin(); }
};

// Binary Search
class Solution2 {
 public:
  int searchInsert(vector<int>& nums, int target) {
    int n = nums.size();

    // Binary search
    //
    auto lo = 0, hi = n;  // [0, n) unknown range
    while (lo < hi) {
      auto mid = lo + (hi - lo) / 2;
      if (nums[mid] < target) {
        lo = mid + 1;  // [mid+1, hi) unknown range
      } else {
        hi = mid;  // [lo, mid) unknown range
      }
    }

    // [0, lo) lower, [lo=hi, n) higher
    // nums[lo-1] < target, nums[lo=hi] >= target
    return lo;
  }
};
