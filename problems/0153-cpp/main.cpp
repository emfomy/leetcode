// Source: https://leetcode.com/problems/find-minimum-in-rotated-sorted-array
// Title: Find Minimum in Rotated Sorted Array
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Suppose an array of length `n` sorted in ascending order is **rotated** between `1` and `n` times. For example, the array `nums = [0,1,2,4,5,6,7]` might become:
//
// - `[4,5,6,7,0,1,2]` if it was rotated `4` times.
// - `[0,1,2,4,5,6,7]` if it was rotated `7` times.
//
// Notice that **rotating** an array `[a[0], a[1], a[2], ..., a[n-1]]` 1 time results in the array `[a[n-1], a[0], a[1], a[2], ..., a[n-2]]`.
//
// Given the sorted rotated array `nums` of **unique** elements, return the minimum element of this array.
//
// You must write an algorithm that runs in`O(log n) time`.
//
// **Example 1:**
//
// ```
// Input: nums = [3,4,5,1,2]
// Output: 1
// Explanation: The original array was [1,2,3,4,5] rotated 3 times.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [4,5,6,7,0,1,2]
// Output: 0
// Explanation: The original array was [0,1,2,4,5,6,7] and it was rotated 4 times.
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [11,13,15,17]
// Output: 11
// Explanation: The original array was [11,13,15,17] and it was rotated 4 times.
// ```
//
// **Constraints:**
//
// - `n == nums.length`
// - `1 <= n <= 5000`
// - `-5000 <= nums[i] <= 5000`
// - All the integers of `nums` are **unique**.
// - `nums` is sorted and rotated between `1` and `n` times.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

using namespace std;

// Binary Search
//
// Mark all number with val >= nums[0] as LEFT,
// mark all number with val < nums[0] as RIGHT.
//
// Use binary search to find first RIGHT.
class Solution {
 public:
  int findMin(vector<int>& nums) {
    int n = nums.size();

    auto front = nums[0];
    if (front <= nums[n - 1]) return front;  // no rotate

    // Binary search
    auto lo = 1, hi = n;  // [1, n) unknown
    while (lo < hi) {
      auto mid = lo + (hi - lo) / 2;
      if (nums[mid] > front) {
        lo = mid + 1;  // [mid+1, hi)
      } else {
        hi = mid;  // [lo, mid)
      }
    }
    // nums[lo-1] LEFT; nums[lo=hi] RIGHT

    return nums[lo];
  }
};

// Binary Search (STL)
//
// Mark all number with val >= nums[0] as LEFT,
// mark all number with val < nums[0] as RIGHT.
//
// Use binary search to find first RIGHT.
class Solution2 {
 public:
  int findMin(vector<int>& nums) {
    int n = nums.size();

    // Compare
    auto front = nums[0];
    auto comp = [=](int a, int b) -> bool {
      auto aa = (a >= front) ? 0 : 1;
      auto bb = (b >= front) ? 0 : 1;
      return aa < bb;
    };

    // Binary search
    auto it = upper_bound(nums.cbegin(), nums.cend(), front, comp);
    return it == nums.cend() ? front : *it;
  }
};
