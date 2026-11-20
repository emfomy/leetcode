// Source: https://leetcode.com/problems/kth-largest-element-in-an-array
// Title: Kth Largest Element in an Array
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer array `nums` and an integer `k`, return the `k^th` largest element in the array.
//
// Note that it is the `k^th` largest element in the sorted order, not the `k^th` distinct element.
//
// Can you solve it without sorting?
//
// **Example 1:**
//
// ```
// Input: nums = [3,2,1,5,6,4], k = 2
// Output: 5
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
// Output: 4
// ```
//
// **Constraints:**
//
// - `1 <= k <= nums.length <= 10^5`
// - `-10^4 <= nums[i] <= 10^4`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <functional>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

// STL
class Solution {
 public:
  int findKthLargest(vector<int>& nums, int k) {
    nth_element(nums.begin(), nums.begin() + k - 1, nums.end(), greater<int>{});
    return nums[k - 1];
  }
};

// Heap
class Solution2 {
 public:
  int findKthLargest(const vector<int>& nums, int k) {
    auto heap = priority_queue<int, vector<int>, greater<>>();  // min-heap
    for (int num : nums) {
      heap.push(num);
      if (heap.size() > k) heap.pop();
    }

    return heap.top();
  }
};

// Quick Select
class Solution3 {
 public:
  int findKthLargest(vector<int>& nums, int k) {
    const int n = nums.size();
    if (k <= 0 || k > n) return -1;

    // Find in [lo, hi)
    int lo = 0, hi = n;
    while (true) {
      int pivot = nums[lo];

      // [lo, l): greater, [l, i) equal, [i, r): unknown, [r, hi): less
      int l = lo, i = lo, r = hi;
      while (i < r) {
        if (nums[i] > pivot) {
          swap(nums[i++], nums[l++]);
        } else if (nums[i] < pivot) {
          swap(nums[i], nums[--r]);
        } else {
          ++i;
        }
      }

      if (k <= l) {
        hi = l;
      } else if (k > r) {
        lo = r;
      } else {
        return pivot;
      }
    }

    return -1;  // unreachable
  }
};
