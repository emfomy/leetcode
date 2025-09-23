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

// Use STL
class Solution {
 public:
  int findKthLargest(vector<int>& nums, int k) {
    nth_element(nums.begin(), nums.begin() + k - 1, nums.end(), greater<int>{});
    return nums[k];
  }
};

// Use Heap
class Solution2 {
 public:
  int findKthLargest(vector<int>& nums, int k) {
    auto pq = priority_queue(greater(), vector<int>());  // min-heap
    for (auto num : nums) {
      pq.push(num);
      if (pq.size() > k) pq.pop();
    }
    return pq.top();
  }
};

// Quick Select
//
// Time: Best O(n), Worst O(n^2), Average O(n)
// Space: O(n)
class Solution3 {
 public:
  int findKthLargest(vector<int>& nums, int k) {
    int pivot = nums[0];

    auto left = vector<int>();   // greater
    auto mid = vector<int>();    // equal
    auto right = vector<int>();  // less

    for (auto num : nums) {
      if (num > pivot) {
        left.push_back(num);
      } else if (num < pivot) {
        right.push_back(num);
      } else {
        mid.push_back(num);
      }
    }

    auto lSize = left.size();
    if (k <= lSize) {
      return findKthLargest(left, k);
    }
    k -= lSize;

    auto mSize = mid.size();
    if (k <= mSize) {
      return pivot;
    }
    k -= mSize;

    return findKthLargest(right, k);
  }
};

// Quick Select
//
// Time: Best O(n), Worst O(n^2), Average O(n)
// Space: O(1)
class Solution4 {
 public:
  int findKthLargest(vector<int>& nums, int k) {
    int lo = 0, hi = nums.size();

    while (true) {
      auto pivot = nums[lo];

      // [lo, l) > pivot, [l, i) = pivot, [i, r) unknown, [r, hi) < pivot
      auto l = lo;
      auto i = lo;
      auto r = hi;
      while (i < r) {
        if (nums[i] > pivot) {
          swap(nums[l++], nums[i++]);  // increase i since left l is known
        } else if (nums[i] < pivot) {
          swap(nums[i], nums[--r]);  // don't increase i since left r-1 is unknown
        } else {
          i++;
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
