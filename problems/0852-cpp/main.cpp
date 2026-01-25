// Source: https://leetcode.com/problems/peak-index-in-a-mountain-array
// Title: Peak Index in a Mountain Array
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer **mountain** array `arr` of length `n` where the values increase to a **peak element** and then decrease.
//
// Return the index of the peak element.
//
// Your task is to solve it in `O(log(n))` time complexity.
//
// **Example 1:**
//
// ```
// Input: arr = [0,1,0]
// Output: 1
// ```
//
// **Example 2:**
//
// ```
// Input: arr = [0,2,1,0]
// Output: 1
// ```
//
// **Example 3:**
//
// ```
// Input: arr = [0,10,5,2]
// Output: 1
// ```
//
// **Constraints:**
//
// - `3 <= arr.length <= 10^5`
// - `0 <= arr[i] <= 10^6`
// - `arr` is **guaranteed** to be a mountain array.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// Use binary search on diff[i] = arr[i+1] - arr[i]
class Solution {
 public:
  int peakIndexInMountainArray(vector<int>& arr) {
    int n = arr.size();

    // Binary Search
    // diff(lo-1) > 0, diff(hi) > 0
    auto lo = 0, hi = n - 1;
    while (lo < hi) {
      auto mid = lo + (hi - lo) / 2;
      if (arr[mid + 1] - arr[mid] > 0) {
        lo = mid + 1;
      } else {
        hi = mid;
      }
    }

    return lo;
  }
};
