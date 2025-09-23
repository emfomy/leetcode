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
// If nums[0] < nums[n-1], then k = 0.
// Otherwise, use binary search to find k such that nums[k-1] >= nums[0] and nums[k] < nums[0].
//
// Next use binary search find the target on nums[k, ..., n-1, 0, ..., l-1].
class Solution {
 public:
  int search(vector<int>& nums, int target) {
    int n = nums.size();

    // Find k
    int k;
    if (nums[0] <= nums[n - 1]) {  // use `=` for n = 1
      k = 0;
    } else {
      auto front = nums[0];
      auto lo = 1, hi = n;  // [1, n) is unknown
      while (lo < hi) {
        auto mid = lo + (hi - lo) / 2;
        if (nums[mid] >= front) {
          lo = mid + 1;  // [mid+1, hi)
        } else {
          hi = mid;  // [lo, mid)
        }
      }
      // nums[lo-1] >= front, nums[lo=hi] < front
      k = lo;
    }

    // Binary search
    {
      auto lo = k, hi = n + k;  // [k, n+k) is unknown
      while (lo < hi) {
        auto mid = lo + (hi - lo) / 2;
        auto val = nums[mid % n];
        if (val == target) return mid % n;
        if (val < target) {
          lo = mid + 1;  // [mid+1, hi)
        } else {
          hi = mid;
        }
      }
    }

    return -1;
  }
};

// Binary Search (STL)
//
// First compare target and nums[0].
// If target >= nums[0], then treat all number with val < nums[0] as inf.
// Othersize, then treat all number with val >= nums[0] as -inf.
class Solution2 {
 public:
  int search(vector<int>& nums, int target) {
    int n = nums.size();

    const int INF = 1e5;

    // Comp
    function<bool(int, int)> comp;
    auto front = nums[0];
    if (target >= front) {
      comp = [=](int a, int b) -> bool {
        if (a < front) a = INF;
        if (b < front) b = INF;
        return a <= b;
      };
    } else {
      comp = [=](int a, int b) -> bool {
        if (a >= front) a = -INF;
        if (b >= front) b = -INF;
        return a <= b;
      };
    }

    // Binary search
    auto it = lower_bound(nums.cbegin(), nums.cend(), target, comp);
    if (it != nums.cend() && *it == target) return it - nums.cbegin();
    return -1;
  }
};
