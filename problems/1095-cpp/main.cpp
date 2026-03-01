// Source: https://leetcode.com/problems/find-in-mountain-array
// Title: Find in Mountain Array
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// (This problem is an **interactive problem**.)
//
// You may recall that an array `arr` is a **mountain array** if and only if:
//
// - `arr.length >= 3`
// - There exists some `i` with `0 < i < arr.length - 1` such that:
//
// - `arr[0] < arr[1] < ... < arr[i - 1] < arr[i]`
// - `arr[i] > arr[i + 1] > ... > arr[arr.length - 1]`
//
// Given a mountain array `mountainArr`, return the **minimum** `index` such that `mountainArr.get(index) == target`. If such an `index` does not exist, return `-1`.
//
// **You cannot access the mountain array directly.** You may only access the array using a `MountainArray` interface:
//
// - `MountainArray.get(k)` returns the element of the array at index `k` (0-indexed).
// - `MountainArray.length()` returns the length of the array.
//
// Submissions making more than `100` calls to `MountainArray.get` will be judged Wrong Answer. Also, any solutions that attempt to circumvent the judge will result in disqualification.
//
// **Example 1:**
//
// ```
// Input: mountainArr = [1,2,3,4,5,3,1], target = 3
// Output: 2
// Explanation: 3 exists in the array, at index=2 and index=5. Return the minimum index, which is 2.```
//
// **Example 2:**
//
// ```
// Input: mountainArr = [0,1,2,4,2,1], target = 3
// Output: -1
// Explanation: 3 does not exist in `the array,` so we return -1.
// ```
//
// **Constraints:**
//
// - `3 <= mountainArr.length() <= 10^4`
// - `0 <= target <= 10^9`
// - `0 <= mountainArr.get(index) <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace std;

// This is the MountainArray's API interface.
// You should not implement it, or speculate about its implementation
class MountainArray {
 public:
  int get(int index);
  int length();
};

// Binary Search
//
// First use binary search to find the peak number.
// Next apply binary search to both side to find the target.
class Solution {
 public:
  int findInMountainArray(int target, MountainArray &arr) {
    const int n = arr.length();

    // Check size
    if (n == 0) return -1;

    // Find peak, binary search
    // D[0] = +, D[n-2] = -
    // D[lo-1] = +, D[hi] = -, [lo, hi) unknown
    int lo = 1, hi = n - 2;
    while (lo < hi) {
      int mid = lo + (hi - lo) / 2;
      if (arr.get(mid + 1) - arr.get(mid) < 0) {
        hi = mid;
      } else {
        lo = mid + 1;
      }
    }
    int peakIdx = hi;

    // Left side [0, peak), binary search
    // Pretend A[-1] < target, A[peak] > target
    lo = 0, hi = peakIdx;  // unknown [lo, hi)
    while (lo < hi) {
      int mid = lo + (hi - lo) / 2;
      int midVal = arr.get(mid);
      if (midVal == target) {
        return mid;
      } else if (midVal < target) {
        lo = mid + 1;
      } else {
        hi = mid;
      }
    }

    // Right side [peak, n), binary search
    // Pretend A[peak-1] > target, A[n] < target
    lo = peakIdx, hi = n;  // unknown [lo, hi)
    while (lo < hi) {
      int mid = lo + (hi - lo) / 2;
      int midVal = arr.get(mid);
      if (midVal == target) {
        return mid;
      } else if (midVal > target) {
        lo = mid + 1;
      } else {
        hi = mid;
      }
    }

    return -1;
  }
};
